#include <iostream>
using namespace std;

// Definisi struktur node + typedef
typedef struct Node { // Membuat tipe data "nodE" dr struct mode pake typedef
    char data;
    Node* next; // Pointer ke mode berikutnya
} nodE; // typedef
struct Node *head = nullptr, *last = nullptr; // Dijadiin "null" agar tdk terisi dgn alamat yg tdk jelas
int maxsize = 4;
int currentsize = 0;

// Fungsi untuk membuat node baru
nodE* createNode(char data) {
    nodE* newNode = new nodE; // Cadangkan memori untuk node baru
    newNode->data = data; // Isi data node
    newNode->next = nullptr; // Atur pointer next ke null
    return newNode; // Kembalikan node baru
}

// Fungsi untuk menambahkan node di awal (insert head)
void insertFirst(char data) {
    if (currentsize >= maxsize) { // Cek jika batas maksimal antrian penuh
    cout << "Antrian sdh penuh! (Max: " << maxsize << ")" << endl;
    return;
    }
    nodE* newNode = createNode(data); // Buat node baru
    newNode->next = head; // Sambung node baru ke head lama
    head = newNode; // Head baru adalah node baru
    if (last == nullptr) { // Jika antrian kosong sebelum insert
        last = head; // Buat last = head
    }
    currentsize++;
}

// Fungsi untuk menambahkan node setelah node tertentu (insert after)
void insertAfter(nodE* prevNode, char data) {
    if (currentsize >= maxsize) { // Cek jika batas maksimal antrian penuh
    cout << "Antrian sdh penuh! (Max: " << maxsize << ")" << endl;
    return;
    }
    nodE* newNode = createNode(data);
    newNode->next = prevNode->next; // Sambungkan ke node baru setelah prevNode
    prevNode->next = newNode;  // Sambungkan prevNode ke node baru
    if (prevNode == last) { // Jika prevNode adalah node terakhir
        last = newNode; // Maka update last
    }
    currentsize++;
}

// Fungsi untuk menghapus node di awal (hapus head)
void deleteFirst() {
    if (head == nullptr) {
        cout << "Linked list is empty. Cannot delete head." << endl;
        return;
    }
    nodE* temp = head; // Simpan head lama
    head = head->next;  // Geser head ke node berikutnya
    if (temp == last) {  // Jika node yang dihapus adalah satu2nya node
        last = nullptr;
    }
    delete temp; // Hapus node lama
    currentsize--;
}
// Fungsi untuk menghapus node setelah node tertentu (delete after)
void deleteAfter(nodE* prevNode) {
    if (prevNode == nullptr || prevNode->next == nullptr) {
    cout << "tidak ada node setelahnya untuk diihapus." << endl;
    return;
    }
    nodE* temp = prevNode->next; // Simpan node yang ingin dihapus
    prevNode->next = temp->next;  // Sambungkan prevNode ke node setelah temp
    if (temp == last) {  // Jika node yang dihapus adalah last
        last = prevNode; // Update last
    }
    delete temp; // Hapus node
    currentsize--;
}

// Fungsi untuk mencetak isi linked list
void printList() {
    nodE* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " (" << temp << ")"; // Tampilkan data dan alamat node
        if (temp->next != nullptr){ // Jika bukan node terakhir
            cout << " "; // Tambahkan spasi/jarak
        }
        temp = temp->next;
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
                insertFirst(value);
                break;
            case 2:
                deleteFirst();
                break;
            case 3:
                printList();
                break;
            case 4: {
                cout << "Masukkan data node yang mau disisipkan setelah: ";
                cin >> target;
                cout << "Masukkan data: ";
                cin >> value;
                // Cari node target
                nodE* temp = head;
                while (temp != nullptr && temp->data != target) {
                    temp = temp->next;
                }
                if (temp == nullptr) {
                    cout << "Node dengan data '" << target << "' tidak ditemukan." << endl;
                }
                else {
                    insertAfter(temp, value);
                }
                break;
            }
            case 5: {
                cout << "Masukkan data node yang mau dihapuskan setelah: ";
                cin >> target;
                // Cari node target
                nodE* temp = head;
                while (temp != nullptr && temp->data != target) {
                    temp = temp->next;
                }
                if (temp == nullptr) {
                    cout << "Node dengan data '" << target << "' tidak ditemukan." << endl;
                }
                else {
                    deleteAfter(temp);
                }
                break;
            }
        }
    } while (pilihan != 0);
    return 0;
}
