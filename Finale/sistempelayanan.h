#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <stack>
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
bool cariPasienBinary(const vector<T>& data, int idCari);

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
