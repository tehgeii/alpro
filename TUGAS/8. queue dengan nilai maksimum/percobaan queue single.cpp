#include <iostream>
#include <string>
using namespace std;

// Struktur node
struct Qnode {
    int data;
    Qnode* next;
};

// Struktur list dengan front dan rear
struct List {
    Qnode* head;//buat manggil
    Qnode* front;
    Qnode* rear;  // elemen belakang
    int total_data;
};

int maks = 4;
int pilihan;
int angka, target;
List queue = {nullptr, nullptr, nullptr, 0};

// Fungsi mengecek apakah queue kosong
bool IsEmpty() {
    return queue.front == nullptr;
}

// Fungsi mengecek apakah queue penuh
bool IsFull() {
    return queue.total_data >= maks;
}

// Fungsi enqueue (tambahkan ke belakang/rear)
void Enqueue(int data) {
    if (IsFull()) {
        cout << "Queue penuh! maks: " << maks << " data" << endl;
        return;
    }

    Qnode* newNode = new Qnode;
    newNode->data = data;
    newNode->next = nullptr;

    if (IsEmpty()) {
        queue.head = newNode;
        queue.front = newNode;
        queue.rear = newNode;
    } else {
        Qnode* current = queue.head;
        while(current->next != nullptr){
            current = current->next;
        }
        current->next = newNode;
        queue.rear = newNode;
    }
    queue.total_data++;
    cout << "Enqueued: " << data << endl;
}

// Fungsi insertAfter yang diperbaiki dan diintegrasikan
void insertAfter(int data, int angka) {
    if (IsEmpty()) {
        cout << "Queue kosong!" << endl;
        return;
    }

    if (IsFull()) {
        cout << "Queue penuh! maks: " << maks << " data" << endl;
        return;
    }

    // Deklarasi temp di luar if agar bisa digunakan setelahnya
    Qnode* current = queue.head;
    while (current != nullptr && current->data != data) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Target tidak ditemukan!" << endl;
        return;
    }

    // Membuat node baru dan menyisipkannya setelah target
    Qnode* newNode = new Qnode;
    newNode->data = angka;
    newNode->next = current->next;
    current->next = newNode;
    queue.total_data++;
}

// Fungsi insertBefore yang diperbaiki dan diintegrasikan
void insertBefore(int data, int angka) {
    if (IsEmpty()) {
        cout << "Queue kosong!" << endl;
        return;
    }

    if (IsFull()) {
        cout << "Queue penuh! maks: " << maks << " data" << endl;
        return;
    }

    // Deklarasi temp di luar if agar bisa digunakan setelahnya
    Qnode* current = queue.head;
    Qnode* prev = nullptr;
    while (current != nullptr && current->data != data) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Target tidak ditemukan!" << endl;
        return;
    }

    // Membuat node baru dan menyisipkannya setelah target
    Qnode* newNode = new Qnode;
    newNode->data = angka;

    // Jika target adalah head (insert di awal)
    if (prev == nullptr) {
        newNode->next = queue.head;
        queue.head = newNode;
    } else { // Jika target bukan head
        newNode->next = prev->next;
        prev->next = newNode;
    }
    queue.total_data++;
}

// Fungsi dequeue (hapus dari depan/front)
void Dequeue() {
    if (IsEmpty()) {
        cout << "Queue kosong, tidak ada yang di-dequeue" << endl;
        return;
    }

    Qnode* temp = queue.front;
    queue.front = queue.front->next;
    
    // Jika queue menjadi kosong setelah dequeue
    if (queue.front == nullptr) {
        queue.rear = nullptr;
    }
    
    cout << "Dequeued: " << temp->data << endl;
    delete temp;
    queue.total_data--; // Jangan lupa kurangi jumlah data
}

// Tampilkan isi queue
void displayQueue() {
    if (IsEmpty()) {
        cout << "Queue kosong" << endl;
        cout << "Jumlah antrian: " << queue.total_data << endl;
        cout << "Sisa antrian: " << maks << endl;
        return;
    }

    cout << "Front: " << queue.front->data << " (" << queue.front << ")\n";
    cout << "Rear: " << queue.rear->data << " (" << queue.rear << ")\n\n";

    Qnode* current = queue.front;
    cout << "Isi queue (front ke rear): " << endl;
    while (current != nullptr) {
        cout << "Nama: " << current->data << " | Alamat: " << current << " | Next: " << current->next << endl;
        current = current->next;
    }

    cout << "\nJumlah antrian: " << queue.total_data << endl;
    cout << "Sisa antrian: " << maks - queue.total_data << endl;
    cout << "---------------------------------------" << endl;
}

// Main
int main() {
    do {
        cout << "\n=== MENU QUEUE ===" << endl;
        cout << "1. Enqueue (insert last)" << endl;
        cout << "2. Dequeue" << endl;
        cout << "3. Print List" << endl;
        cout << "4. Insert After" << endl;
        cout << "5. Insert Before" << endl;
        cout << "0. Exit" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore(); // untuk getline

        if (pilihan == 1) {
            cout << "Masukkan angka: ";
            cin >> angka;
            Enqueue(angka);
        } else if (pilihan == 2) {
            Dequeue();
        } else if (pilihan == 3) {
            displayQueue();
        } else if (pilihan == 4) {
            cout << "Masukkan angka yang ingin disisipkan sesudahnya: ";
            cin >> target;
            cout << "Masukkan angka baru: ";
            cin >> angka;
            insertAfter(target, angka);
        } else if (pilihan == 5) {
            cout << "Masukkan angka yang ingin disisipkan sebelumnya: ";
            cin >> target;
            cout << "Masukkan angka baru: ";
            cin >> angka;
            insertBefore(target, angka);
        } else {
            cout << "Pilihan tidak valid! Coba lagi.\n" << endl;
        }
    } while (pilihan != 0);

    cout << "Program selesai." << endl;
    return 0;
}