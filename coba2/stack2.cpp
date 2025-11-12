#include <iostream>
using namespace std;

// Struktur Node untuk stack
struct tElmtStack {
    int data;
    tElmtStack* next;
};

typedef tElmtStack Stack;

// Inisialisasi TOP
Stack* TOP = nullptr;

// Mengecek apakah stack kosong
bool isEmpty() {
    return TOP == nullptr;
}

// Fungsi push (menambahkan elemen ke atas stack)
void push(int data) {
    Stack* newNode = new Stack;
    newNode->data = data;
    newNode->next = TOP;  // arahkan ke TOP sebelumnya
    TOP = newNode;        // sekarang newNode jadi TOP
    cout << "Pushed: " << data << endl;
}

// Fungsi pop (menghapus elemen paling atas)
void pop() {
    if (isEmpty()) {
        cout << "Stack kosong, tidak ada yang di-pop" << endl;
        return;
    }

    Stack* temp = TOP;
    cout << "Popped: " << temp->data << endl;
    TOP = TOP->next;  // pindahkan TOP ke node di bawahnya
    delete temp;
}

// Fungsi untuk menampilkan isi stack
void displayStack() {
    if (isEmpty()) {
        cout << "Stack kosong" << endl;
        return;
    }

    Stack* current = TOP;
    cout << "\nIsi stack dari atas ke bawah:\n";
    while (current != nullptr) {
        cout << "Alamat: " << current << endl;
        cout << "Nilai: " << current->data << endl;
        cout << "Alamat next: " << current->next << endl << endl;
        current = current->next;
    }
    cout << "---------------------------------------" << endl;
}

int main() {
    // Cek awal
    if (isEmpty()) {
        cout << "Stack baru saja diinisialisasi dan kosong." << endl;
    }

    // Tambah data
    push(10);
    push(20);
    push(30);

    // Tampilkan
    displayStack();

    // Hapus satu per satu
    pop();
    displayStack();

    pop();
    displayStack();

    pop();
    displayStack();

    // Tes pop pada stack kosong
    pop();

    return 0;
}