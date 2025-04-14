#ifndef UNIVERSITY_MEMBER_H
#define UNIVERSITY_MEMBER_H

#include <vector>
#include <string>

using namespace std;

struct Message {
    string sender;
    string timestamp;
    string content;
};

class UniversityMember {
protected:
    string id;
    vector<Message> inbox;

public:
    string name;
    UniversityMember(const string& name, const string& id);
    virtual ~UniversityMember() = default;

    string getName() const;
    void setName(const string& newName);

    void sendMessage(UniversityMember& recipient, const string& content, bool anonymous = false);
    void receiveMessage(const Message& message);
    virtual string getInbox() const;
    const vector<Message>& getRawInbox() const;

    virtual string getID() const = 0;
};

#endif // UNIVERSITY_MEMBER_H