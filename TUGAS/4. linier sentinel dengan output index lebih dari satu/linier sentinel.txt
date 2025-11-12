#include <iostream>
using namespace std;

int sentinelSearch(int arr[], int n, int x) {
    // Simpan elemen terakhir
    int last = arr[n - 1]; // 7-1 kan index 6 sama aja terkahir

    // Set elemen terakhir sebagai sentinel
    arr[n - 1] = x; // set elemen terakhir sebagai sentinelnya

    int i = 0;
    while (i < n && arr[i] != x) {
        i++;
    }

    // Kembalikan elemen terakhir ke nilai aslinya
    arr[n - 1] = last;

    // Mencari elemen pertama
    if (i == n) {
        cout << "Element not found in the array" << endl;
        return -1;
    } else {
        cout << "Element found at index " << i;
    }

    i++; // Masuk ke elemen berikutnya
    while (i < n) {
        if (arr [i] == x) {
            cout << " and " << i;
        }
        i++;
    }
    return i;
}

int main() {
    int arr[] = {3, 5, 2, 9, 7, 7, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 7;
    int result = sentinelSearch(arr, n, x);
    return 0;
}
