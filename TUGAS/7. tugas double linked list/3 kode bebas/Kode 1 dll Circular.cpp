#include <iostream>
using namespace std;

// Struktur Node
struct Node {
    int data;
    Node* prev;
    Node* next;
};

// Fungsi untuk membuat node baru
Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->prev = nullptr;
    newNode->next = nullptr;
    return newNode;
}

// Fungsi untuk menyisipkan node sebagai elemen pertama dalam linked list
void insertFirst(Node* &head, Node* &tail, int data) {
    Node* newNode = createNode(data);
    if (head == nullptr) {
        head = tail = newNode; // Jika linked list kosong, node baru menjadi head serta tail
        newNode->next = newNode;
        newNode->prev = newNode;
    } else {
        newNode->next = head;
        newNode->prev = tail;
        head->prev = newNode; // Mengatur prev dari head menjadi node baru
        tail->next = newNode; // Mengatur next dari tail menjadi node baru
        head = newNode; // Mengatur node baru sebagai head
    }
}

// Fungsi untuk menyisipkan node sebagai elemen terakhir dalam linked list
void insertLast(Node* &head, Node* &tail, int data) {
    Node* newNode = createNode(data);
    if (tail == nullptr) {
        head = tail = newNode; // Jika linked list kosong, node baru menjadi head serta tail
        newNode->next = newNode;
        newNode->prev = newNode;
    } else {
        newNode->prev = tail;
        newNode->next = head;
        tail->next = newNode; // Mengatur next dari tail menjadi node baru
        head->prev = newNode; // Mengatur prev dari head menjadi node baru
        tail = newNode; // Mengatur node baru sebagai tail
    }
}

// Fungsi untuk menyisipkan node setelah node dengan nilai tertentu dalam linked list
void insertAfter(Node* &head, Node* &tail, int target, int data) {
    if (head == nullptr) {
        cout << "Linked list kosong" << endl;
        return;
    }
    // Mulai pencarian dari head
    Node* current = head;
    // Traversal pakai do-while
    do {
        if (current->data == target) {
            Node* newNode = createNode(data);
            newNode->prev = current;
            newNode->next = current->next;
            current->next->prev = newNode;
            current->next = newNode;

            // Jika insert setelah tail, update tail
            if (current == tail) {
                tail = newNode;
                head->prev = tail;
            }
            return;
        }
        current = current->next;
    } while (current != head);

    cout << "Data " << target << " tidak ditemukan" << endl;
}

// Fungsi untuk menghapus node pertama dari linked list
void deleteFirst(Node* &head, Node* &tail) {
    if (head == nullptr) {
        cout << "Linked list kosong, tidak ada yang dihapus" << endl;
        return;
    }
    // Simpan alamat node yang akan dihapus
    Node* temp = head;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        // Ubah head menjadi node setelahnya
        head = head->next;
        head->prev = tail;
        tail->next = head;
    }
    delete temp;
}

// Fungsi untuk menghapus node terakhir dari linked list
void deleteLast(Node* &head, Node* &tail) {
    if (tail == nullptr) return;

    Node* temp = tail;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = head;
        head->prev = tail;
    }
    delete temp;
}

// Fungsi untuk menghapus node setelah node dengan nilai tertentu dari linked list
void deleteAfter(Node* &head, Node* &tail, int target) {
    if (head == nullptr) {
        cout << "Linked list kosong, tidak ada yang dihapus" << endl;
        return;
    }

    Node* current = head;
    do {
        if (current->data == target) {
            if (current->next == head && current == tail) {
                cout << "Tidak ada node setelahnya" << endl;
                return;
            }

            Node* toDelete = current->next;
            current->next = toDelete->next;
            toDelete->next->prev = current;

            // Jika perlu, update head atau tail
            if (toDelete == head) {
                head = toDelete->next;
            }
            if (toDelete == tail) {
                tail = current;
            }

            delete toDelete;
            return;
        }
        current = current->next;
    } while (current != head);

    cout << "Data " << target << " tidak ditemukan" << endl;
}

// Fungsi untuk menampilkan informasi tentang setiap node dalam linked list
void displayList(Node* head) {
    if (head == nullptr) {
        cout << "Linked list kosong" << endl;
        return;
    }

    Node* current = head;
    do {
        cout << "\nAlamat: " << current << endl;
        cout << "Nilai: " << current->data << endl;
        cout << "Alamat prev: " << current->prev << endl;
        cout << "Alamat next: " << current->next << endl << endl;
        current = current->next;
    } while (current != head);
    cout << endl;
}

int main() {
    Node* head = nullptr;
    Node* tail = nullptr;
    int choice, data, target;

    do {
        cout << "\nMenu Double Linked List Circular:" << endl;
        cout << "1. Insert First" << endl;
        cout << "2. Insert Last" << endl;
        cout << "3. Insert After" << endl;
        cout << "4. Delete First" << endl;
        cout << "5. Delete Last" << endl;
        cout << "6. Delete After" << endl;
        cout << "7. Print List" << endl;
        cout << "8. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Masukkan data: ";
                cin >> data;
                insertFirst(head, tail, data);
                break;
            case 2:
                cout << "Masukkan data: ";
                cin >> data;
                insertLast(head, tail, data);
                break;
            case 3:
                cout << "Masukkan data setelah: ";
                cin >> target;
                cout << "Masukkan data baru: ";
                cin >> data;
                insertAfter(head, tail, target, data);
                break;
            case 4:
                deleteFirst(head, tail);
                break;
            case 5:
                deleteLast(head, tail);
                break;
            case 6:
                cout << "Masukkan data sebelum yang akan dihapus: ";
                cin >> target;
                deleteAfter(head, tail, target);
                break;
            case 7:
                displayList(head);
                break;
            case 8:
                cout << "Program selesai." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while(choice != 8);
    return 0;
}
