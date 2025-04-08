#include "UniversityMember.h"

UniversityMember::UniversityMember(string name, int age) : name(name), age(age) {}

string UniversityMember::getName() const { return name; }
void UniversityMember::setName(const string& newName) { name = newName; }

int UniversityMember::getAge() const { return age; }
void UniversityMember::setAge(int newAge) { age = newAge; }

void UniversityMember::sendMessage(UniversityMember& recipient, const string& message) {
    recipient.inbox.push_back(name + ": " + message);
}

void UniversityMember::getMessages() const {
    cout << "Inbox of " << name << ":\n";
    for (const string& msg : inbox) {
        cout << msg << endl;
    }
}