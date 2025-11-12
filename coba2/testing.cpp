#include <iostream>
#include <string>
using namespace std;

// Struktur node untuk DLL
typedef struct Qnode {
    string data;
    Qnode* next;
    Qnode* prev; // ← Sekarang aktif digunakan!
} gerbong;

// Struktur queue dengan front dan rear
struct List {
    Qnode* front;       // Node paling depan (untuk dequeue)
    Qnode* rear;        // Node paling belakang (untuk enqueue)
    int total_data;     // Jumlah elemen dalam queue
};

int maks = 4;
int pilihan;
string nama, target;
List queue = {nullptr, nullptr, 0}; // Inisialisasi kosong

// Mengecek apakah queue kosong
bool IsEmpty() {
    return queue.front == nullptr;
}

// Mengecek apakah queue penuh
bool IsFull() {
    return queue.total_data >= maks;
}

// Menambahkan data ke belakang (rear)
void Enqueue(string data) {
    if (IsFull()) {
        cout << "Queue penuh! Maks: " << maks << " data\n";
        return;
    }

    gerbong* newNode = new gerbong;
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = queue.rear;

    if (IsEmpty()) {
        queue.front = queue.rear = newNode;
    } else {
        queue.rear->next = newNode;
        queue.rear = newNode;
    }

    queue.total_data++;
    cout << "Enqueued: " << data << endl;
}

// Menghapus data dari depan (front)
void Dequeue() {
    if (IsEmpty()) {
        cout << "Queue kosong, tidak bisa dequeue.\n";
        return;
    }

    gerbong* temp = queue.front;
    queue.front = queue.front->next;

    if (queue.front != nullptr) {
        queue.front->prev = nullptr;
    } else {
        // Jika setelah dequeue kosong, rear juga null
        queue.rear = nullptr;
    }

    cout << "Dequeued: " << temp->data << endl;
    delete temp;
    queue.total_data--;
}

// Menyisipkan data setelah target
void insertAfter(string target, string nama) {
    if (IsEmpty()) {
        cout << "Queue kosong!\n";
        return;
    }
    if (IsFull()) {
        cout << "Queue penuh!\n";
        return;
    }

    gerbong* current = queue.front;
    while (current != nullptr && current->data != target) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Target tidak ditemukan!\n";
        return;
    }

    gerbong* newNode = new gerbong;
    newNode->data = nama;
    newNode->next = current->next;
    newNode->prev = current;

    if (current->next != nullptr) {
        current->next->prev = newNode;
    } else {
        queue.rear = newNode; // Jika insert setelah rear
    }

    current->next = newNode;
    queue.total_data++;
}

// Menyisipkan data sebelum target
void insertBefore(string target, string nama) {
    if (IsEmpty()) {
        cout << "Queue kosong!\n";
        return;
    }
    if (IsFull()) {
        cout << "Queue penuh!\n";
        return;
    }

    gerbong* current = queue.front;
    while (current != nullptr && current->data != target) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Target tidak ditemukan!\n";
        return;
    }

    gerbong* newNode = new Qnode;
    newNode->data = nama;
    newNode->next = current;
    newNode->prev = current->prev;

    if (current->prev != nullptr) {
        current->prev->next = newNode;
    } else {
        queue.front = newNode; // Jika insert sebelum front
    }

    current->prev = newNode;
    queue.total_data++;
}

// Menampilkan isi queue dari depan
void displayQueue() {
    if (IsEmpty()) {
        cout << "Queue kosong\n";
    } else {
        cout << "Isi queue (front ke rear):\n";
        gerbong* current = queue.front;
        while (current != nullptr) {
            cout << "Nama: " << current->data << " | ";
            current = current->next;
        }
        cout << "\n";
    }

    cout << "Jumlah antrian: " << queue.total_data << endl;
    cout << "Sisa antrian: " << maks - queue.total_data << endl;
    cout << "---------------------------------------" << endl;
}

// Menampilkan isi queue dari belakang (khusus DLL)
void displayReverse() {
    if (IsEmpty()) {
        cout << "Queue kosong\n";
        return;
    }

    cout << "Isi queue (rear ke front):\n";
    Qnode* current = queue.rear;
    while (current != nullptr) {
        cout << "Nama: " << current->data << " | ";
        current = current->prev;
    }
    cout << "\n---------------------------------------" << endl;
}

// Fungsi utama
int main() {
    do {
        cout << "\n=== MENU QUEUE (Double Linked List) ===" << endl;
        cout << "1. Enqueue (Tambah belakang)" << endl;
        cout << "2. Dequeue (Hapus depan)" << endl;
        cout << "3. Tampilkan dari depan" << endl;
        cout << "4. Tampilkan dari belakang" << endl;
        cout << "5. Insert After" << endl;
        cout << "6. Insert Before" << endl;
        cout << "0. Exit" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore(); // Bersihkan newline

        if (pilihan == 1) {
            cout << "Masukkan nama: ";
            cin >> nama;
            Enqueue(nama);
        } else if (pilihan == 2) {
            Dequeue();
        } else if (pilihan == 3) {
            displayQueue();
        } else if (pilihan == 4) {
            displayReverse();
        } else if (pilihan == 5) {
            cout << "Masukkan nama target (setelah siapa?): ";
            cin >> target;
            cout << "Masukkan nama baru: ";
            cin >> nama;
            insertAfter(target, nama);
        } else if (pilihan == 6) {
            cout << "Masukkan nama target (sebelum siapa?): ";
            cin >> target;
            cout << "Masukkan nama baru: ";
            cin >> nama;
            insertBefore(target, nama);
        } else if (pilihan != 0) {
            cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);

    // Hapus semua node sebelum keluar
    while (!IsEmpty()) {
        Dequeue();
    }

    cout << "Program selesai." << endl;
    return 0;
}