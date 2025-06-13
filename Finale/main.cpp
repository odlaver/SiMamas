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

        while (!(cin >> pilihan) || pilihan < 1 || pilihan > 9) {
            cout << "\nOpsi tidak valid.\n";
            cout << "Silakan pilih opsi yang tersedia (1-9): ";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (pilihan) {
            case 1:
                sistem.daftar();
                cout << "\nTunggu sebentar..";
                sleep(2);
                sistem.clearScreen();
                break;
            case 2:
                sistem.lihatAntrian();
                cout << "\nTunggu sebentar..";
                sleep(4);
                sistem.clearScreen();
                break;
            case 3:
                sistem.prosesPasien();
                cout << "\nPasien sedang diproses...";
                sleep(1);
                cout << "\nPasien telah diproses. Terima kasih telah menunggu.\n";
                sleep(2);
                sistem.clearScreen();
                break;
            case 4:
                sistem.riwayatPelayanan();
                cout << "\nTunggu sebentar..";
                sleep(4);
                sistem.clearScreen();
                break;
            case 5:
                sistem.cariPasien();
                sleep(2);
                sistem.clearScreen();
                break;
            case 6:
                sistem.editPasien();
                cout << "\nTunggu sebentar..";
                sleep(2);
                sistem.clearScreen();
                break;
            case 7:
                sistem.hapusPasien();
                cout << "\nTunggu sebentar..";
                sleep(2);
                sistem.clearScreen();
                break;
            case 8:
                sistem.statistikPuskes();
                sleep(4);
                sistem.clearScreen();
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
