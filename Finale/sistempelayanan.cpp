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

