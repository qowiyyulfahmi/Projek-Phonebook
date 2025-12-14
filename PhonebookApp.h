#ifndef PHONEBOOKAPP_H
#define PHONEBOOKAPP_H

#include "User.h"     // Mengimpor kelas User untuk mengelola data pengguna.
#include <fstream>    // Digunakan untuk operasi file (membaca/menulis file).
#include <sstream>    // Digunakan untuk manipulasi string stream (misalnya parsing CSV).
#include <vector>     // Digunakan untuk menyimpan koleksi pengguna dan kontak.

// Definisi kelas PhonebookApp, mengelola keseluruhan logika aplikasi buku telepon.
class PhonebookApp {
private:
    vector<User> users;         // Daftar semua pengguna yang terdaftar dalam aplikasi.
    vector<Contact> allContacts; // Daftar semua kontak (opsional untuk pengelolaan global).
    User* currentUser;          // Pointer ke pengguna yang sedang aktif/log masuk.

public:
    // Konstruktor untuk menginisialisasi aplikasi buku telepon.
    PhonebookApp();

    // Metode untuk memuat data pengguna dari file.
    void loadUsers();

    // Metode untuk menyimpan data pengguna ke file.
    void saveUsers() const;

    // Metode untuk memuat data kontak dari file.
    void loadContacts();

    // Metode untuk menyimpan data kontak ke file.
    void saveContacts() const;

    // Metode untuk mencari pengguna berdasarkan username.
    User* findUser(const string& username);

    // Metode untuk memvalidasi data registrasi pengguna.
    bool validateRegistration(const string& username, const string& password);

    // Metode untuk meminta pengguna menyimpan perubahan data.
    void promptSaveChanges();

    // Metode untuk mendaftarkan pengguna baru.
    void registerUser();

    // Metode untuk login pengguna ke dalam aplikasi.
    void loginUser();

    // Metode untuk logout pengguna dari aplikasi.
    void logoutUser();

    // Metode untuk menyimpan semua data (pengguna dan kontak).
    void save();

    // Metode untuk memuat semua data (pengguna dan kontak).
    void load();

    // Metode utama untuk menjalankan aplikasi.
    void run();
};

#endif // PHONEBOOKAPP_H
