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

    ofstream file("riwayat_pasien.txt", ios::app);
    file << p.id << "\n";
    file << p.nama << "\n";
    file << p.umur << "\n";
    file << p.keluhan << "\n";
    file.close();
}


void SistemPelayanan::riwayatPelayanan() {
    clearScreen();
    ifstream file("riwayat_pasien.txt");

    if (!file) {
        cout << "\nTidak ada riwayat pasien yang tersimpan.\n";
        return;
    }

    Pasien p;
    cout << "\n=== Riwayat Pelayanan Pasien ===\n";

    while (file >> p.id) {
        file.ignore();
        file.getline(p.nama, 50);
        file >> p.umur;
        file.ignore();
        file.getline(p.keluhan, 100);

        cout << "\nID: " << p.id << "\n";
        cout << "Nama: " << p.nama << "\n";
        cout << "Umur: " << p.umur << " tahun\n";
        cout << "Keluhan: " << p.keluhan << "\n";
        cout << "------------------------------------\n";
    }

    file.close();
}


void SistemPelayanan::cariPasien() {
    clearScreen();
    int id;
    cout << "\nMasukkan ID pasien yang ingin dicari: ";
    cin >> id;

    bool ditemukan = false;
    ifstream file("riwayat_pasien.txt");

    if (!file) {
        cout << "\nGagal membuka file riwayat_pasien.txt\n";
        return;
    }

    Pasien p;
    while (file >> p.id) {
        file.ignore(); 
        file.getline(p.nama, 50);
        file >> p.umur;
        file.ignore();
        file.getline(p.keluhan, 100);

        if (p.id == id) {
            ditemukan = true;
            cout << "\n=== Data Pasien Ditemukan ===\n";
            cout << "ID: " << p.id << "\n";
            cout << "Nama: " << p.nama << "\n";
            cout << "Umur: " << p.umur << " tahun\n";
            cout << "Keluhan: " << p.keluhan << "\n";
            break;
        }
    }

    if (!ditemukan) {
        cout << "\nPasien dengan ID " << id << " tidak ditemukan dalam riwayat.\n";
    }

    file.close();
}

    void SistemPelayanan::editPasien() {
        clearScreen();

        int id;
        cout << "\n=== Edit Data Pasien ===\n";
        cout << "Masukkan ID pasien yang ingin diedit: ";
        cin >> id;

        bool ditemukan = false;
        ifstream file("riwayat_pasien.txt");
        ofstream tempFile("temp_riwayat_pasien.txt", ios::app);

        if (!file) {
            cout << "\nGagal membuka file riwayat_pasien.txt\n";
            return;
        }

        Pasien p;
        while (file >> p.id) {
            file.ignore();
            file.getline(p.nama, 50);
            file >> p.umur;
            file.ignore();
            file.getline(p.keluhan, 100);

            if (p.id == id) {
                ditemukan = true;
                cout << "\nData ditemukan. Masukkan data baru:\n";

                cin.ignore();

                cout << "Nama baru: ";
                cin.getline(p.nama, 50);
            }
            tempFile << p.id << "\n";
            tempFile << p.nama << "\n";
            tempFile << p.umur << "\n";
            tempFile << p.keluhan << "\n";
        }

        file.close();
        tempFile.close();

        remove("riwayat_pasien.txt");
        rename("temp_riwayat_pasien.txt", "riwayat_pasien.txt");

        if (!ditemukan) {
            cout << "\nPasien dengan ID " << id << " tidak ditemukan.\n";
        } else {
            cout << "\nData pasien berhasil diperbarui.\n";
        }
    }


void SistemPelayanan::hapusPasien() {
    clearScreen();

    int id;
    cout << "\n=== Hapus Data Pasien ===\n";
    cout << "Masukkan ID pasien yang mau dihapus: ";
    cin >> id;

    bool ditemukan = false;
    ifstream file("riwayat_pasien.txt");
    ofstream tempFile("temp_riwayat_pasien.txt", ios::app); 

    if (!file) {
        cout << "\nGagal membuka file riwayat_pasien.txt\n";
        return;
    }

    Pasien p;
    while (file >> p.id) {
        file.ignore(); 
        file.getline(p.nama, 50);
        file >> p.umur;
        file.ignore();
        file.getline(p.keluhan, 100);

        if (p.id == id) {
            ditemukan = true;
            cout << "\nPasien ditemukan:\n";
            cout << "ID: " << p.id << ", Nama: " << p.nama << "\n";
            char konfirmasi;
            cout << "Yakin ingin menghapus pasien ini? (y/n): ";
            cin >> konfirmasi;

            if (konfirmasi == 'y' || konfirmasi == 'Y') {
                cout << "Data pasien berhasil dihapus.\n";
                continue;  
            } else {
                tempFile << p.id << "\n";
                tempFile << p.nama << "\n";
                tempFile << p.umur << "\n";
                tempFile << p.keluhan << "\n";
            }
        } else {
            tempFile << p.id << "\n";
            tempFile << p.nama << "\n";
            tempFile << p.umur << "\n";
            tempFile << p.keluhan << "\n";
        }
    }

    file.close();
    tempFile.close();

    if (!ditemukan) {
        cout << "\nPasien dengan ID " << id << " tidak ditemukan.\n";
    } else {
        remove("riwayat_pasien.txt"); 
        rename("temp_riwayat_pasien.txt", "riwayat_pasien.txt");
    }
}

void SistemPelayanan::statistikPuskes() {
    clearScreen();
    ifstream file("riwayat_pasien.txt");

    if (!file) {
        cout << "\nBelum ada pasien terdaftar.\n";
        return;
    }

    int totalUmur = 0;
    int termuda = 120;
    int jumlahPasien = 0;

    Pasien p;
    while (file >> p.id) {
        file.ignore();
        file.getline(p.nama, 50);
        file >> p.umur;
        file.ignore(); 
        file.getline(p.keluhan, 100);

        totalUmur += p.umur;
        if (p.umur < termuda) {
            termuda = p.umur;
        }
        jumlahPasien++;
    }

    file.close();

    if (jumlahPasien == 0) {
        cout << "\nTidak ada pasien yang diproses.\n";
        return;
    }

    int rataRataUmur = totalUmur / jumlahPasien;
    cout << "\n=== Statistik Puskesmas ===\n";
    cout << "Jumlah pasien terdaftar: " << jumlahPasien << "\n";
    cout << "Rata-rata umur pasien: " << fixed << setprecision(2) << rataRataUmur << " tahun\n";
    cout << "Pasien termuda: " << termuda << " tahun\n";
}


bool SistemPelayanan::validasiUmur(int umur) {
    if (umur < 0 || umur > 120) {
        return false;
    }
    return true;
}

void SistemPelayanan::clearScreen() {
    #ifdef _WIN32
    system("cls"); 
    #endif
}
