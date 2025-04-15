#ifndef UNIVERSITYMEMBER_H
#define UNIVERSITYMEMBER_H

#include <string>
#include <vector>

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

    virtual string getID() const = 0;

    void sendMessage(UniversityMember& recipient, const string& content, bool anonymous) const;
    void receiveMessage(const Message& msg);

    string getInbox() const;
    const vector<Message>& getRawInbox() const;
};

#endif // UNIVERSITYMEMBER_H
