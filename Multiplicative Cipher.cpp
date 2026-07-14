#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Function to find modular inverse using Extended Euclidean Algorithm
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1; // Inverse doesn't exist
}

string encryptMultiplicative(string text, int key) {
    string result = "";
    for (char &c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += ((c - base) * key) % 26 + base;
        } else {
            result += c;
        }
    }
    return result;
}

string decryptMultiplicative(string text, int key) {
    int invKey = modInverse(key, 26);
    if (invKey == -1) {
        return "Error: Key is not coprime with 26. Decryption impossible!";
    }
    return encryptMultiplicative(text, invKey);
}

int main() {
    string message = "Cryptography";
    int key = 7; // Must be coprime with 26 (e.g., 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25)

    string encrypted = encryptMultiplicative(message, key);
    string decrypted = decryptMultiplicative(encrypted, key);

    cout << "--- Multiplicative Cipher ---" << endl;
    cout << "Original:  " << message << endl;
    cout << "Encrypted: " << encrypted << endl;
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}