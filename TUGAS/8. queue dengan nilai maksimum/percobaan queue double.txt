#include <iostream>
#include <string>
using namespace std;

// Struktur node
struct Qnode {
    string data;
    Qnode* next;
    Qnode* prev;
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
string nama, target;
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
void Enqueue(string data) {
    if (IsFull()) {
        cout << "Queue penuh! maks: " << maks << " data" << endl;
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
        newNode->next = queue.front;
        queue.front->prev = newNode;
        queue.front = newNode;
        queue.head = newNode;
    }
    queue.total_data++;
    cout << "Enqueued: " << data << endl;
}

// Fungsi insertAfter yang diperbaiki dan diintegrasikan
void insertAfter(string data, string nama) {
    if (IsEmpty()) {
        cout << "Queue kosong!" << endl;
        return;
    }

    if (IsFull()) {
        cout << "Queue penuh! maks: " << maks << " antrian" << endl;
        return;
    }

    // Deklarasi temp di luar if agar bisa digunakan setelahnya
    Qnode* current = queue.front;
    while (current != nullptr && current->data != data) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Target tidak ditemukan!" << endl;
        return;
    }

    // Membuat node baru dan menyisipkannya setelah target
    Qnode* newNode = new Qnode;
    newNode->data = nama;
    newNode->next = current->next;
    newNode->prev = current;

    if (current->next != nullptr) {
        current->next->prev = newNode;
    } else {
        queue.rear = newNode;
    }
    current->next = newNode;
    queue.total_data++;
}

// Fungsi insertBefore yang diperbaiki dan diintegrasikan
void insertBefore(string data, string nama) {
    if (IsEmpty()) {
        cout << "Queue kosong!" << endl;
        return;
    }

    if (IsFull()) {
        cout << "Queue penuh! maks: " << maks << " antrian" << endl;
        return;
    }

    // Deklarasi temp di luar if agar bisa digunakan setelahnya
    Qnode* current = queue.front;
    while (current != nullptr && current->data != data) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Target tidak ditemukan!" << endl;
        return;
    }

    // Membuat node baru dan menyisipkannya setelah target
    Qnode* newNode = new Qnode;
    newNode->data = nama;
    newNode->prev = current->prev;
    newNode->next = current;  

    // Jika target adalah head (insert di awal)
    if (current->prev != nullptr) {
        current->prev->next = newNode;
    } else {
        queue.front = newNode;
    }
    current->prev = newNode;
    queue.total_data++;
}

void deleteBefore(string valueToDeleteBefore){
    if (IsEmpty()) {
        cout << "Queue kosong, tidak ada yang dihapus" << endl;
        return;
    }

     Qnode* current = queue.front;

    // Mencari node dengan nilai target
    while (current != nullptr && current->data != valueToDeleteBefore) {
        current = current->next;
    }
    // Node yang akan dihapus adalah node sebelum 'current'
    Qnode* temp = current->prev;
    current->prev = temp->prev;
    if (temp->prev != nullptr) {
        temp->prev->next = current;
    } else {
        // Jika node yang dihapus adalah rear
        queue.rear = current;
    }

    cout << "Dihapus data setelah " << valueToDeleteBefore << ": " << temp->data << endl;
    delete temp;
    queue.total_data--;
}

// Fungsi dequeue (hapus dari depan/front)
void Dequeue() {
    if (IsEmpty()) {
        cout << "Queue kosong, tidak ada yang di-dequeue" << endl;
        return;
    }

    Qnode* temp = queue.rear;
    
    // Jika queue menjadi kosong setelah dequeue
    if (queue.front == queue.rear) {
        queue.front = nullptr;
        queue.rear = nullptr;
        queue.head = nullptr;
    } else {
        queue.rear = queue.rear->prev;
        queue.rear->next = nullptr;
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

    cout << "Head: " << queue.head->data << " (" << queue.head << ")\n";
    cout << "Front: " << queue.front->data << " (" << queue.front << ")\n";
    cout << "Rear: " << queue.rear->data << " (" << queue.rear << ")\n";

    Qnode* current = queue.head;
    cout << "\nIsi queue (front ke rear): " << endl;
    while (current != nullptr) {
        cout << "Nama: " << current->data << " | Alamat: " << current << " | Prev: " << current->prev << "| Next: " << current->next << endl;
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
        cout << "1. Insert Data (Enqueue)" << endl;
        cout << "2. Jalankan (Dequeue)" << endl;
        cout << "3. Print List" << endl;
        cout << "4. Insert After" << endl;
        cout << "5. Insert Before" << endl;
        cout << "6. Delete Before" << endl;
        cout << "0. Exit" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore(); // untuk getline

        if (pilihan == 1) {
            cout << "Masukkan nama: ";
            cin >> nama;
            Enqueue(nama);
        } else if (pilihan == 2) {
            Dequeue();
        } else if (pilihan == 3) {
            displayQueue();
        } else if (pilihan == 4) {
            cout << "Masukkan nama yang ingin disisipkan sesudahnya: ";
            cin >> target;
            cout << "Masukkan nama baru: ";
            cin >> nama;
            insertAfter(target, nama);
        } else if (pilihan == 5) {
            cout << "Masukkan nama yang ingin disisipkan sebelumnya: ";
            cin >> target;
            cout << "Masukkan nama baru: ";
            cin >> nama;
            insertBefore(target, nama);
        } else if (pilihan == 6) {
            cout << "Masukkan angka yang ingin dihapus Sebelumnya: ";
            cin >> target;
            deleteBefore(target);
        } else {
            cout << "Pilihan tidak valid! Coba lagi.\n" << endl;
        }
    } while (pilihan != 0);

    cout << "Program selesai." << endl;
    return 0;
}