#include <iostream>
using namespace std;

int main() {
    const int n = 7;
    int arr[n];  // Total 7 bits: 3 parity + 4 data
    int p1, p2, p4;

    cout << "Enter the 7-bit received data (Hamming Code) one by one:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Calculate parity bits using received data (positions start from 0)
    p1 = arr[0] ^ arr[2] ^ arr[4] ^ arr[6]; // parity at position 1 (index 0)
    p2 = arr[1] ^ arr[2] ^ arr[5] ^ arr[6]; // parity at position 2 (index 1)
    p4 = arr[3] ^ arr[4] ^ arr[5] ^ arr[6]; // parity at position 4 (index 3)

    // Calculate error position (binary to decimal)
    int error_position = p4 * 4 + p2 * 2 + p1 * 1;

    if (error_position == 0) {
        cout << "✅ Received data is correct. No error detected." << endl;
    } else {
        cout << "❌ Error detected at position: " << error_position << endl;

        // Flip the bit at the error position
        arr[error_position - 1] ^= 1;

        cout << "✅ Corrected data: ";
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
