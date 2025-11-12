#include <iostream> 
using namespace std;

struct Qnode {       // Mendefinisikan struktur node untuk queue
    int data;        // Variabel untuk menyimpan data/integer
    Qnode* next;     // Pointer ke node berikutnya dalam queue
};

struct List {        // Struktur untuk mengelola queue
    Qnode* front;    // Pointer ke node paling depan (pertama) dalam queue
    Qnode* rear;     // Pointer ke node paling belakang (terakhir) dalam queue
    int total_data;  // Variabel untuk menghitung jumlah data dalam queue
};

int maks = 4;        // Batas maksimal data yang bisa diantri (kapasitas queue)
int pilihan;         // Variabel untuk menyimpan pilihan menu user
int nama, target;    // Variabel untuk input data (nama) dan target operasi
List queue = {nullptr, nullptr, 0}; // Inisialisasi queue kosong

// Fungsi untuk mengecek apakah queue kosong
bool IsEmpty() {
    return queue.front == nullptr; // Kembalikan true jika front null (tidak ada node)
}

// Fungsi untuk mengecek apakah queue penuh
bool IsFull() {
    return queue.total_data >= maks; // Kembalikan true jika jumlah data >= kapasitas maks
}

// Fungsi untuk menambahkan data ke belakang queue
void Enqueue(int data) {
    if (IsFull()) {  // Cek jika queue penuh
        cout << "Queue penuh! Maks: " << maks << " data\n";
        return;      // Keluar dari fungsi jika penuh
    }

    Qnode* newNode = new Qnode{data, nullptr}; // Buat node baru dengan data dan next null

    if (IsEmpty()) {  // Jika queue kosong
        queue.front = queue.rear = newNode; // Front dan rear menunjuk ke node baru
    } else {          // Jika queue tidak kosong
        queue.rear->next = newNode; // Node terakhir menunjuk ke node baru
        queue.rear = newNode;       // Node baru menjadi rear (terakhir)
    }

    queue.total_data++; // Tambah jumlah data dalam queue
    cout << "Enqueued: " << data << endl; // Tampilkan pesan sukses
}

// Fungsi untuk menyisipkan data setelah node tertentu
void insertAfter(int data, int nama) {
    if (IsEmpty()) {  // Cek jika queue kosong
        cout << "Queue kosong!\n";
        return;
    }

    if (IsFull()) {  // Cek jika queue penuh
        cout << "Queue penuh! Maks: " << maks << " data\n";
        return;
    }

    Qnode* current = queue.front; // Mulai dari node depan
    while (current != nullptr && current->data != data) { // Cari node dengan data yang sesuai
        current = current->next;
    }

    if (current == nullptr) {  // Jika tidak ditemukan
        cout << "Target tidak ditemukan!\n";
        return;
    }

    Qnode* newNode = new Qnode{nama, current->next}; // Buat node baru
    current->next = newNode; // Sisipkan node baru setelah current

    if (current == queue.rear) { // Jika current adalah node terakhir
        queue.rear = newNode;   // Maka node baru menjadi node terakhir
    }

    queue.total_data++; // Tambah jumlah data
}

