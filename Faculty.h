#ifndef FACULTY_H
#define FACULTY_H

#include "UniversityMember.h"

class Faculty : public UniversityMember {
private:
    int faculty_id;

public:
    Faculty(string name, int age, int faculty_id);

    int getFacultyID() const;
    void setFacultyID(int newID);
};

#endif // FACULTY_H
