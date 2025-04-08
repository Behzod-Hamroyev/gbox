#include "Administration.h"

Administration::Administration(string name, int age, int admin_id)
    : UniversityMember(name, age), admin_id(admin_id) {}

int Administration::getAdminID() const { return admin_id; }
void Administration::setAdminID(int newID) { admin_id = newID; }
