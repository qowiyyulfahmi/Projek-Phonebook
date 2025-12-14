#include "User.h"

User::User(int id, const string& username, const string& password)
    : id(id), username(username), password(password) {}

int User::getID() const { return id; }
string User::getUsername() const { return username; }
bool User::authenticate(const string& inputPassword) const { return password == inputPassword; }

bool User::contactExists(const string& name, const string& phoneNumber) const {
    return any_of(contacts.begin(), contacts.end(), [&](const Contact& c) {
        return c.name == name && c.phoneNumber == phoneNumber;
    });
}

void User::addContact(const string& name, const string& phoneNumber) {
    auto it = find_if(contacts.begin(), contacts.end(), [&](const Contact& c) {
        return c.name == name || c.phoneNumber == phoneNumber;
    });

    if (it != contacts.end()) {
        cout << "Contact addition failed: Name or phone number already exists.\n";
    } else {
        contacts.emplace_back(id, name, phoneNumber);
        cout << "Contact added successfully!\n";
    }
}

void User::removeContact(const string& name) {
    auto it = remove_if(contacts.begin(), contacts.end(),
                        [&name](const Contact& c) { return c.name == name; });
    if (it != contacts.end()) {
        contacts.erase(it, contacts.end());
        cout << "Contact removed successfully!\n";
    } else {
        cout << "Contact not found.\n";
    }
}

void User::listContacts() const {
    if (contacts.empty()) {
        cout << "No contacts to display.\n";
        return;
    }
    cout << setw(20) << left << "Name" << setw(15) << "Phone Number\n";
    cout << string(35, '-') << '\n';
    for (const auto& contact : contacts) {
        cout << setw(20) << left << contact.name << setw(15) << contact.phoneNumber << '\n';
    }
}

string User::toCSV() const {
    return to_string(id) + "," + username + "," + password;
}
