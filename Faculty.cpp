#include "Faculty.h"

Faculty::Faculty(string name, int age, int faculty_id)
    : UniversityMember(name, age), faculty_id(faculty_id) {}

int Faculty::getFacultyID() const { return faculty_id; }
void Faculty::setFacultyID(int newID) { faculty_id = newID; }
