#include <iostream>
#include <string>
using namespace std;

class AkunBank {
private:
    string nomorRekening;
    double saldo;
    string namaPemilik;

public:
    // Constructor untuk inisialisasi awal
    AkunBank(string nr, double s, string np) {
        nomorRekening = nr;
        saldo = s;
        namaPemilik = np;
    }

    // Setter untuk namaPemilik
    void setNamaPemilik(string nR, double S, string nP) {
        nomorRekening = nR;
        saldo = S;
        namaPemilik = nP;
    }

    // Method untuk menampilkan informasi akun
    void tampilkanInfo() {
        cout << "Informasi Akun Bank:" << endl;
        cout << "Nomor Rekening: " << nomorRekening << endl;
        cout << "Nama Pemilik: " << namaPemilik << endl;
        cout << "Saldo: Rp" << saldo << endl;
    }
};

int main() {
    // Membuat objek akun dengan constructor
    AkunBank akun1("1234567890", 2000000, "sekar tarji");

    // Mengubah nama pemilik menggunakan setter
    akun1.setNamaPemilik("9876543210", 1000000, "tek ringting");

    // Menampilkan informasi akun
    akun1.tampilkanInfo();

    return 0;
}
