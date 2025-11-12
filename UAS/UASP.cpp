// insert first, delete last
#include <iostream>
using namespace std;

// Struktur node untuk menyimpan satu data dalam queue
typedef struct Qnode {
    string data; // Menyimpan nilai angka
    Qnode* prev; // Pointer ke node sebelumnya
    Qnode* next; // Pointer ke node berikutnya
} qnodE; // Nama alias: qnodE

// Struktur untuk mengelola seluruh queue
typedef struct List {
    Qnode* head; // Pointer ke node paling depan (bisa dipakai untuk traversal)
    Qnode* front; // Pointer ke node terdepan (posisi masuk)
    Qnode* rear; // Pointer ke node terbelakang (posisi keluar)
    int jumlah_data; // Penghitung jumlah data saat ini
} lisT; // Nama alias: lisT

int maksimum = 3; // Kapasitas maksimal queue
lisT queue = {nullptr, nullptr, nullptr, 0}; // Inisialisasi queue kosong

// Cek apakah queue kosong (tidak ada data)
bool IsEmpty() {
    return queue.front == nullptr; // Front null artinya kosong
}

// Cek apakah queue penuh (data mencapai batas maksimum)
bool IsFull() {
    return queue.jumlah_data >= maksimum; // Bandingkan jumlah dengan kapasitas
}

// Tambah data di depan (front) - Mirip insert first
void Enqueue(string data) {
    if (IsFull()) {
        cout << "Queue penuh! Maksimal " << maksimum << " data." << endl;
        return; // Langsung keluar jika penuh
    }

    // Buat node baru
    qnodE* newNode = new qnodE; // Alokasi memori
    newNode->data = data;       // Isi data
    newNode->next = nullptr;    // Awalnya tidak menunjuk node lain
    newNode->prev = nullptr;

    if (IsEmpty()) { 
        // Jika queue kosong, front, rear, dan head semuanya menunjuk node baru
        queue.head = newNode;
        queue.front = newNode;
        queue.rear = newNode;
    } else {
        // Jika ada data:
        newNode->next = queue.front; // Node baru menunjuk ke front lama
        queue.front->prev = newNode;  // Front lama menunjuk balik ke node baru
        queue.front = newNode;        // Update front menjadi node baru
        queue.head = newNode;         // Update head (opsional, bisa dipakai traversal)
    }
    queue.jumlah_data++; // Tambah jumlah data
    cout << "Enqueued: " << data << endl;
}

// Sisipkan data setelah node tertentu
void insertAfter(string target, string angkaBaru) {
    if (IsEmpty()) {
        cout << "Tidak bisa karena queue kosong." << endl;
        return;
    }
    if (IsFull()) {
        cout << "Data penuh, mohon maaf." << endl;
        return;
    }

    // Cari node yang mengandung 'target'
    qnodE* temp = queue.front; // Mulai dari depan
    while (temp != nullptr && temp->data != target) {
        temp = temp->next; // Geser ke node berikutnya
    }

    // Jika target tidak ditemukan
    if (temp == nullptr) {
        cout << "Target tidak ditemukan." << endl;
        return;
    }

    // Buat node baru
    qnodE* newNode = new qnodE;
    newNode->data = angkaBaru;
    newNode->next = temp->next; // Node baru menunjuk ke node setelah temp
    newNode->prev = temp;       // Node baru menunjuk balik ke temp

    // Jika temp bukan node terakhir (ada node setelahnya)
    if (temp->next != nullptr) {
        temp->next->prev = newNode; // Node setelah temp menunjuk balik ke node baru
    } else {
        queue.rear = newNode; // Jika temp adalah rear, update rear jadi node baru
    }
    temp->next = newNode; // Temp menunjuk ke node baru

    queue.jumlah_data++;
    cout << "Disisipkan " << angkaBaru << " setelah " << target << endl;
}

// Sisipkan data sebelum node tertentu
void insertBefore(string target, string angkaBaru) {
    if (IsEmpty()) {
        cout << "Queue kosong!" << endl;
        return;
    }
    if (IsFull()) {
        cout << "Queue penuh!" << endl;
        return;
    }

    // Cari node yang mengandung 'target'
    qnodE* temp = queue.front;
    while (temp != nullptr && temp->data != target) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Target tidak ditemukan." << endl;
        return;
    }

    // Buat node baru
    qnodE* newNode = new qnodE;
    newNode->data = angkaBaru;
    newNode->prev = temp->prev; // Node baru menunjuk ke node sebelum temp
    newNode->next = temp;       // Node baru menunjuk ke temp

    // Jika temp bukan node pertama (ada node sebelumnya)
    if (temp->prev != nullptr) {
        temp->prev->next = newNode; // Node sebelum temp menunjuk ke node baru
    } else {
        queue.front = newNode; // Jika temp adalah front, update front jadi node baru
    }
    temp->prev = newNode; // Temp menunjuk balik ke node baru

    queue.jumlah_data++;
    cout << "Disisipkan " << angkaBaru << " sebelum " << target << endl;
}

// Hapus data terakhir (rear) - Mirip delete last
void Dequeue() {
    if (IsEmpty()) {
        cout << "Queue kosong, tidak ada yang di-dequeue" << endl;
        return;
    }

    qnodE* temp = queue.rear; // Simpan node yang akan dihapus (paling belakang)

    // Kasus 1: Hanya ada satu data
    if (queue.front == queue.rear) {
        queue.front = nullptr;
        queue.rear = nullptr;
        queue.head = nullptr;
    } else {
        // Kasus 2: Ada banyak data
        queue.rear = queue.rear->prev; // Geser rear ke node sebelumnya
        queue.rear->next = nullptr;    // Putuskan hubungan dengan node terakhir
    }

    cout << "Dequeued: " << temp->data << endl;
    delete temp; // Hapus node dari memori

    queue.jumlah_data--; // Kurangi jumlah data
}

