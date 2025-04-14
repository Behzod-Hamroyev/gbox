#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <memory>
#include "UniversityMember.h"

void saveUsers(const std::vector<std::unique_ptr<UniversityMember>>& users);
void loadUsers(std::vector<std::unique_ptr<UniversityMember>>& users);
void appendMessageToFile(const string& recipientID, const Message& message);

#endif //DATABASE_H