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

void SistemPelayanan::daftar() {
    clearScreen();
    Pasien p;
    p.id = nextID++;

    cout << "\n=== Formulir Pendaftaran Pasien ===\n";

    cout << "Namanya siapa: ";
    cin.ignore();
    while (true) {
        cin.getline(p.nama, 50);
        if (strlen(p.nama) > 0) break;
        cout << "Nama tidak boleh kosong. Coba lagi: ";
    }

    cout << "Umurnya berapa: ";
    while (true) {
        cin >> p.umur;
        if (validasiUmur(p.umur)) break;
        cout << "Umur tidak valid. Masukkan umur yang lebih jelas: ";
    }

    cin.ignore();

    cout << "Keluhannya apa: ";
    cin.getline(p.keluhan, 100);

    dataPasien.push_back(p);
    antrianPasien.push(p);

    cout << "\nPendaftaran berhasil, silakan menunggu sampai antrian kamu dipanggil untuk diproses...\n";
}

void SistemPelayanan::lihatAntrian() {
    clearScreen();
    if (antrianPasien.empty()) {
        cout << "\nAntrian kosong.\n";
        return;
    }

    cout << "\n=== Daftar Antrian Pasien ===\n";
    queue<Pasien> temp = antrianPasien;
    while (!temp.empty()) {
        Pasien p = temp.front();
        temp.pop();
        cout << "ID: " << p.id << ", Nama: " << p.nama << ", Umur: " << p.umur << ", Keluhan: " << p.keluhan << ".\n";
    }
}

void SistemPelayanan::prosesPasien() {
    clearScreen();
    if (antrianPasien.empty()) {
        cout << "\nTidak ada pasien dalam antrian.\n";
        return;
    }

    Pasien p = antrianPasien.front();
    antrianPasien.pop();

    cout << "\n=== Memproses Pasien ===\n";
    cout << "ID: " << p.id << "\n";
    cout << "Nama: " << p.nama << "\n";
    cout << "Umur: " << p.umur << " tahun\n";
    cout << "Keluhan: " << p.keluhan << "\n";

    string keluhanPasien(p.keluhan);
    transform(keluhanPasien.begin(), keluhanPasien.end(), keluhanPasien.begin(), ::tolower);

    if (keluhanSaranMap.find(keluhanPasien) != keluhanSaranMap.end()) {
        cout << "Saran Pengobatan: " << keluhanSaranMap[keluhanPasien] << "\n";
    } else {
        cout << "Kami sarankan untuk segera ke rumah sakit untuk penanganan keluhan ini.\n";
    }

    riwayatPasien.push(p);
    simpanRiwayat();
}

void SistemPelayanan::riwayatPelayanan() {
    clearScreen();
    bacaRiwayat();
    unordered_set<int> riwayatSet;
    if (riwayatPasien.empty()) {
        cout << "\nTidak ada pasien yang telah diproses.\n";
        return;
    }

    cout << "\n=== Riwayat Pelayanan Pasien ===\n";

    stack<Pasien> temp = riwayatPasien;
    
    while (!temp.empty()) {
        Pasien p = temp.top();
        temp.pop();

        if (riwayatSet.find(p.id) == riwayatSet.end()) {
            riwayatSet.insert(p.id);
            cout << "\nID: " << p.id << "\n";
            cout << "Nama: " << p.nama << "\n";
            cout << "Umur: " << p.umur << " tahun\n";
            cout << "Keluhan: " << p.keluhan << "\n";
            cout << "Status: Sudah Diproses\n";
            cout << "=====================================\n";
        }
    }
}

void SistemPelayanan::cariPasien() {
    clearScreen();
    int id;
    cout << "\nMasukkan ID pasien yang ingin dicari: ";
    cin >> id;

    sort(dataPasien.begin(), dataPasien.end(), [](const Pasien& a, const Pasien& b) {
        return a.id < b.id;
    });

    if (cariPasienBinary(dataPasien, id)) {
        cout << "\n=== Data Pasien Ditemukan ===\n";
        for (const auto& p : dataPasien) {
            if (p.id == id) {
                cout << "ID: " << p.id << "\n";
                cout << "Nama: " << p.nama << "\n";
                cout << "Umur: " << p.umur << " tahun\n";
                cout << "Keluhan: " << p.keluhan << "\n";
                break;
            }
        }
    } else {
        cout << "\nPasien dengan ID " << id << " tidak ditemukan.\n";
    }
}
