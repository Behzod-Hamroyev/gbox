#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <memory>
#include "UniversityMember.h"

void saveUsers(const vector<unique_ptr<UniversityMember>>& users);
void loadUsers(vector<unique_ptr<UniversityMember>>& users);

#endif //DATABASE_H