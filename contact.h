#ifndef CONTACT_H
#define CONTACT_H

// Guard header untuk mencegah multiple inclusions.
#include <string> // Digunakan untuk representasi data string.

using namespace std; // Menyederhanakan akses ke anggota dari namespace std (tidak disarankan di file header).

// Definisi kelas Contact, merepresentasikan sebuah kontak individu.
class Contact {
public:
    int userID;           // ID pengguna pemilik kontak ini.
    string name;          // Nama kontak.
    string phoneNumber;   // Nomor telepon kontak.

    // Konstruktor untuk menginisialisasi objek Contact dengan ID pengguna, nama, dan nomor telepon.
    Contact(int userID, const string& name, const string& phoneNumber);

    // Metode untuk mengonversi data kontak menjadi format CSV (Comma-Separated Values).
    string toCSV() const;
};

#endif // CONTACT_H
