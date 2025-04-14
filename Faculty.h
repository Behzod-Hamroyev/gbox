#ifndef FACULTY_H
#define FACULTY_H

#include "UniversityMember.h"

class Faculty : public UniversityMember {
public:
    Faculty(const std::string& name, const std::string& id);
    std::string getID() const override;
};

#endif // FACULTY_H