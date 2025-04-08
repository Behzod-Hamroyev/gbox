#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <string>
#include <memory>
#include <vector>
#include "UniversityMember.h"

std::string generateUniqueID(const std::string& prefix, const std::vector<std::unique_ptr<UniversityMember>>& users);
void registerUser(std::vector<std::unique_ptr<UniversityMember>>& users);

#endif //REGISTRATION_H
