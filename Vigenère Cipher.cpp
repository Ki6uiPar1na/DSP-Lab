#include <iostream>
#include <string>

using namespace std;

string encryptVigenere(string plaintext, string key) {
    string ciphertext = "";
    int keyIdx = 0;
    for (char &c : plaintext) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char keyBase = isupper(key[keyIdx % key.length()]) ? 'A' : 'a';
            int k = key[keyIdx % key.length()] - keyBase;
            
            ciphertext += ((c - base + k) % 26) + base;
            keyIdx++;
        } else {
            ciphertext += c;
        }
    }
    return ciphertext;
}

string decryptVigenere(string ciphertext, string key) {
    string plaintext = "";
    int keyIdx = 0;
    for (char &c : ciphertext) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char keyBase = isupper(key[keyIdx % key.length()]) ? 'A' : 'a';
            int k = key[keyIdx % key.length()] - keyBase;
            
            int val = (c - base - k) % 26;
            if (val < 0) val += 26;
            
            plaintext += val + base;
            keyIdx++;
        } else {
            plaintext += c;
        }
    }
    return plaintext;
}

int main() {
    string msg = "ATTACK AT DAWN";
    string key = "LEMON";
    
    string cipher = encryptVigenere(msg, key);
    cout << "Vigenere Cipher:\n";
    cout << "Ciphertext: " << cipher << endl;
    cout << "Decrypted:  " << decryptVigenere(cipher, key) << "\n\n";
    return 0;
}