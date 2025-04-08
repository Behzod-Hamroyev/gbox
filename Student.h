#ifndef STUDENT_H
#define STUDENT_H

#include "UniversityMember.h"

class Student : public UniversityMember {
private:
    int student_id;

public:
    Student(string name, int age, int student_id);

    int getStudentID() const;
    void setStudentID(int newID);
};

#endif // STUDENT_H
