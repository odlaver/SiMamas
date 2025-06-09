#include <iostream>             // buat input-output standar (cout, cin)
#include <iomanip>              // buat format tampilan seperti spacing, dll
#include <vector>               // buat nyimpen banyak data pasien dalam satu tempat (seprti array)
#include <queue>                // buat antrian (FIFO)
#include <unordered_map>        // untuk menyimpan keluhan dan saran dengan pencocokan yang cepat
#include <stack>                // buat riwayat (LIFO)
#include <fstream>              // buat nyimpen dan membaca data dari file
#include <cstring>              // buat fungsi-fungsi manipulasi string seperti strcpy, strlen
#include <algorithm>            // buat fungsi pencarian dan pengurutan (misalnya binary search)
#include <unistd.h>             // buat ngasih delay antar fungsi

using namespace std;

struct Pasien {
    int id;
    char nama[50]; 
    int umur; 
    char keluhan[100]; 
};

class SistemPelayanan {
private:
    vector<Pasien> dataPasien;
    queue<Pasien> antrianPasien;
    stack<Pasien> riwayatPasien;

    int nextID;
    unordered_map<string, string> keluhanSaranMap;

public:
    SistemPelayanan() {
        nextID = 1; 
        bacaKeluhanSaran();
        bacaData();  
    }

    ~SistemPelayanan() {
        simpanData(); 
    }

    void clearScreen() {
        #ifdef _WIN32
        system("cls"); 
        #endif
    }
