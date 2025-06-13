#include "sistempelayanan.h"
#include <iomanip>

SistemPelayanan::SistemPelayanan() {
    bacaLastID();
    bacaKeluhanSaran();
    bacaRiwayat();
}

SistemPelayanan::~SistemPelayanan() {
    simpanRiwayat();
    simpanLastID();
}

void SistemPelayanan::bacaLastID() {
    ifstream file("last_id.txt");
    if (file) {
        file >> nextID; 
    } else {
        nextID = 1;
    }
    file.close();
}

void SistemPelayanan::simpanLastID() {
    ofstream file("last_id.txt");
    file << nextID;
    file.close();
}

void SistemPelayanan::bacaKeluhanSaran() {
    ifstream file("keluhan_saran.txt");
    if (!file) {
        cout << "\nGagal membuka file keluhan_saran.txt\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        size_t pos = line.find("|");
        if (pos != string::npos) {
            string keluhan = line.substr(0, pos);
            string saran = line.substr(pos + 1);
            transform(keluhan.begin(), keluhan.end(), keluhan.begin(), ::tolower);
            keluhanSaranMap[keluhan] = saran;
        }
    }
    file.close();
}

void SistemPelayanan::bacaRiwayat() {
    ifstream file("riwayat_pasien.txt");

    Pasien p;
    while (file >> p.id) {
        file.ignore();
        file.getline(p.nama, 50);
        file >> p.umur;
        file.ignore();
        file.getline(p.keluhan, 100);

        riwayatPasien.push(p);
    }
    file.close();
}

void SistemPelayanan::simpanRiwayat() {
    ofstream file("riwayat_pasien.txt", ios::app);
    while (!riwayatPasien.empty()) {
        Pasien p = riwayatPasien.top();
        riwayatPasien.pop();
        file << p.id << "\n";
        file << p.nama << "\n";
        file << p.umur << "\n";
        file << p.keluhan << "\n";
    }
    file.close();
}
