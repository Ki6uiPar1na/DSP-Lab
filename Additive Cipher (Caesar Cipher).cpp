#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string encryptAdditive(string text, int key) {
    string result = "";
    for (char &c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += (c - base + key) % 26 + base;
        } else {
            result += c; // Leave non-alphabetic characters as they are
        }
    }
    return result;
}

string decryptAdditive(string text, int key) {
    // Decryption is just shifting backward
    return encryptAdditive(text, 26 - (key % 26));
}

int main() {
    string message = "Hello World";
    int key = 3;

    string encrypted = encryptAdditive(message, key);
    string decrypted = decryptAdditive(encrypted, key);

    cout << "--- Additive Cipher ---" << endl;
    cout << "Original:  " << message << endl;
    cout << "Encrypted: " << encrypted << endl;
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}