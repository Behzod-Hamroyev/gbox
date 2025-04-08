#include "Student.h"

Student::Student(string name, int age, int student_id)
    : UniversityMember(name, age), student_id(student_id) {}

int Student::getStudentID() const { return student_id; }
void Student::setStudentID(int newID) { student_id = newID; }
