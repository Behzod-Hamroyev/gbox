#include "UniversityMember.h"
#include <ctime>
#include <sstream>
#include <fstream>
#include <iomanip>

UniversityMember::UniversityMember(const string& name, const string& id)
    : name(name), id(id) {}

string UniversityMember::getName() const {
    return name;
}

void UniversityMember::setName(const string& newName) {
    name = newName;
}

void UniversityMember::sendMessage(UniversityMember& recipient, const string& content, bool anonymous) const {
    Message msg;
    msg.sender = anonymous ? "Anonymous" : name;

    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    msg.timestamp = string(buffer);

    msg.content = content;
    recipient.receiveMessage(msg);
}

void UniversityMember::receiveMessage(const Message& msg) {
    inbox.push_back(msg);
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