// Fungsi untuk menyisipkan data sebelum node tertentu
void insertBefore(int data, int nama) {
    if (IsEmpty()) {  // Cek jika queue kosong
        cout << "Queue kosong!\n";
        return;
    }

    if (IsFull()) {  // Cek jika queue penuh
        cout << "Queue penuh! Maks: " << maks << " data\n";
        return;
    }

    Qnode* current = queue.front; // Mulai dari node depan
    Qnode* prev = nullptr;       // Pointer untuk node sebelumnya

    while (current != nullptr && current->data != data) { // Cari node dengan data yang sesuai
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {  // Jika tidak ditemukan
        cout << "Target tidak ditemukan!\n";
        return;
    }

    Qnode* newNode = new Qnode{nama, current}; // Buat node baru menunjuk ke current

    if (prev == nullptr) { // Jika ingin menyisipkan sebelum node pertama
        queue.front = newNode; // Node baru menjadi node pertama
    } else {
        prev->next = newNode; // Node sebelumnya menunjuk ke node baru
    }

    queue.total_data++; // Tambah jumlah data
}

// Fungsi untuk menghapus data dari depan queue
void Dequeue() {
    if (IsEmpty()) {  // Cek jika queue kosong
        cout << "Queue kosong, tidak ada yang di-dequeue\n";
        return;
    }

    Qnode* temp = queue.front; // Simpan node depan sementara
    queue.front = queue.front->next; // Geser front ke node berikutnya

    if (queue.front == nullptr) { // Jika queue menjadi kosong
        queue.rear = nullptr;    // Set rear juga null
    }

    cout << "Dequeued: " << temp->data << endl; // Tampilkan data yang dihapus
    delete temp;                // Hapus node dari memori
    queue.total_data--;         // Kurangi jumlah data
}

// Fungsi untuk menghapus node setelah node tertentu
void deleteAfter(int target) {
    if (IsEmpty()) {  // Cek jika queue kosong
        cout << "Queue kosong!\n";
        return;
    }

    Qnode* current = queue.front; // Mulai dari node depan

    while (current != nullptr && current->data != target) { // Cari node dengan data target
        current = current->next;
    }

    if (current == nullptr || current->next == nullptr) { // Jika target tidak ditemukan atau target adalah node terakhir
        cout << "Tidak bisa menghapus setelah " << target << endl;
        return;
    }

    Qnode* temp = current->next; // Simpan node yang akan dihapus
    current->next = temp->next;  // Hubungkan current ke node setelah temp

    if (temp == queue.rear) {    // Jika yang dihapus adalah node terakhir
        queue.rear = current;    // Maka current menjadi node terakhir
    }

    cout << "Data setelah " << target << " (" << temp->data << ") telah dihapus.\n";
    delete temp;                // Hapus node dari memori
    queue.total_data--;         // Kurangi jumlah data
}

// Fungsi untuk menghapus node sebelum node tertentu
void deleteBefore(int target) {
    if (IsEmpty() || queue.front->next == nullptr) { // Cek jika queue kosong atau hanya 1 node
        cout << "Queue terlalu sedikit untuk menghapus sebelum data!\n";
        return;
    }

    if (queue.front->data == target) { // Cek jika target adalah node pertama
        cout << "Tidak bisa menghapus sebelum data pertama!\n";
        return;
    }

    Qnode* beforePrev = nullptr; // Pointer untuk node sebelum previous
    Qnode* prev = nullptr;       // Pointer untuk node sebelumnya
    Qnode* current = queue.front; // Mulai dari node depan

    while (current->next != nullptr && current->next->data != target) { // Cari node dengan data target
        beforePrev = prev;
        prev = current;
        current = current->next;
    }

    if (current->next == nullptr) { // Jika target tidak ditemukan
        cout << "Target tidak ditemukan!\n";
        return;
    }

    // Hapus node current (node sebelum target)
    if (beforePrev == nullptr) { // Jika node yang dihapus adalah node kedua
        queue.front = current->next; // Node setelah current menjadi front
    } else {
        beforePrev->next = current->next; // Hubungkan node sebelum current ke node setelah current
    }

    cout << "Data sebelum " << target << " (" << current->data << ") telah dihapus.\n";
    delete current;             // Hapus node dari memori
    queue.total_data--;         // Kurangi jumlah data

    if (queue.rear == current) { // Jika yang dihapus adalah node terakhir
        queue.rear = beforePrev; // Update rear ke node sebelum current
    }
}

// Fungsi untuk menampilkan isi queue
void displayQueue() {
    if (IsEmpty()) {  // Cek jika queue kosong
        cout << "Queue kosong\n";
        cout << "Jumlah antrian: 0\n";
        cout << "Sisa antrian: " << maks << endl;
        return;
    }

    Qnode* current = queue.front; // Mulai dari node depan
    cout << "Isi queue (front ke rear):\n";
    while (current != nullptr) {  // Loop melalui semua node
        cout << "Nama: " << current->data
             << " | Alamat: " << current
             << " | Next: " << current->next << endl;
        current = current->next;  // Pindah ke node berikutnya
    }

    cout << "\nJumlah antrian: " << queue.total_data << endl;
    cout << "Sisa antrian: " << maks - queue.total_data << endl;
    cout << "---------------------------------------\n";
}

// Fungsi utama program
int main() {
    do {
        // Menampilkan menu
        cout << "\n=== MENU QUEUE ===\n";
        cout << "1. Insert Data (Enqueue)\n";
        cout << "2. Jalankan (Dequeue)\n";
        cout << "3. Print List\n";
        cout << "4. Insert After\n";
        cout << "5. Insert Before\n";
        cout << "6. Delete After\n";
        cout << "7. Delete Before\n";
        cout << "0. Exit\n";
        cout << "Pilihan: ";
        cin >> pilihan;  // Menerima input pilihan user

        // Switch case untuk setiap pilihan menu
        if (pilihan == 1) {
            cout << "Masukkan nama (angka): ";
            cin >> nama;
            Enqueue(nama);  // Panggil fungsi Enqueue
        } else if (pilihan == 2) {
            Dequeue();      // Panggil fungsi Dequeue
        } else if (pilihan == 3) {
            displayQueue(); // Panggil fungsi displayQueue
        } else if (pilihan == 4) {
            cout << "Masukkan angka yang ingin disisipkan sesudahnya: ";
            cin >> target;
            cout << "Masukkan angka baru: ";
            cin >> nama;
            insertAfter(target, nama); // Panggil fungsi insertAfter
        } else if (pilihan == 5) {
            cout << "Masukkan angka yang ingin disisipkan sebelumnya: ";
            cin >> target;
            cout << "Masukkan angka baru: ";
            cin >> nama;
            insertBefore(target, nama); // Panggil fungsi insertBefore
        } else if (pilihan == 6) {
            cout << "Masukkan angka yang ingin dihapus setelahnya: ";
            cin >> target;
            deleteAfter(target); // Panggil fungsi deleteAfter
        } else if (pilihan == 7) {
            cout << "Masukkan angka yang ingin dihapus sebelumnya: ";
            cin >> target;
            deleteBefore(target); // Panggil fungsi deleteBefore
        } else if (pilihan != 0) {
            cout << "Pilihan tidak valid! Coba lagi.\n"; // Pesan error untuk pilihan tidak valid
        }

    } while (pilihan != 0);  // Loop selama user tidak memilih 0 (exit)

    cout << "Program selesai.\n";
    return 0;  // Akhiri program
}