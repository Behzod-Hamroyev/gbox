#ifndef UNIVERSITY_MEMBER_H
#define UNIVERSITY_MEMBER_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class UniversityMember {
protected:
    string name;
    int age;
    vector<string> inbox;

public:
    UniversityMember(string name, int age);

    string getName() const;
    void setName(const string& newName);

    int getAge() const;
    void setAge(int newAge);

    void sendMessage(UniversityMember& recipient, const string& message);
    void getMessages() const;
};

#endif // UNIVERSITY_MEMBER_H