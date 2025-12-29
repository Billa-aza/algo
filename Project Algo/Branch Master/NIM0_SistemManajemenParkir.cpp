#include <iostream>
#include <string>
using namespace std;

int main() {
    const int MAX = 100;
    string plat[MAX];
    string jenis[MAX];
    int jumlah = 0;
    int pilihan;

        do {
            cout << "\n==== Sistem Manajemen Parkir ===\n";
            cout << "1. Tambah Kendaraan Masuk\n";
            cout << "2. Tampilkan Semua Kendaraan\n";
            cout << "3. Cari Kendaraan (Filter 1 Kendaraan)\n";
            cout << "4. Total Kendaraan\n";
            cout << "5. Total Biaya Parkir\n";
            cout << "6. Keluar\n";
            cout << "Pilih Menu (1-6): ";
            cin >>  pilihan;

            switch (pilihan) {
                case 1:
                if (jumlah < MAX) {
                cout << "Masukka Plat Nomor: ";
                cin >> plat[jumlah];

                cout << "Jenis Kendaraan (Motor/Mobil): ";
                cin >> jenis[jumlah];

                jumlah++;
                cout << "Kendaraan Berhasil Ditambahkkan.\n";
        } else {
            cout << "Parkiran Penuh!\n";

        }
        break; 

        case 2:    
        if (jumlah == 0) {
            cout << "Belum Ada Kendaraan.\n";
        } else {
            cout << "\nDaftar Kendaraan Parkir:\n";
            cout << "_____________________________\n";
            for (int i = 0; i < jumlah; i++) {
            cout << i + 1 << ". Plat: " << plat[i]
                 << " | Jenis: " <<jenis[i] <<endl;

        }
            }
            break;

        case 3: {
            string cariPlat; 
            bool ditemukan = false; 

            cout << "Masukkan Plat Nomor yang dicari: ";
            cin >> cariPlat;

            for (int i = 0; i <jumlah; i++) {
                if (plat[i] == cariPlat) {
                    cout << "\nKendaraan ditemukan:\n";
                    cout << "Plat Nomor : " << plat[i] <<endl;
                    cout << "Jenis      : " << jenis[i] <<endl;
                    ditemukan = true;
                    break;
                }
            }
            
            if (!ditemukan) {
                cout << "Kendaraan Tidak Ditemukan.\n";

            }
            break;
        }   

        case 4: 
            cout << "Total Kendaraan Parkir: " <<jumlah <<endl;
            break;
        
        case 5: {
            int total = 0;
            for (int i = 0; i <jumlah; i++) {
                if (jenis[i] == "Motor" || jenis[i] == "motor") {
                    total += 2000;
                } else if (jenis[i] == "Mobil" || jenis[i] == "mobil") {
                    total += 5000;
                }
            }       
            cout << "Total Biaya Parkir: Rp " <<total <<endl;
            break;
        }
                
        case 6:     
            cout << "Terimakasih. Program Selesai.\n";
            break;

        default:
            cout << "Pilihan Tidak Valid!\n";
    }

        }while (pilihan != 6);

        return 0;
    
    }


