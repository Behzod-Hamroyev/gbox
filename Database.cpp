#include "Database.h"
#include "Student.h"
#include "Faculty.h"
#include "Administration.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std;

string getCurrentTimestamp() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}

void saveUsers(const vector<unique_ptr<UniversityMember>>& users) {
    ofstream out("users.db");
    if (!out) {
        cerr << "Error opening users.db for writing." << endl;
        return;
    }

    for (const auto& user : users) {
        string role;
        if (dynamic_cast<Student*>(user.get())) role = "Student";
        else if (dynamic_cast<Faculty*>(user.get())) role = "Faculty";
        else if (dynamic_cast<Administration*>(user.get())) role = "Administration";
        else continue;

        out << "#ROLE: " << role << "\n";
        out << user->getName() << "\n";
        out << user->getID() << "\n";

        const auto& inbox = user->getInbox();
        out << inbox.size() << "\n";
        for (const Message& msg : inbox) {
            out << msg.sender << "|" << msg.timestamp << "|" << msg.content << "\n";
        }
    }

    out.close();
}

void loadUsers(vector<unique_ptr<UniversityMember>>& users) {
    ifstream in("users.db");
    if (!in) {
        cerr << "users.db not found. Skipping load." << endl;
        return;
    }

    string line;
    while (getline(in, line)) {
        if (line.rfind("#ROLE:", 0) != 0) continue;
        string role = line.substr(7);

        string name, id;
        getline(in, name);
        getline(in, id);

        int messageCount;
        in >> messageCount;
        in.ignore();

        unique_ptr<UniversityMember> user;
        if (role == "Student") user = make_unique<Student>(name, id);
        else if (role == "Faculty") user = make_unique<Faculty>(name, id);
        else if (role == "Administration") user = make_unique<Administration>(name, id);
        else continue;

        for (int i = 0; i < messageCount; ++i) {
            string msgLine;
            getline(in, msgLine);
            size_t firstDelim = msgLine.find('|');
            size_t secondDelim = msgLine.find('|', firstDelim + 1);

            if (firstDelim == string::npos || secondDelim == string::npos) continue;

            string sender = msgLine.substr(0, firstDelim);
            string timestamp = msgLine.substr(firstDelim + 1, secondDelim - firstDelim - 1);
            string content = msgLine.substr(secondDelim + 1);

            user->receiveMessage({ sender, timestamp, content });
        }

        users.push_back(std::move(user));
    }

    in.close();
}

void appendMessageToFile(const string& recipientID, const Message& message) {
    ifstream in("users.db");
    if (!in) {
        cerr << "users.db not found. Cannot append message." << endl;
        return;
    }

    vector<string> lines;
    string line;
    while (getline(in, line)) {
        lines.push_back(line);
    }
    in.close();

    ofstream out("users.db");
    if (!out) {
        cerr << "Failed to open users.db for writing." << endl;
        return;
    }

    for (size_t i = 0; i < lines.size(); ++i) {
        out << lines[i] << '\n';

        if (lines[i].rfind("#ROLE:", 0) == 0 && i + 2 < lines.size()) {
            string name = lines[i + 1];
            string id = lines[i + 2];

            if (id == recipientID) {
                int msgCount = stoi(lines[i + 3]);
                msgCount++;
                lines[i + 3] = to_string(msgCount); // Update message count

                out << name << '\n';
                out << id << '\n';
                out << msgCount << '\n';

                i += 3; // move index to just after ID line

                // Copy old messages
                for (int m = 0; m < msgCount - 1; ++m) {
                    out << lines[++i] << '\n';
                }

                // Append new message
                out << message.sender << "|" << message.timestamp << "|" << message.content << '\n';
            }
        }
    }

    out.close();
}
