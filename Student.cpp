#include "Student.h"

Student::Student(const std::string& name, const std::string& id) : UniversityMember(name, id) {}

std::string Student::getID() const {
    return id;
}