// Hapus data setelah node tertentu
void deleteAfter(string valueToDeleteAfter) {
    if (IsEmpty()) {
        cout << "Queue kosong, tidak ada yang dihapus" << endl;
        return;
    }

    // Cari node dengan nilai 'valueToDeleteAfter'
    qnodE* current = queue.front;
    while (current != nullptr && current->data != valueToDeleteAfter) {
        current = current->next;
    }

    // Validasi: pastikan node ditemukan dan punya node setelahnya
    if (current == nullptr || current->next == nullptr) {
        cout << "Tidak ada data setelah node ini" << endl;
        return;
    }

    // Node yang akan dihapus adalah node setelah 'current'
    qnodE* temp = current->next;

    // Hubungkan current dengan node setelah temp
    current->next = temp->next;
    if (temp->next != nullptr) {
        temp->next->prev = current; // Jika temp bukan rear
    } else {
        queue.rear = current; // Jika temp adalah rear, update rear
    }

    cout << "Dihapus data setelah " << valueToDeleteAfter << ": " << temp->data << endl;
    delete temp; // Hapus node
    queue.jumlah_data--;
}

// Hapus data sebelum node tertentu
void deleteBefore(string valueToDeleteBefore){
    if (IsEmpty()) {
        cout << "Queue kosong, tidak ada yang dihapus" << endl;
        return;
    }

    // Cari node dengan nilai 'valueToDeleteBefore'
    qnodE* current = queue.front;
    while (current != nullptr && current->data != valueToDeleteBefore) {
        current = current->next;
    }

    // Validasi: pastikan node ditemukan dan punya node sebelumnya
    if (current == nullptr || current->prev == nullptr) {
        cout << "Tidak ada data sebelum node ini" << endl;
        return;
    }

    // Node yang akan dihapus adalah node sebelum 'current'
    qnodE* temp = current->prev; 

    // Hubungkan node sebelum temp dengan current
    current->prev = temp->prev;
    if (temp->prev != nullptr) {
        temp->prev->next = current; // Jika temp bukan front
    } else {
        queue.front = current; // Jika temp adalah front, update front
    }

    cout << "Dihapus data sebelum " << valueToDeleteBefore << ": " << temp->data << endl;
    delete temp; // Hapus node
    queue.jumlah_data--;
}

// Tampilkan seluruh isi queue beserta informasi
void displayQueue() {
    if (IsEmpty()) {
        cout << "Queue kosong" << endl;
        cout << "Jumlah data: 0" << endl;
        cout << "Sisa slot: " << maksimum << endl;
        return;
    }

    // Tampilkan front dan rear beserta alamat memorinya
    cout << "Front: " << queue.front->data << " (" << queue.front << ")\n";
    cout << "Rear: " << queue.rear->data << " (" << queue.rear << ")\n\n";//

    // Traverse: tampilkan semua node dari front ke rear
    qnodE* current = queue.front;
    cout << "Isi queue (dari front ke rear):" << endl;
    while (current != nullptr) {
        // Tampilkan data, alamat node, alamat prev, dan next
        cout << "Angka: " << current->data
             << " | Alamat: " << current
             << " | Prev: " << current->prev
             << " | Next: " << current->next << endl;
        current = current->next;
    }

    // Tampilkan statistik
    cout << "\nJumlah data dalam queue: " << queue.jumlah_data << endl;
    cout << "Sisa slot: " << maksimum - queue.jumlah_data << endl;
    cout << "---------------------------------------" << endl;
}

// Program utama: Menu interaktif
int main() {
    int pilihan;
    do {
        // Tampilkan menu
        cout << "A11.2024.15851" << endl;
        cout << "Dafi Hauzan A.H\n\n" << endl;
        cout << "\n=== MENU QUEUE ===" << endl;
        cout << "1. Enqueue (insert first)" << endl;
        cout << "2. Dequeue" << endl;
        cout << "3. Delete After" << endl;
        cout << "4. Delete Before" << endl;
        cout << "5. Insert After" << endl;
        cout << "6. Insert Before" << endl;
        cout << "7. Print List" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        // Proses pilihan user
        if (pilihan == 1) {
            string angka;
            cout << "Masukkan Angka: ";
            cin >> angka;
            Enqueue(angka);
        } else if (pilihan == 2) {
            Dequeue();
        } else if (pilihan == 3) {
            string target;
            cout << "Masukkan angka yang ingin dihapus Setelahnya: ";
            cin >> target;
            deleteAfter(target);
        } else if (pilihan == 4) {
            string target;
            cout << "Masukkan angka yang ingin dihapus Sebelumnya: ";
            cin >> target;
            deleteBefore(target);
        } else if (pilihan == 5) {
            string target, angkaBaru;
            cout << "Masukkan angka yang ingin disisipkan setelahnya: ";
            cin >> target;
            cout << "Masukkan angka baru: ";
            cin >> angkaBaru;
            insertAfter(target, angkaBaru);
        } else if (pilihan == 6) {
            string target, angkaBaru;
            cout << "Masukkan angka yang ingin disisipkan sebelumnya: ";
            cin >> target;
            cout << "Masukkan angka baru: ";
            cin >> angkaBaru;
            insertBefore(target, angkaBaru);
        } else if (pilihan == 7) {
            displayQueue();
        } else if (pilihan == 0) {
            cout << "Program selesai." << endl;
            break;
        } else {
            cout << "Pilihan tidak valid. Coba lagi." << endl;
        }
    } while (pilihan != 0);
    return 0;
}