#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <string>
#include <memory>
#include <vector>
#include "UniversityMember.h"

string generateUniqueID(const string& prefix, const vector<unique_ptr<UniversityMember>>& users);
void registerUser(vector<unique_ptr<UniversityMember>>& users);

#endif //REGISTRATION_H