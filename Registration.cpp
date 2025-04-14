#include "Registration.h"
#include "Student.h"
#include "Faculty.h"
#include "Administration.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <fstream>

using namespace std;

string generateUniqueID(const string& prefix, const vector<unique_ptr<UniversityMember>>& users) {
    string id;
    bool unique = false;

    while (!unique) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(1000, 9999);
        int number = distrib(gen);

        id = prefix + to_string(number);

        unique = all_of(users.begin(), users.end(), [&](const unique_ptr<UniversityMember>& user) {
            return user->getID() != id;
        });
    }
    return id;
}

void registerUser(vector<unique_ptr<UniversityMember>>& users) {
    int roleChoice;
    cout << "\n--- Register New User ---" << endl;
    cout << "1. Student" << endl;
    cout << "2. Faculty" << endl;
    cout << "3. Administration" << endl;
    cout << "0. Go Back" << endl;
    cout << "Select role to register: ";
    cin >> roleChoice;
    cin.ignore();

    if (roleChoice == 0) return;

    string name;
    cout << "Enter name (e.g., Elon Musk): ";
    getline(cin, name);

    string id;

    switch (roleChoice) {
        case 1:
            id = generateUniqueID("ST", users);
            users.push_back(make_unique<Student>(name, id));
            cout << "Student registered with ID: " << id << endl;
            break;
        case 2:
            id = generateUniqueID("FA", users);
            users.push_back(make_unique<Faculty>(name, id));
            cout << "Faculty registered with ID: " << id << endl;
            break;
        case 3:
            id = generateUniqueID("AD", users);
            users.push_back(make_unique<Administration>(name, id));
            cout << "Administration registered with ID: " << id << endl;
            break;
        default:
            cout << "Invalid option. Returning to menu." << endl;
    }
    const auto& user = users.back();
    ofstream out("../users.db", ios::app);
    if (out) {
        string role;
        if (dynamic_cast<Student*>(user.get())) role = "Student";
        else if (dynamic_cast<Faculty*>(user.get())) role = "Faculty";
        else if (dynamic_cast<Administration*>(user.get())) role = "Administration";

        out << "#ROLE: " << role << "\n";
        out << user->getName() << "\n";
        out << user->getID() << "\n";
        out << "0\n";
    } else {
        cerr << "Error appending user to users.db" << endl;
    }
}
