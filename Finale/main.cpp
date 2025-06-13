#include "SistemPelayanan.h"
#include <unistd.h>

int main() {
    
    SistemPelayanan sistem;
    sistem.clearScreen();

    int pilihan;
    do {
        cout << "\n=== Menu Utama ===\n";
        cout << "1. Pendaftaran Pasien\n";
        cout << "2. Lihat Daftar Antrian\n";
        cout << "3. Proses Pasien\n";
        cout << "4. Riwayat Pelayanan\n";
        cout << "5. Cari Pasien\n";
        cout << "6. Edit Data Pasien\n";
        cout << "7. Hapus Data Pasien\n";
        cout << "8. Statistik Puskesmas\n";
        cout << "9. Keluar\n";
        cout << "Pilih opsi (1-9): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                sistem.daftar();
                break;
            case 2:
                sistem.lihatAntrian();
                break;
            case 3:
                sistem.prosesPasien();
                break;
            case 4:
                sistem.riwayatPelayanan();
                break;
            case 5:
                sistem.cariPasien();
                break;
            case 6:
                sistem.editPasien();
                break;
            case 7:
                sistem.hapusPasien();
                break;
            case 8:
                sistem.statistikPuskes();
                break;
            case 9:
                cout << "\nTerima kasih telah berkonsultasi!\n";
                break;
            default:
                cout << "\nOpsi tidak valid. Silakan pilih opsi yang tersedia.\n";
                break;
        }

    } while (pilihan != 9);

    return 0;
}
