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
    void viewInbox(const vector<unique_ptr<UniversityMember>>& users, const string& id) const;
    void viewUserInfo(const vector<unique_ptr<UniversityMember>>& users, const string& id) const;
    void removeUser(vector<unique_ptr<UniversityMember>>& users, const string& id);
};

#endif //MANAGER_H