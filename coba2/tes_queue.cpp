// insert last + delete first + Delete after + insert after + insert before + output
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

    Qnode* temp = queue.front;
    queue.front = queue.front->next;

    if (queue.front == nullptr) {
        queue.rear = nullptr;
    } else {
        queue.front->prev = nullptr;
    }

    cout << "Dequeued: " << temp->data << endl;
    delete temp;
    queue.jumlah_data--;
}

void deleteAfter(int valueToDeleteAfter) {
    if (IsEmpty()) {
        cout << "Queue kosong, tidak ada yang dihapus" << endl;
        return;
    }

    Qnode* current = queue.front;

    // Mencari node dengan nilai target
    while (current != nullptr && current->data != valueToDeleteAfter) {
        current = current->next;
    }

    // Cek apakah target ditemukan dan memiliki node setelahnya
    if (current == nullptr || current->next == nullptr) {
        cout << "Data " << valueToDeleteAfter << " tidak ditemukan atau tidak memiliki data setelahnya." << endl;
        return;
    }

    // Node yang akan dihapus adalah node setelah 'current'
    Qnode* temp = current->next;
    current->next = temp->next;

    if (temp->next != nullptr) {
        temp->next->prev = current;
    } else {
        // Jika node yang dihapus adalah rear
        queue.rear = current;
    }

    cout << "Dihapus data setelah " << valueToDeleteAfter << ": " << temp->data << endl;
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
        cout << "1. Enqueue (insert last)" << endl;
        cout << "2. Dequeue" << endl;
        cout << "3. Delete After (Untuk data ke 2 hingga ke empat)" << endl;
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
        cout << "Masukkan angka yang ingin dihapus setelahnya: ";
        cin >> target;
        deleteAfter(target);
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