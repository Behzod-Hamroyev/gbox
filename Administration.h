#ifndef ADMINISTRATION_H
#define ADMINISTRATION_H

#include "UniversityMember.h"

class Administration : public UniversityMember {
public:
    Administration(const string& name, const string& id);
    std::string getID() const override;
};

#endif // ADMINISTRATION_H