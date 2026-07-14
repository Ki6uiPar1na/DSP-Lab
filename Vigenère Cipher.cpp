#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string encryptVigenere(string text, string key) {
    string ciphertext = "";
    int keyIdx = 0;
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char keyBase = isupper(key[keyIdx % key.length()]) ? 'A' : 'a';
            int shift = toupper(key[keyIdx % key.length()]) - 'A';
            ciphertext += (c - base + shift) % 26 + base;
            keyIdx++;
        } else {
            ciphertext += c;
        }
    }
    return ciphertext;
}

string decryptVigenere(string text, string key) {
    string plaintext = "";
    int keyIdx = 0;
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            int shift = toupper(key[keyIdx % key.length()]) - 'A';
            plaintext += (c - base - shift + 26) % 26 + base;
            keyIdx++;
        } else {
            plaintext += c;
        }
    }
    return plaintext;
}

int main() {
    string text = "GEEKSFORGEEKS";
    string key = "AYUSH";
    
    string encrypted = encryptVigenere(text, key);
    string decrypted = decryptVigenere(encrypted, key);
    
    cout << "--- Vigenere Cipher ---" << endl;
    cout << "Original:  " << text << endl;
    cout << "Encrypted: " << encrypted << endl;
    cout << "Decrypted: " << decrypted << endl;
    return 0;
}