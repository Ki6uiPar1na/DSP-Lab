#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

string encryptAffine(string text, int a, int b) {
    string result = "";
    for (char &c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += (a * (c - base) + b) % 26 + base;
        } else {
            result += c;
        }
    }
    return result;
}

string decryptAffine(string text, int a, int b) {
    int invA = modInverse(a, 26);
    if (invA == -1) return "Error: 'a' must be coprime with 26.";
    
    string result = "";
    for (char &c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            int val = (invA * ((c - base) - b + 26)) % 26;
            result += val + base;
        } else {
            result += c;
        }
    }
    return result;
}

int main() {
    string message = "Affine Cipher";
    int a = 5, b = 8; // 'a' must be coprime with 26

    string encrypted = encryptAffine(message, a, b);
    string decrypted = decryptAffine(encrypted, a, b);

    cout << "--- Affine Cipher ---" << endl;
    cout << "Original:  " << message << endl;
    cout << "Encrypted: " << encrypted << endl;
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}