#include "Administration.h"

Administration::Administration(const std::string& name, const std::string& id) : UniversityMember(name, id) {}

string Administration::getID() const {
    return id;
}