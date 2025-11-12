#include <iostream>
using namespace std;

// Struktur Node
struct Node { 
    char data;
    Node* next;
    Node* prev;
};
struct Node *head = nullptr, *last = nullptr;
int maxsize = 5, currentsize = 0;

// Fungsi untuk membuat node baru
Node* createNode(char data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->prev = nullptr;
    newNode->next = nullptr;
    return newNode;
}

// Fungsi untuk menambahkan node di awal (insert head)
void insertFirst(Node*& head, char data) {
    if (currentsize >= maxsize) {
    cout << "Antrian sdh penuh! (Max: " << maxsize << ")" << endl;
    return;
    }
    Node* newNode = createNode(data);
    if (head == nullptr) {
        head = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    currentsize++;
}

// Fungsi untuk menyisipkan node setelah node dengan nilai tertentu dalam linked list
void insertAfter(Node* head, int valueToInsertAfter, char data) {
    if (currentsize >= maxsize) {
    cout << "Antrian sdh penuh! (Max: " << maxsize << ")" << endl;
    return;
    }

    Node* current = head;

    while (current != nullptr && current->data != valueToInsertAfter) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Node dengan nilai " << valueToInsertAfter << " tidak ditemukan" << endl;
        return;
    }

    Node* newNode = createNode(data);

    newNode->next = current->next; 
    newNode->prev = current; 
    current->next = newNode;

    if (newNode->next != nullptr) {
        newNode->next->prev = newNode;
    }
    currentsize++;
}

// Fungsi untuk menyisipkan node sebelum node dengan nilai tertentu dalam linked list
void insertBefore(Node*& head, char valueToInsertBefore, char data) {
    if (currentsize >= maxsize) { // Cek jika batas maksimal antrian penuh
        cout << "Antrian sdh penuh! (Max: " << maxsize << ")" << endl;
        return;
    }

    if (head == nullptr) {
        cout << "Linked list kosong, tidak bisa insert before" << endl;
        return;
    }

    if (head->data == valueToInsertBefore) {
        insertFirst(head, data);
        return;
    }

    Node* current = head;

    while (current != nullptr && current->data != valueToInsertBefore) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Node dengan nilai " << valueToInsertBefore << " tidak ditemukan" << endl;
        return;
    }

    Node* newNode = createNode(data);

    newNode->prev = current->prev; 
    newNode->next = current; 
    current->prev->next = newNode; 
    current->prev = newNode; 
    currentsize++;
}
// Fungsi untuk menghapus node setelah node dengan nilai tertentu dari linked list
void deleteAfter(Node* head, char valueToDeleteAfter) {
    // Jika linked list kosong
    if (head == nullptr) {
        cout << "Linked list kosong, tidak ada yang dihapus" << endl;
        return;
    }

    Node* current = head;


    while (current != nullptr && current->data != valueToDeleteAfter) {
        current = current->next;
    }


    if (current == nullptr || current->next == nullptr) {
        cout << "Node dengan nilai " << valueToDeleteAfter << " tidak ditemukan atau tidak memiliki node setelahnya" << endl;
        return;
    }


    Node* temp = current->next;


    current->next = temp->next;

    if (temp->next != nullptr) {
        temp->next->prev = current;
    }
    // Hapus node
    delete temp;
    currentsize--;
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
    int pilihan;
    char value, target;
    do {
        cout << "\nMENU:" << endl;
        cout << "1. Insert First " << endl;
        cout << "2. Print List" << endl;
        cout << "3. Insert After " << endl;
        cout << "4. Delete After" << endl;
        cout << "5. Insert Before" << endl;
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
                displayList(head);
                break;
            case 3: {
                cout << "Masukkan data setelah: ";
                cin >> target;
                cout << "Masukkan data baru: ";
                cin >> value;
                insertAfter(head, target, value);
                break;
            }
            case 4: {
                cout << "Masukkan data sebelum yang akan dihapus: ";
                cin >> target;
                deleteAfter(head, target);
                break;
            }
            case 5: {
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
