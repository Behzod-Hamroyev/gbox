#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <limits>

#include "UniversityMember.h"
#include "Registration.h"
#include "Manager.h"
#include "Database.h"

using namespace std;

void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
};
int getMenuChoice(int min, int max) {
    int choice;
    while (true) {
        cout << "Enter your choice (" << min << "-" << max << "): ";
        cin >> choice;
        if (cin.fail() || choice < min || choice > max) {
            cin.clear();
            clearInputBuffer();
            cout << "Invalid input. Try again.\n";
        } else {
            clearInputBuffer();
            return choice;
        }
    }
}

UniversityMember* findUser(const vector<unique_ptr<UniversityMember>>& users, const string& name, const string& id) {
    for (const auto& user : users) {
        if (user->getName() == name && user->getID() == id) {
            return user.get();
        }
    }
    return nullptr;
}

UniversityMember* findUserByName(const vector<unique_ptr<UniversityMember>>& users, const string& name) {
    for (const auto& user : users) {
        if (user->getName() == name) return user.get();
    }
    return nullptr;
}

void settingsMenu(UniversityMember* user) {
    bool inSettings = true;
    while (inSettings) {
        cout << "\n--- Settings Menu ---\n";
        cout << "1. Change Name\n2. Display User ID\n0. Go Back\n";
        int choice = getMenuChoice(0, 2);
        switch (choice) {
            case 1: {
                cout << "Enter new name: ";
                string newName;
                getline(cin, newName);
                user->setName(newName);
                cout << "Name changed successfully.\n";
                break;
            }
            case 2:
                cout << "User ID: " << user->getID() << "\n";
                break;
            case 0:
                inSettings = false;
                break;
        }
    }
}

void userMenu(UniversityMember* user, vector<unique_ptr<UniversityMember>>& users) {
    bool active = true;
    while (active) {
        cout << "\n--- User Menu ---\n";
        cout << "1. Send Message\n2. View Inbox\n3. Settings\n0. Log out\n";
        int choice = getMenuChoice(0, 3);
        switch (choice) {
            case 1: {
                cout << "Enter recipient Name: ";
                string recipientName;
                getline(cin, recipientName);
                UniversityMember* recipient = findUserByName(users, recipientName);
                if (!recipient) {
                    cout << "User not found.\n";
                    break;
                }
                cout << "Send anonymously? (1 = Yes, 0 = No): ";
                int anonChoice = getMenuChoice(0, 1);
                cout << "Enter message: ";
                string message;
                getline(cin, message);
                if (anonChoice == 1) {
                    recipient->sendMessage(*recipient, message, true);
                } else {
                    user->sendMessage(*recipient, message, false);
                }
                cout << "Message sent.\n";
                break;
            }
            case 2: {
                string inboxStr = user->getInbox();
                if (inboxStr.empty()) {
                    cout << "Inbox is empty.\n";
                } else {
                    cout << inboxStr;
                }
                break;
            }
            case 3:
                settingsMenu(user);
                break;
            case 0:
                active = false;
                break;
        }
    }
}

void signIn(vector<unique_ptr<UniversityMember>>& users, Manager& manager) {
    bool signInActive = true;
    while (signInActive) {
        cout << "\n--- Sign In ---\n";
        cout << "1. Student\n2. Faculty\n3. Administration\n4. Manager\n0. Go Back\n";
        int role = getMenuChoice(0, 4);

        if (role == 0) break;

        if (role == 4) {
            cout << "Enter manager password: ";
            string password;
            getline(cin, password);
            if (password != "kitten") {
                cout << "Incorrect password. Access denied.\n";
                continue;
            }
            bool managerActive = true;
            while (managerActive) {
                cout << "\n--- Manager Menu ---\n";
                cout << "1. View All Users\n2. View Inbox\n3. View User Info\n4. Remove User\n0. Log out\n";
                int mChoice = getMenuChoice(0, 4);
                string targetName;
                switch (mChoice) {
                    case 1:
                        if (users.empty()) {
                            cout << "There are no users yet.\n";
                        } else {
                            manager.viewAllUsers(users);
                        }
                        break;
                    case 2:
                        cout << "Enter Name: ";
                        getline(cin, targetName);
                        if (!findUserByName(users, targetName)) {
                            cout << "User not found.\n";
                        } else if (findUserByName(users, targetName)->getRawInbox().empty()) {
                            cout << "Inbox is empty.\n";
                        } else {
                            manager.viewInbox(users, targetName);
                        }
                        break;
                    case 3:
                        cout << "Enter Name: ";
                        getline(cin, targetName);
                        if (!findUserByName(users, targetName)) {
                            cout << "User not found.\n";
                        } else {
                            manager.viewUserInfo(users, targetName);
                        }
                        break;
                    case 4:
                        cout << "Enter Name: ";
                        getline(cin, targetName);
                        if (!findUserByName(users, targetName)) {
                            cout << "This user does not exist.\n";
                        } else {
                            manager.removeUser(users, targetName);
                        }
                        break;
                    case 0:
                        managerActive = false;
                        break;
                }
            }
        } else {
            cout << "Enter your name (e.g., Elon Musk): ";
            string name;
            getline(cin, name);

            cout << "Enter your ID (e.g., AB1234): ";
            string id;
            getline(cin, id);

            UniversityMember* user = findUser(users, name, id);
            if (!user) {
                cout << "Invalid credentials. Try again.\n";
                continue;
            }
            userMenu(user, users);
        }
    }
}

int main() {
    vector<unique_ptr<UniversityMember>> users;
    Manager manager;
    bool running = true;

    loadUsers(users);

    while (running) {
        cout << "\n=== University Communication System ===\n";
        cout << "1. Sign In\n2. Sign Up\n0. Exit\n";
        int choice = getMenuChoice(0, 2);

        switch (choice) {
            case 1:
                signIn(users, manager);
                break;
            case 2:
                registerUser(users);
                break;
            case 0:
                running = false;
                cout << "Exiting...\n";
                break;
        }
    }

    saveUsers(users);

    return 0;
}
