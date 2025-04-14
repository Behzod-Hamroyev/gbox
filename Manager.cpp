#include "Manager.h"
#include <iostream>

Manager::Manager() = default;

void Manager::viewAllUsers(const vector<unique_ptr<UniversityMember>>& users) const {
    for (const auto& user : users) {
        cout << "ID: " << user->getID() << ", Name: " << user->getName() << endl;
    }
}

void Manager::viewInbox(const vector<std::unique_ptr<UniversityMember>>& users, const string& id) const {
    for (const auto& user : users) {
        if (user->getID() == id) {
            cout << "Inbox: " << user->getInbox() << endl;
            return;
        }
    }
    std::cout << "User not found." << std::endl;
}

void Manager::viewUserInfo(const vector<unique_ptr<UniversityMember>>& users, const string& id) const {
    for (const auto& user : users) {
        if (user->getID() == id) {
            cout << "Name: " << user->getName() << ", ID: " << user->getID() << std::endl;
            return;
        }
    }
    cout << "User not found." << std::endl;
}

void Manager::removeUser(vector<unique_ptr<UniversityMember>>& users, const string& id) {
    for (auto it = users.begin(); it != users.end(); ++it) {
        if ((*it)->getID() == id) {
            users.erase(it);
            std::cout << "User removed." << std::endl;
            return;
        }
    }
    std::cout << "User not found." << std::endl;
}