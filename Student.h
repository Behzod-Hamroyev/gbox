#ifndef STUDENT_H
#define STUDENT_H

#include "UniversityMember.h"

class Student : public UniversityMember {
public:
    Student(const string& name, const string& id);
    std::string getID() const override;
};

#endif // STUDENT_H