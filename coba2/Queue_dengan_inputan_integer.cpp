// insert last + delete first + insert after + OUTPUT
#include <iostream>
using namespace std;

// Struktur node
struct Qnode {
    int data;
    Qnode* prev;
    Qnode* next;
};

// Struktur list dengan front dan rear
struct List {
    Qnode* head;
    Qnode* front;
    Qnode* rear;  
    int jumlah_data;
};

int maksimum = 4;
List queue = {nullptr, nullptr, nullptr, 0};

// Fungsi mengecek apakah queue kosong
bool IsEmpty() {
    return queue.front == nullptr;
}

// Fungsi mengecek apakah queue penuh
bool IsFull() {
    return queue.jumlah_data >= maksimum;
}

// Fungsi enqueue (tambahkan ke belakang/rear)
void Enqueue(int data) {
    if (IsFull()) {
        cout << "Queue penuh! Maksimal " << maksimum << " data." << endl;
        return;
    }

    Qnode* newNode = new Qnode;
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = nullptr;

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
        newNode->prev = queue.rear;
        queue.rear = newNode;
    }
    queue.jumlah_data++;
    cout << "Enqueued: " << data << endl;
}

// Fungsi insertAfter yang diperbaiki dan diintegrasikan
void insertAfter(int target, int angkaBaru) {
    if (IsEmpty()) {
        cout << "Tidak bisa karena queue kosong." << endl;
        return;
    }

    if (IsFull()) {
        cout << "Data penuh, mohon maaf." << endl;
        return;
    }

    // Deklarasi temp di luar if agar bisa digunakan setelahnya
    Qnode* temp = queue.head;
    while (temp != nullptr && temp->data != target) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Target tidak ditemukan." << endl;
        return;
    }

    // Membuat node baru dan menyisipkannya setelah target
    Qnode* newNode = new Qnode;
    newNode->data = angkaBaru;
    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next != nullptr) {
        temp->next->prev = newNode;
    } else {
        // jika temp adalah rear, update rear
        queue.rear = newNode;
    }

    temp->next = newNode;
    queue.jumlah_data++;
    cout << "Disisipkan " << angkaBaru << " setelah " << target << endl;
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
    } else {
        queue.front->prev = nullptr;
    }
    
    cout << "Dequeued: " << temp->data << endl;
    delete temp;
    queue.jumlah_data--; // Jangan lupa kurangi jumlah data
}

// Tampilkan isi queue
void displayQueue() {
    if (IsEmpty()) {
        cout << "Queue kosong" << endl;
        cout << "Jumlah data: 0" << endl;
        cout << "Sisa slot: " << maksimum << endl;
        return;
    }

    Qnode* current = queue.front;
    cout << "Isi queue (dari front ke rear):" << endl;
    while (current != nullptr) {
        cout << "Angka: " << current->data
             << " | Alamat: " << current
             << " | Prev: " << current->prev
             << " | Next: " << current->next << endl;
        current = current->next;
    }

    cout << "\nJumlah data dalam queue: " << queue.jumlah_data << endl;
    cout << "Sisa slot: " << maksimum - queue.jumlah_data << endl;
    cout << "---------------------------------------" << endl;
}

// Main
int main() {
    int pilihan;
    do {
        cout << "\n=== MENU QUEUE ===" << endl;
        cout << "1. Insert data (enqueue)" << endl;
        cout << "2. Jalankan (dequeue)" << endl;
        cout << "3. Insert after" << endl;
        cout << "4. Tampilkan data dalam queue" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore(); // untuk getline

        if (pilihan == 1) {
            int angka;
            cout << "Masukkan Angka: ";
            cin >> angka;
            Enqueue(angka);
        } else if (pilihan == 2) {
            Dequeue();
        } else if (pilihan == 4) {
            displayQueue();
        } else if (pilihan == 3) {
            int target, angkaBaru;
            cout << "Masukkan Angka yang ingin disisipkan setelahnya: ";
            cin >> target;
            cout << "Masukkan Angka baru: ";
            cin >> angkaBaru;
            insertAfter (target, angkaBaru);
        } else if (pilihan != 0) {
            cout << "Pilihan tidak valid. Coba lagi." << endl;
        }
    } while (pilihan != 0);

    cout << "Program selesai." << endl;
    return 0;
}