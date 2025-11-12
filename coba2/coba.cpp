#include <iostream>
using namespace std;

struct Qnode {
    int data;
    Qnode* next;
};

struct List {
    Qnode* front;
    Qnode* rear;
    int total_data;
};

int maks = 4;
int pilihan;
int nama, target;
List queue = {nullptr, nullptr, 0};

// Cek apakah queue kosong
bool IsEmpty() {
    return queue.front == nullptr;
}

// Cek apakah queue penuh
bool IsFull() {
    return queue.total_data >= maks;
}

// Tambah data ke belakang
void Enqueue(int data) {
    if (IsFull()) {
        cout << "Queue penuh! Maks: " << maks << " data\n";
        return;
    }

    Qnode* newNode = new Qnode{data, nullptr};

    if (IsEmpty()) {
        queue.front = queue.rear = newNode;
    } else {
        queue.rear->next = newNode;
        queue.rear = newNode;
    }

    queue.total_data++;
    cout << "Enqueued: " << data << endl;
}

// Sisipkan data setelah elemen tertentu
void insertAfter(int data, int nama) {
    if (IsEmpty()) {
        cout << "Queue kosong!\n";
        return;
    }

    if (IsFull()) {
        cout << "Queue penuh! Maks: " << maks << " data\n";
        return;
    }

    Qnode* current = queue.front;
    while (current != nullptr && current->data != data) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Target tidak ditemukan!\n";
        return;
    }

    Qnode* newNode = new Qnode{nama, current->next};
    current->next = newNode;

    if (current == queue.rear) {
        queue.rear = newNode;
    }

    queue.total_data++;
}

// Sisipkan data sebelum elemen tertentu
void insertBefore(int data, int nama) {
    if (IsEmpty()) {
        cout << "Queue kosong!\n";
        return;
    }

    if (IsFull()) {
        cout << "Queue penuh! Maks: " << maks << " data\n";
        return;
    }

    Qnode* current = queue.front;
    Qnode* prev = nullptr;

    while (current != nullptr && current->data != data) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Target tidak ditemukan!\n";
        return;
    }

    Qnode* newNode = new Qnode{nama, current};

    if (prev == nullptr) {
        queue.front = newNode;
    } else {
        prev->next = newNode;
    }

    queue.total_data++;
}

// Hapus data dari depan
void Dequeue() {
    if (IsEmpty()) {
        cout << "Queue kosong, tidak ada yang di-dequeue\n";
        return;
    }

    Qnode* temp = queue.front;
    queue.front = queue.front->next;

    if (queue.front == nullptr) {
        queue.rear = nullptr;
    }

    cout << "Dequeued: " << temp->data << endl;
    delete temp;
    queue.total_data--;
}

// Tampilkan isi queue
void displayQueue() {
    if (IsEmpty()) {
        cout << "Queue kosong\n";
        cout << "Jumlah antrian: 0\n";
        cout << "Sisa antrian: " << maks << endl;
        return;
    }

    Qnode* current = queue.front;
    cout << "Isi queue (front ke rear):\n";
    while (current != nullptr) {
        cout << "Nama: " << current->data
             << " | Alamat: " << current
             << " | Next: " << current->next << endl;
        current = current->next;
    }

    cout << "\nJumlah antrian: " << queue.total_data << endl;
    cout << "Sisa antrian: " << maks - queue.total_data << endl;
    cout << "---------------------------------------\n";
}

// Main program
int main() {
    do {
        cout << "\n=== MENU QUEUE ===\n";
        cout << "1. Insert Data (Enqueue)\n";
        cout << "2. Jalankan (Dequeue)\n";
        cout << "3. Print List\n";
        cout << "4. Insert After\n";
        cout << "5. Insert Before\n";
        cout << "0. Exit\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == 1) {
            cout << "Masukkan nama (angka): ";
            cin >> nama;
            Enqueue(nama);
        } else if (pilihan == 2) {
            Dequeue();
        } else if (pilihan == 3) {
            displayQueue();
        } else if (pilihan == 4) {
            cout << "Masukkan angka yang ingin disisipkan sesudahnya: ";
            cin >> target;
            cout << "Masukkan angka baru: ";
            cin >> nama;
            insertAfter(target, nama);
        } else if (pilihan == 5) {
            cout << "Masukkan angka yang ingin disisipkan sebelumnya: ";
            cin >> target;
            cout << "Masukkan angka baru: ";
            cin >> nama;
            insertBefore(target, nama);
        } else if (pilihan != 0) {
            cout << "Pilihan tidak valid! Coba lagi.\n";
        }

    } while (pilihan != 0);

    cout << "Program selesai.\n";
    return 0;
}