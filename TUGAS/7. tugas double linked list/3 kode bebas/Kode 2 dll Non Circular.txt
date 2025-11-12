#include <iostream>
using namespace std;

// Struktur Node
struct Node {
    int data;     // Menyimpan nilai/data
    Node* prev;   // Pointer ke node sebelumnya (prev = previous)
    Node* next;   // Pointer ke node berikutnya (next)
};

// Fungsi untuk membuat node baru
Node* createNode(int data) {
    Node* newNode = new Node(); // Alokasi memori untuk node baru
    newNode->data = data;       // Isi data ke dalam node
    newNode->prev = nullptr;    // Atur pointer prev ke null
    newNode->next = nullptr;    // Atur pointer next ke null
    return newNode;             // Kembalikan node yang sudah dibuat
}

// Fungsi untuk menyisipkan node sebagai elemen pertama dalam linked list
void insertFirst(Node*& head, int data) {
    Node* newNode = createNode(data); // Buat node baru
    if (head == nullptr) {
        head = newNode; // Jika linked list kosong, node baru menjadi head
    } else {
        newNode->next = head; // Node baru menunjuk ke head lama
        head->prev = newNode; // Mengatur prev dari head menjadi node baru
        head = newNode;       // Mengatur node baru sebagai head
    }
}

// Fungsi untuk menyisipkan node sebagai elemen terakhir dalam linked list
void insertLast(Node*& head, int data) {
    Node* newNode = createNode(data); // Buat node baru
    if (head == nullptr) {
        head = newNode; // Jika linked list kosong, node baru menjadi head
    } else {
        Node* current = head;
        // Mencari posisi terakhir dalam linked list
        while (current->next != nullptr) {
            current = current->next;
        }
        // Menyisipkan node baru setelah posisi terakhir
        current->next = newNode; // Mengatur next dari posisi terakhir menjadi node baru
        newNode->prev = current; // Mengatur prev dari node baru
        // Menampilkan informasi tentang setiap node dalam linked list
    }
}

// Fungsi untuk menyisipkan node setelah node dengan nilai tertentu dalam linked list
void insertAfter(Node* head, int valueToInsertAfter, int data) {
    // Mulai pencarian dari head
    Node* current = head;
    // Mencari node dengan nilai yang sesuai
    while (current != nullptr && current->data != valueToInsertAfter) {
        current = current->next;
    }
    // Jika node dengan nilai yang sesuai tidak ditemukan
    if (current == nullptr) { // Jika target tidak ditemukan
        cout << "Node dengan nilai " << valueToInsertAfter << " tidak ditemukan" << endl;
        return;
    }
    // Membuat node baru
    Node* newNode = createNode(data);
    // Menyisipkan node baru setelah node dengan nilai yang sesuai
    newNode->next = current->next; // Mengatur next dari node baru
    newNode->prev = current; // Mengatur prev dari node baru
    current->next = newNode; // Mengatur next dari node yang sebelumnya menunjuk ke node baru
    // Mengatur prev dari node yang berada setelah node baru, jika ada
    if (newNode->next != nullptr) {
        newNode->next->prev = newNode;
    }
}

// Fungsi untuk menghapus node pertama dari linked list
void deleteFirst(Node*& head) {
    // Jika linked list kosong
    if (head == nullptr) {
        cout << "Linked list kosong, tidak ada yang dihapus" << endl;
        return;
    }
    // Simpan alamat node yang akan dihapus
    Node* temp = head;
    // Ubah head menjadi node setelahnya
    head = head->next;

    // Jika linked list head tidak null atau ada isinya
    if (head != nullptr) {
        head->prev = nullptr;
    }
    // Hapus node pertama
    delete temp;
}

// Fungsi untuk menghapus node terakhir dari linked list
void deleteLast(Node*& head) {
    // Jika linked list kosong
    if (head == nullptr) {
        cout << "Linked list kosong, tidak ada yang dihapus" << endl;
        return;
    }

    // Jika linked list hanya memiliki satu node
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }

    // Mencari node terakhir dalam linked list
    Node* current = head;

    while (current->next->next != nullptr) {
        current = current->next;
    }

    // Simpan alamat node terakhir
    Node* temp = current->next;

    // Mengatur prev dari node sebelumnya menjadi nullptr
    current->next = nullptr;

    // Hapus node terakhir
    delete temp;
}

// Fungsi untuk menghapus node setelah node dengan nilai tertentu dari linked list
void deleteAfter(Node* head, int valueToDeleteAfter) {
    // Jika linked list kosong
    if (head == nullptr) {
        cout << "Linked list kosong, tidak ada yang dihapus" << endl;
        return;
    }

    Node* current = head;

    // Mencari node dengan nilai yang sesuai
    while (current != nullptr && current->data != valueToDeleteAfter) {
        current = current->next;
    }

    // Jika node dengan nilai yang sesuai tidak ditemukan
    if (current == nullptr || current->next == nullptr) {
        cout << "Node dengan nilai " << valueToDeleteAfter << " tidak ditemukan atau tidak memiliki node setelahnya" << endl;
        return;
    }

    // Simpan alamat node yang akan dihapus
    Node* temp = current->next;

    // Hubungkan node sebelumnya dengan node setelah yang akan dihapus
    current->next = temp->next;
    // Jika node setelah yang akan dihapus bukan node terakhir
    if (temp->next != nullptr) {
        temp->next->prev = current;
    }

    // Hapus node
    delete temp;
}

// Fungsi untuk menampilkan informasi tentang setiap node dalam linked list
void displayList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << "\nAlamat: " << current << endl;
        cout << "Nilai: " << current->data << endl;
        cout << "Alamat prev: " << current->prev << endl;
        cout << "Alamat next: " << current->next << endl << endl;
        current = current->next;
    }
    cout << endl;
}

int main() {
    Node* head = nullptr; // Pointer ke node pertama (kosong di awal)
    Node* tail = nullptr; // Pointer ke node terakhir (kosong di awal)
    int choice, data, target;

    do {
        cout << "\nMenu Double Linked List Non-Circular:" << endl;
        cout << "1. Insert First" << endl;
        cout << "2. Insert Last" << endl;
        cout << "3. Insert After" << endl;
        cout << "4. Delete First" << endl;
        cout << "5. Delete Last" << endl;
        cout << "6. Delete After" << endl;
        cout << "7. Print List" << endl;
        cout << "8. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> choice; // Baca input pilihan user

        switch(choice) {
            case 1: // Insert di awal
                cout << "Masukkan data: ";
                cin >> data;
                insertFirst(head, data);
                break;

            case 2: // Insert di akhir
                cout << "Masukkan data: ";
                cin >> data;
                insertLast(head, data);
                break;

            case 3: // Insert setelah node tertentu
                cout << "Masukkan data setelah: ";
                cin >> target;
                cout << "Masukkan data baru: ";
                cin >> data;
                insertAfter(head, target, data);
                break;

            case 4: // Hapus node pertama
                deleteFirst(head);
                break;

            case 5: // Hapus node terakhir
                deleteLast(head);
                break;

            case 6: // Hapus node setelah node tertentu
                cout << "Masukkan data sebelum yang akan dihapus: ";
                cin >> target;
                deleteAfter(head, target);
                break;

            case 7: // Cetak list dua arah
                displayList(head);
                break;

            case 8: // Keluar dari program
                cout << "Program selesai." << endl;
                break;

            default: // Input tidak valid
                cout << "Pilihan tidak valid!" << endl;
        }
    } while(choice != 8); // Ulangi sampai user pilih keluar
    return 0;
}
