#include "PhonebookApp.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

PhonebookApp::PhonebookApp() : currentUser(nullptr) {
    loadUsers();
}

void PhonebookApp::loadUsers() {
    users.clear();
    ifstream inFile("users.csv");
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        int id;
        string username, password;
        ss >> id;
        ss.ignore(1); // Skip comma
        getline(ss, username, ',');
        getline(ss, password, ',');
        if (!username.empty() && !password.empty()) {
            users.emplace_back(id, username, password);
        }
    }
    inFile.close();
}

void PhonebookApp::saveUsers() const {
    ofstream outFile("users.csv");
    for (const auto& user : users) {
        outFile << user.toCSV() << '\n';
    }
    outFile.close();
}

void PhonebookApp::loadContacts() {
    allContacts.clear();
    ifstream inFile("contacts.csv");
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        int userID;
        string name, phoneNumber;
        ss >> userID;
        ss.ignore(1); // Skip comma
        getline(ss, name, ',');
        getline(ss, phoneNumber, ',');
        if (!name.empty() && !phoneNumber.empty()) {
            allContacts.emplace_back(userID, name, phoneNumber);
        }
    }
    inFile.close();

    if (currentUser) {
        currentUser->contacts.clear();
        for (const auto& contact : allContacts) {
            if (contact.userID == currentUser->getID()) {
                currentUser->contacts.push_back(contact);
            }
        }
    }
}

void PhonebookApp::saveContacts() const {
    ofstream outFile("contacts.csv");
    for (const auto& contact : allContacts) {
        outFile << contact.toCSV() << '\n';
    }
    outFile.close();
}

User* PhonebookApp::findUser(const string& username) {
    for (auto& user : users) {
        if (user.getUsername() == username) {
            return &user;
        }
    }
    return nullptr;
}

bool PhonebookApp::validateRegistration(const string& username, const string& password) {
    if (username.empty() || password.empty()) {
        cout << "Username or password cannot be empty.\n";
        return false;
    }

    if (findUser(username)) {
        cout << "Username already exists. Please choose another one.\n";
        return false;
    }

    return true;
}

void PhonebookApp::promptSaveChanges() {
    char choice;
    cout << "Do you want to save changes? (y/n): ";
    cin >> choice;
    if (tolower(choice) == 'y') {
        saveContacts();
        cout << "Changes saved successfully!\n";
    }
}

void PhonebookApp::registerUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (validateRegistration(username, password)) {
        int newID = users.size();
        users.emplace_back(newID, username, password);
        saveUsers();
        cout << "User registered successfully with ID: " << newID << '\n';
    }
}

void PhonebookApp::loginUser() {
    loadContacts();
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    User* user = findUser(username);
    if (user && user->authenticate(password)) {
        currentUser = user;
        currentUser->contacts.clear();
        for (const auto& contact : allContacts) {
            if (contact.userID == currentUser->getID()) {
                currentUser->contacts.push_back(contact);
            }
        }
        cout << "Logged in successfully!\n";
    } else {
        cout << "Invalid username or password.\n";
    }
}

void PhonebookApp::logoutUser() {
    if (currentUser) {
        currentUser = nullptr;
        cout << "Logged out successfully!\n";
    } else {
        cout << "No user is currently logged in.\n";
    }
}

void PhonebookApp::save() {
    if (currentUser) {
        saveContacts();
        cout << "Contacts saved successfully!\n";
    } else {
        cout << "Please login to save your contacts.\n";
    }
}

void PhonebookApp::load() {
    if (currentUser) {
        loadContacts();
        cout << "Data loaded successfully!\n";
    } else {
        cout << "No user is currently logged in.\n";
    }
}

// INI ADALAH FUNGSI RUN YANG BARU
void PhonebookApp::run() {
    int choice;
    while (true) { 
        // KONDISI 1: BELUM LOGIN (Menu Terbatas)
        if (currentUser == nullptr) {
            cout << "\n=== MENU UTAMA ===\n";
            cout << "1. Register User\n";
            cout << "2. Login\n";
            cout << "3. Keluar Aplikasi (Exit)\n";
            cout << "Masukkan pilihan: ";
            cin >> choice;

            switch (choice) {
                case 1: registerUser(); break;
                case 2: loginUser(); break;
                case 3: 
                    cout << "Terima kasih telah menggunakan aplikasi ini.\n";
                    return; 
                default: cout << "Pilihan tidak valid.\n";
            }
        } 
        // KONDISI 2: SUDAH LOGIN (Menu Lengkap)
        else {
            cout << "\n=== DASHBOARD USER: " << currentUser->getUsername() << " ===\n";
            cout << "1. Add Contact\n";
            cout << "2. Remove Contact\n";
            cout << "3. List Contacts\n";
            cout << "4. Save Data\n";
            cout << "5. Load Data\n";
            cout << "6. Logout\n";
            cout << "Masukkan pilihan: ";
            cin >> choice;

            switch (choice) {
                case 1: { // Add
                    string name, phone;
                    cout << "Enter name: "; cin >> name;
                    cout << "Enter phone number: "; cin >> phone;
                    size_t initialSize = currentUser->contacts.size();
                    currentUser->addContact(name, phone);
                    if (currentUser->contacts.size() > initialSize) {
                        allContacts.emplace_back(currentUser->getID(), name, phone);
                        promptSaveChanges();
                    }
                    break;
                }
                case 2: { // Remove
                    string name;
                    cout << "Enter name to remove: "; cin >> name;
                    size_t initialSize = currentUser->contacts.size();
                    currentUser->removeContact(name);
                    if (currentUser->contacts.size() < initialSize) {
                        allContacts.erase(remove_if(allContacts.begin(), allContacts.end(),
                            [&](const Contact& c) { return c.userID == currentUser->getID() && c.name == name; }), allContacts.end());
                        promptSaveChanges();
                    }
                    break;
                }
                case 3: currentUser->listContacts(); break;
                case 4: save(); break;
                case 5: load(); break;
                case 6: logoutUser(); break;
                default: cout << "Pilihan tidak valid.\n";
            }
        }
    }
}