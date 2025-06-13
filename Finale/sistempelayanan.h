#ifndef SISTEMPELAYANAN_H
#define SISTEMPELAYANAN_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <unistd.h> 

using namespace std;

struct Pasien {
    int id;
    char nama[50]; 
    int umur; 
    char keluhan[100]; 
};

template <typename T>
bool cariPasienBinary(const vector<T>& data, int idCari) {
    int kiri = 0;
    int kanan = data.size() - 1;

    while (kiri <= kanan) {
        int tengah = kiri + (kanan - kiri) / 2;

        if (data[tengah].id == idCari)
            return true;
        else if (data[tengah].id < idCari)
            kiri = tengah + 1;
        else
            kanan = tengah - 1;
    }

    return false;
}

class SistemPelayanan {
private:
    vector<Pasien> dataPasien;
    queue<Pasien> antrianPasien;
    stack<Pasien> riwayatPasien;

    int nextID = 1; 
    unordered_map<string, string> keluhanSaranMap;

public:
    SistemPelayanan();
    ~SistemPelayanan();

    void bacaLastID();
    void simpanLastID();
    void bacaKeluhanSaran();
    void bacaRiwayat();
    void simpanRiwayat();
    void daftar();
    void lihatAntrian();
    void prosesPasien();
    void riwayatPelayanan();
    void cariPasien();
    void editPasien();
    void hapusPasien();
    void statistikPuskes();
    bool validasiUmur(int umur);
    void clearScreen();
};

#endif
