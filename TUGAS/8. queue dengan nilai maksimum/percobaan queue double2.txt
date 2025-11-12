// insert first + delete last + Delete before + insert after + insert before + output
#include <iostream>
using namespace std;

// Struktur node
struct Qnode {
    int data;
    Qnode* prev;
    Qnode* next;
};

// Struktur list
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

// Fungsi enqueue (seperti insert first = tambahkan ke depan/front)
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
        newNode->next = queue.front;
        queue.front->prev = newNode;
        queue.front = newNode;
        queue.head = newNode;
    }
    queue.jumlah_data++;
    cout << "Enqueued: " << data << endl;
}

// Fungsi insertAfter
void insertAfter(int target, int angkaBaru) {
    if (IsEmpty()) {
        cout << "Tidak bisa karena queue kosong." << endl;
        return;
    }
    if (IsFull()) {
        cout << "Data penuh, mohon maaf." << endl;
        return;
    }

    Qnode* temp = queue.front;
    while (temp != nullptr && temp->data != target) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Target tidak ditemukan." << endl;
        return;
    }

    Qnode* newNode = new Qnode;
    newNode->data = angkaBaru;
    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next != nullptr) {
        temp->next->prev = newNode;
    } else {
        queue.rear = newNode;
    }
    temp->next = newNode;

    queue.jumlah_data++;
    cout << "Disisipkan " << angkaBaru << " setelah " << target << endl;
}

// Fungsi insertBefore
void insertBefore(int target, int angkaBaru) {
    if (IsEmpty()) {
        cout << "Queue kosong!" << endl;
        return;
    }
    if (IsFull()) {
        cout << "Queue penuh!" << endl;
        return;
    }

    Qnode* temp = queue.front;
    while (temp != nullptr && temp->data != target) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Target tidak ditemukan." << endl;
        return;
    }

    Qnode* newNode = new Qnode;
    newNode->data = angkaBaru;
    newNode->prev = temp->prev;
    newNode->next = temp;  

    if (temp->prev != nullptr) {
        temp->prev->next = newNode;
    } else {
        queue.front = newNode;
    }
    temp->prev = newNode;

    queue.jumlah_data++;
    cout << "Disisipkan " << angkaBaru << " sebelum " << target << endl;
}

// Fungsi dequeue
void Dequeue() {
    if (IsEmpty()) {
        cout << "Queue kosong, tidak ada yang di-dequeue" << endl;
        return;
    }

    Qnode* temp = queue.rear;

    if (queue.front == queue.rear) {
        // Hanya satu elemen
        queue.front = nullptr;
        queue.rear = nullptr;
        queue.head = nullptr;
    } else {
        queue.rear = queue.rear->prev;
        queue.rear->next = nullptr;
    }

    cout << "Dequeued: " << temp->data << endl;
    delete temp;

    queue.jumlah_data--;
}

// menambahkan fungsi delete before
void deleteBefore(int valueToDeleteBefore){
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
    queue.jumlah_data--;
}

// Tampilkan isi queue
void displayQueue() {
    if (IsEmpty()) {
        cout << "Queue kosong" << endl;
        cout << "Jumlah data: 0" << endl;
        cout << "Sisa slot: " << maksimum << endl;
        return;
    }

    cout << "Front: " << queue.front->data << " (" << queue.front << ")\n";
    cout << "Rear: " << queue.rear->data << " (" << queue.rear << ")\n\n";

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
        cout << "1. Enqueue (insert first)" << endl;
        cout << "2. Dequeue" << endl;
        cout << "3. Delete Before" << endl;
        cout << "4. Insert After" << endl;
        cout << "5. Insert Before" << endl;
        cout << "6. Print List" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        
        if (pilihan == 1) {
            int angka;
            cout << "Masukkan Angka: ";
            cin >> angka;
            Enqueue(angka);
        } else if (pilihan == 2) {
            Dequeue();
        } else if (pilihan == 3) {
        int target;
        cout << "Masukkan angka yang ingin dihapus Sebelumnya: ";
        cin >> target;
        deleteBefore(target);
        } else if (pilihan == 4) {
            int target, angkaBaru;
            cout << "Masukkan angka yang ingin disisipkan setelahnya: ";
            cin >> target;
            cout << "Masukkan angka baru: ";
            cin >> angkaBaru;
            insertAfter(target, angkaBaru);
        } else if (pilihan == 5) {
            int target, angkaBaru;
            cout << "Masukkan angka yang ingin disisipkan sebelumnya: ";
            cin >> target;
            cout << "Masukkan angka baru: ";
            cin >> angkaBaru;
            insertBefore(target, angkaBaru);
        } else if (pilihan == 6) {
            displayQueue();
        } else if (pilihan != 0) {
            cout << "Pilihan tidak valid. Coba lagi." << endl;
        }
    } while (pilihan != 0);

    cout << "Program selesai." << endl;
    return 0;
}