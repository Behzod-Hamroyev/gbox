#include "Faculty.h"

Faculty::Faculty(const std::string& name, const std::string& id) : UniversityMember(name, id) {}

std::string Faculty::getID() const {
    return id;
}