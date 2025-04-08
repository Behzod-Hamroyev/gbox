#ifndef ADMINISTRATION_H
#define ADMINISTRATION_H

#include "UniversityMember.h"

class Administration : public UniversityMember {
private:
    int admin_id;

public:
    Administration(string name, int age, int admin_id);

    int getAdminID() const;
    void setAdminID(int newID);
};

#endif // ADMINISTRATION_H