#ifndef USER_H
#define USER_H

// Guard header untuk mencegah multiple inclusions.
#include "Contact.h" // Mengimpor definisi kelas Contact, yang diperlukan oleh kelas User.
#include <vector>    // Digunakan untuk menyimpan koleksi kontak dalam bentuk vektor.
#include <string>    // Digunakan untuk representasi data string.
#include <iostream>  // Digunakan untuk fungsi input dan output.
#include <iomanip>   // Digunakan untuk manipulasi output.
#include <algorithm> // Digunakan untuk operasi algoritmik seperti pencarian atau pengurutan.

using namespace std; // Menyederhanakan akses ke anggota dari namespace std (tidak selalu disarankan di header).

// Definisi kelas User.
class User {
private:
    int id;              // ID unik pengguna.
    string username;     // Nama pengguna.
    string password;     // Kata sandi pengguna.

public:
    vector<Contact> contacts; // Koleksi kontak milik pengguna.

    // Konstruktor untuk menginisialisasi objek User dengan id, username, dan password.
    User(int id, const string& username, const string& password);

    // Getter untuk mendapatkan ID pengguna.
    int getID() const;

    // Getter untuk mendapatkan username pengguna.
    string getUsername() const;

    // Metode untuk mengotentikasi pengguna berdasarkan password yang diberikan.
    bool authenticate(const string& inputPassword) const;

    // Metode untuk memeriksa apakah kontak tertentu sudah ada berdasarkan nama dan nomor telepon.
    bool contactExists(const string& name, const string& phoneNumber) const;

    // Metode untuk menambahkan kontak baru ke daftar kontak.
    void addContact(const string& name, const string& phoneNumber);

    // Metode untuk menghapus kontak berdasarkan nama.
    void removeContact(const string& name);

    // Metode untuk mencetak daftar kontak pengguna ke output standar.
    void listContacts() const;

    // Metode untuk mengonversi data pengguna menjadi format CSV (Comma-Separated Values).
    string toCSV() const;
};

#endif // USER_H
