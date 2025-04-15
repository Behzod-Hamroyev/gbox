#include "Manager.h"
#include <iostream>

Manager::Manager() = default;

void Manager::viewAllUsers(const vector<unique_ptr<UniversityMember>>& users) const {
    for (const auto& user : users) {
        cout << "Name: " << user->getName() << ", ID: " << user->getID() << endl;
    }
}

void Manager::viewInbox(const vector<unique_ptr<UniversityMember>>& users, const string& name) const {
    for (const auto& user : users) {
        if (user->getName() == name) {
            string inboxStr = user->getInbox();
            if (inboxStr.empty()) {
                cout << "Inbox is empty.\n";
            } else {
                cout << "Inbox of " << user->getName() << ": " << endl;
                cout << inboxStr;
            }

            return;
        }
    }
    cout << "User not found." << endl;
}

void Manager::viewUserInfo(const vector<unique_ptr<UniversityMember>>& users, const string& name) const {
    for (const auto& user : users) {
        if (user->getName() == name) {
            cout << "Name: " << user->getName() << ", ID: " << user->getID() << std::endl;
            return;
        }
    }
    cout << "User not found." << std::endl;
}

void Manager::removeUser(vector<unique_ptr<UniversityMember>>& users, const string& name) {
    for (auto it = users.begin(); it != users.end(); ++it) {
        if ((*it)->getName() == name) {
            users.erase(it);
            std::cout << "User removed." << std::endl;
            return;
        }
    }
    std::cout << "User not found." << std::endl;
}