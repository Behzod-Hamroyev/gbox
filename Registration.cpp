#include "Registration.h"

#include "Registration.h"
#include "Student.h"
#include "Faculty.h"
#include "Administration.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

string generateUniqueID(const string& prefix, const vector<unique_ptr<UniversityMember>>& users) {
    string id;
    bool unique = false;

    while (!unique) {
        int number = rand() % 9000 + 1000; // 4-digit random number
        id = prefix + to_string(number);

        unique = all_of(users.begin(), users.end(), [&](const unique_ptr<UniversityMember>& user) {
            return user->getID() != id;
        });
    }
    return id;
}

void registerUser(vector<unique_ptr<UniversityMember>>& users) {
    string role;
    cout << "Enter role (student/faculty/administration): ";
    cin >> role;
    cin.ignore();

    string name;
    cout << "Enter name: ";
    getline(cin, name);

    if (role == "student") {
        string id = generateUniqueID("ST", users);
        users.push_back(make_unique<Student>(name, id));
        cout << "Student registered with ID: " << id << endl;
    } else if (role == "faculty") {
        string id = generateUniqueID("FA", users);
        users.push_back(make_unique<Faculty>(name, id));
        cout << "Faculty registered with ID: " << id << endl;
    } else if (role == "administration") {
        string id = generateUniqueID("AD", users);
        users.push_back(make_unique<Administration>(name, id));
        cout << "Administration registered with ID: " << id << endl;
    } else {
        cout << "Invalid role entered." << endl;
    }
}
