#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <memory>
#include "UniversityMember.h"
using namespace std;

class Manager {
public:
    Manager();
    void viewAllUsers(const vector<unique_ptr<UniversityMember>>& users) const;
    void viewInbox(const vector<unique_ptr<UniversityMember>>& users, const string& name) const;
    void viewUserInfo(const vector<unique_ptr<UniversityMember>>& users, const string& name) const;
    void removeUser(vector<unique_ptr<UniversityMember>>& users, const string& name);
};

#endif //MANAGER_H