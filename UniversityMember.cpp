#include "UniversityMember.h"
#include <iostream>
#include <sstream>
#include <ctime>

UniversityMember::UniversityMember(const string& name, const string& id) : name(name), id(id) {}

string UniversityMember::getName() const { return name; }
void UniversityMember::setName(const string& newName) { name = newName; }

void UniversityMember::sendMessage(UniversityMember& recipient, const string& content, bool anonymous) {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);

    Message msg = {
        .sender = anonymous ? "Anonymous" : name,
        .timestamp = buffer,
        .content = content
    };

    recipient.receiveMessage(msg);
}

void UniversityMember::receiveMessage(const Message& message) {
    inbox.push_back(message);
}

string UniversityMember::getInbox() const {
    ostringstream oss;
    for (const Message& msg : inbox) {
        oss << "From: " << msg.sender << "\n";
        oss << "At: " << msg.timestamp << "\n";
        oss << "Message: " << msg.content << "\n";
        oss << "--------------------------\n";
    }
    return oss.str();
}

const vector<Message>& UniversityMember::getRawInbox() const {
    return inbox;
}