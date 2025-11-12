// Ini codingannya bekas UTS (single linked list non circular)
// Jadi saya (Dafi) hanya mengubah codingannya dari single menjadi double
// Sisanya masih sama (non circular, typedef, maksimal gerbong yaitu 5)

#include <iostream>
using namespace std;

// Struktur Node + typedef
typedef struct Node { // Membuat tipe data "GerbonG" dr struct mode pake typedef
    char data;
    Node* next; // Pointer ke mode berikutnya
    Node* prev; // Pointer ke mode sebelumnya
} GerbonG; // typedef
struct Node *head = nullptr, *last = nullptr; // Dijadiin "null" agar tdk terisi dgn alamat yg tdk jelas
int maxsize = 5, currentsize = 0;

// Fungsi untuk membuat node baru
GerbonG* createNode(char data) {
    GerbonG* newNode = new GerbonG; // Cadangkan memori untuk node baru
    newNode->data = data; // Isi data node
    newNode->prev = nullptr; // Atur pointer prev ke null
    newNode->next = nullptr; // Atur pointer next ke null
    return newNode; // Kembalikan node baru
}

// Fungsi untuk menambahkan node di awal (insert head)
void insertFirst(GerbonG*& head, char data) {
    if (currentsize >= maxsize) { // Cek jika batas maksimal antrian penuh
    cout << "Antrian sdh penuh! (Max: " << maxsize << ")" << endl;
    return;
    }
    GerbonG* newNode = createNode(data); // Buat node baru
    if (head == nullptr) {
        head = newNode; // Jika linked list kosong, node baru menjadi head
    } else {
        newNode->next = head; // Node baru menunjuk ke head lama
        head->prev = newNode; // Mengatur prev dari head menjadi node baru
        head = newNode; // Mengatur node baru sebagai head
    }
    currentsize++;
}

// Fungsi untuk menyisipkan node setelah node dengan nilai tertentu dalam linked list
void insertAfter(GerbonG* head, int valueToInsertAfter, char data) {
    if (currentsize >= maxsize) { // Cek jika batas maksimal antrian penuh
    cout << "Antrian sdh penuh! (Max: " << maxsize << ")" << endl;
    return;
    }
    // Mulai pencarian dari head
    GerbonG* current = head;
    // Mencari node dengan nilai yang sesuai
    while (current != nullptr && current->data != valueToInsertAfter) {
        current = current->next;
    }
    // Jika node dengan nilai yang sesuai tidak ditemukan
    if (current == nullptr) {
        cout << "Node dengan nilai " << valueToInsertAfter << " tidak ditemukan" << endl;
        return;
    }
    // Membuat node baru
    GerbonG* newNode = createNode(data);
    // Menyisipkan node baru setelah node dengan nilai yang sesuai
    newNode->next = current->next; // Mengatur next dari node baru
    newNode->prev = current; // Mengatur prev dari node baru
    current->next = newNode; // Mengatur next dari node yang sebelumnya menunjuk ke node baru
    // Mengatur prev dari node yang berada setelah node baru, jika ada
    if (newNode->next != nullptr) {
        newNode->next->prev = newNode;
    }
    currentsize++;
}

// Fungsi untuk menyisipkan node sebelum node dengan nilai tertentu dalam linked list
void insertBefore(GerbonG*& head, char valueToInsertBefore, char data) {
    if (currentsize >= maxsize) { // Cek jika batas maksimal antrian penuh
        cout << "Antrian sdh penuh! (Max: " << maxsize << ")" << endl;
        return;
    }
    // Jika linked list kosong
    if (head == nullptr) {
        cout << "Linked list kosong, tidak bisa insert before" << endl;
        return;
    }
    // Jika disisipkan sebelum head, sehingga menjadi head baru
    if (head->data == valueToInsertBefore) {
        insertFirst(head, data);
        return;
    }
    // Mulai mencari posisi untuk menyisipkan di tengah
    GerbonG* current = head;
    // Mencari node dengan nilai yang sesuai
    while (current != nullptr && current->data != valueToInsertBefore) {
        current = current->next;
    }
    // Jika node dengan nilai yang sesuai tidak ditemukan
    if (current == nullptr) {
        cout << "Node dengan nilai " << valueToInsertBefore << " tidak ditemukan" << endl;
        return;
    }
    // Membuat node baru
    GerbonG* newNode = createNode(data);
    // Menyisipkan node baru sebelum node yang ditemukan
    newNode->prev = current->prev; // Mengatur prev dari node baru
    newNode->next = current; // Mengatur next dari node baru
    current->prev->next = newNode; // Mengatur next dari node sebelum current
    current->prev = newNode; // Mengatur prev dari current ke node baru
    currentsize++;
}

// Fungsi untuk menghapus node di awal (hapus head)
void deleteFirst(GerbonG*& head) {
    // Jika linked list kosong
    if (head == nullptr) {
        cout << "Linked list kosong, tidak ada yang dihapus" << endl;
        return;
    }
    // Simpan alamat node yang akan dihapus
    GerbonG* temp = head;
    // Ubah head menjadi node setelahnya
    head = head->next;

    // Jika linked list head tidak null atau ada isinya
    if (head != nullptr) {
        head->prev = nullptr;
    }
    // Hapus node pertama
    delete temp;
    currentsize--;
}
// Fungsi untuk menghapus node setelah node dengan nilai tertentu dari linked list
void deleteAfter(GerbonG* head, char valueToDeleteAfter) {
    // Jika linked list kosong
    if (head == nullptr) {
        cout << "Linked list kosong, tidak ada yang dihapus" << endl;
        return;
    }

    GerbonG* current = head;

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
    GerbonG* temp = current->next;

    // Hubungkan node sebelumnya dengan node setelah yang akan dihapus
    current->next = temp->next;
    // Jika node setelah yang akan dihapus bukan node terakhir
    if (temp->next != nullptr) {
        temp->next->prev = current;
    }
    // Hapus node
    delete temp;
    currentsize--;
}

// Fungsi untuk menampilkan informasi tentang setiap node dalam linked list
void displayList(GerbonG* head) {
    GerbonG* current = head;
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
    int pilihan;
    char value, target;
    do {
        cout << "\nMENU:" << endl;
        cout << "1. Insert First " << endl;
        cout << "2. Delete First" << endl;
        cout << "3. Print List" << endl;
        cout << "4. Insert After " << endl;
        cout << "5. Delete After" << endl;
        cout << "6. Insert Before" << endl;
        cout << "0. Out" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        switch (pilihan) {
            case 0:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                break;
            case 1:
                cout << "Masukkan data: "; cin >> value;
                insertFirst(head, value);
                break;
            case 2:
                deleteFirst(head);
                break;
            case 3:
                displayList(head);
                break;
            case 4: {
                cout << "Masukkan data setelah: ";
                cin >> target;
                cout << "Masukkan data baru: ";
                cin >> value;
                insertAfter(head, target, value);
                break;
            }
            case 5: {
                cout << "Masukkan data sebelum yang akan dihapus: ";
                cin >> target;
                deleteAfter(head, target);
                break;
            }
            case 6: {
                cout << "Masukkan data sebelum: ";
                cin >> target;
                cout << "Masukkan data baru: ";
                cin >> value;
                insertBefore(head, target, value);
                break;
            }
        }
    } while (pilihan != 8);
    return 0;
}
