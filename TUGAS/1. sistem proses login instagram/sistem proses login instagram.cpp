#include <iostream>
#include <string>
using namespace std;

class LoginInstagram {
private:

    string VUsername; // Menyimpan username yang valid
    string VPassword; // Menyimpan password yang valid

public:
    // Constructor untuk inisialisasi username dan password
    LoginInstagram(string username, string password) {
        VUsername = username;
        VPassword = password;
    }

    // Cara untuk mengecek login
    void CekLogin(string username, string password) {
        if (username == VUsername && password == VPassword) {
            cout << "\nLogin berhasil! Menuju ke homepage Instagram..." << endl;
            exit(0); // Keluar dari program setelah login berhasil
        } else {
            cout << "\nData tidak valid!" << endl;
            LupaPassword(); // Panggil lupa password
        }
    }

    // Cara untuk menangani lupa password
    void LupaPassword() {
        char choice;
        cout << "Lupa password? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            string NewPassword;
            while (true) {
                cout << "\nMasukkan password baru: ";
                cin >> NewPassword;

                // Validasi: password baru tidak boleh sama dengan password lama
                if (NewPassword == VPassword) {
                    cout << "Error: Password baru tidak boleh sama dengan password sebelumnya. Silakan coba lagi." << endl;
                } else {
                    SetPassword(NewPassword); // Update password
                    cout << "Password berhasil diperbarui. Silakan login kembali." << endl;
                    break; // Keluar dari loop setelah password berhasil diupdate
                }
            }
        } else {
            cout << "Silakan coba login kembali." << endl;
        }
    }

    // Method untuk mengupdate password
    void SetPassword(string NewPassword) {
        VPassword = NewPassword;
    }
};

int main() {
    // Inisialisasi sistem login dengan username dan password default
    LoginInstagram SistemLogin("dafi", "123");

    string username, password;

    cout << "=== Sistem Login Instagram ===" << endl;

    // Loop untuk proses login
    while (true) {
        cout << "\nUsername/Email: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        // Panggil method checkLogin dari class
        SistemLogin.CekLogin(username, password);
    }

    return 0;
}
