#include <iostream>

using namespace std;

// Struktur Node untuk queue
struct Qnode {
    int data;
    Qnode* next;
    Qnode* prev;
};
int maxx = 2;
int jumlah = 0;
int choice;
// Struktur List untuk menyimpan head dan front dari queue
struct List {
    Qnode* head;//buat manggil
    Qnode* front;
    Qnode* rear;
};

// Inisialisasi queue
List queue = {nullptr, nullptr, nullptr}; //head, front, rear

// Fungsi untuk mengecek apakah queue kosong
bool IsEmpty() {
    return queue.head == nullptr;
}

// Fungsi untuk mengecek apakah queue penuh (tidak relevan untuk linked list, jadi selalu false)
bool IsFull() {
    return false;
}

// Fungsi untuk enqueue (menambahkan elemen di awal queue)
void EnqueueBefore(Qnode* head,int data, int ValueToInsertBefore) {
    if (jumlah >= maxx)
    {
        cout << "penuh\n" << endl;
        return;
    }
    Qnode* current = head;
    while (current != nullptr && current->data != ValueToInsertBefore) {
        current = current->next;
    }
    Qnode* newNode = new Qnode;
    newNode->data = data;
    newNode->next = queue.head;
    newNode->prev = nullptr;

    if (IsEmpty()) {
        queue.head = newNode;
        queue.front = newNode;
        queue.rear = newNode;
    } else {
        queue.head->prev = newNode;
        queue.head = newNode;
        queue.rear = newNode;
    }
    cout << "Enqueued: " << data << endl;
    jumlah++;

}

// Fungsi untuk dequeue (menghapus elemen dari akhir queue)
void DequeueBefore() {

    if (IsEmpty()) {
        cout << "Queue kosong, tidak ada yang di-dequeue" << endl;
        return;
    }


    if (queue.rear->prev == nullptr) { // Jika hanya ada satu elemen di queue
        cout << "Dequeued 1: " << queue.rear->data << endl;
        delete queue.rear;
        queue.head = nullptr;
        queue.rear = nullptr;
        queue.front = nullptr;
    }
    else {
        Qnode* temp = queue.rear;
        queue.rear = queue.rear->prev;
        queue.rear->next = nullptr;
        cout << "Dequeued 2: " << temp->data << endl;
        delete temp;
    }
    jumlah--;
}

// Fungsi untuk menampilkan isi queue
void displayQueue() {
    if (IsEmpty()) {
        cout << "Queue kosong" << endl;
        return;
    }
    Qnode* current = queue.head;
    cout << "Isi queue:" << endl;
    while (current != nullptr) {
        cout << "Nilai: " << current->data << endl;
        cout << "Front: " << queue.front->data << endl;
        cout << "Rear: " << queue.rear->data << endl;
        cout << "Alamat: " << current << endl;
        cout << "Alamat next: " << current->next << endl;
        cout << "Alamat prev: " << current->prev << endl << endl;
        current = current->next;
    }
    cout << "jumlah antrian: " << jumlah << endl;
    cout << "sisa antrian: " << maxx - jumlah << endl;
    cout << endl << "---------------------------------------" <<endl;
}

int main() {
    // Memastikan queue kosong
    if (IsEmpty()) {
        cout << "Queue baru saja diinisialisasi dan kosong." << endl;
    }

    do {
        cout << "\nMenu Queue DLL:" << endl;
        cout << "1. Insert Before" << endl;
        cout << "2. Delete Before" << endl;
        cout << "3. Print List" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> choice; // Baca input pilihan user

        switch(choice) {
            case 1: // Insert di awal
                cout << "Masukkan data: ";
                cin >> data;
                EnqueueBefore(head, data);
                break;

            case 2: // Insert di akhir
                cout << "Masukkan data: ";
                cin >> data;
                DequeueBefore(head, data);
                break;

            case 3: // Cetak list dua arah
                displayQueue(head);
                break;

            case 4: // Keluar dari program
                cout << "Program selesai." << endl;
                break;

            default: // Input tidak valid
                cout << "Pilihan tidak valid!" << endl;
        }
    } while(choice != 4); // Ulangi sampai user pilih keluar
    return 0;
}
