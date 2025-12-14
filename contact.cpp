#include "Contact.h"

Contact::Contact(int userID, const string& name, const string& phoneNumber)
    : userID(userID), name(name), phoneNumber(phoneNumber) {}

string Contact::toCSV() const {
    return to_string(userID) + "," + name + "," + phoneNumber;
}
