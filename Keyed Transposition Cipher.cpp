#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string encryptKeyedTransposition(string text, vector<int> key) {
    int blockSize = key.size();
    while (text.length() % blockSize != 0) {
        text += 'X'; // Pad out plaintext
    }
    
    string ciphertext = "";
    for (size_t i = 0; i < text.length(); i += blockSize) {
        string block = text.substr(i, blockSize);
        string permuted = block;
        for (int k = 0; k < blockSize; k++) {
            permuted[k] = block[key[k]];
        }
        ciphertext += permuted;
    }
    return ciphertext;
}

string decryptKeyedTransposition(string text, vector<int> key) {
    int blockSize = key.size();
    string plaintext = "";
    for (size_t i = 0; i < text.length(); i += blockSize) {
        string block = text.substr(i, blockSize);
        string original = block;
        for (int k = 0; k < blockSize; k++) {
            original[key[k]] = block[k];
        }
        plaintext += original;
    }
    return plaintext;
}

int main() {
    string text = "KEYEDTRANSPOSITION";
    vector<int> key = {2, 0, 3, 1}; // Represents mapping: 0->2, 1->0, etc.
    
    string encrypted = encryptKeyedTransposition(text, key);
    string decrypted = decryptKeyedTransposition(encrypted, key);
    
    cout << "--- Keyed Transposition ---" << endl;
    cout << "Original:  " << text << endl;
    cout << "Encrypted: " << encrypted << endl;
    cout << "Decrypted: " << decrypted << endl;
    return 0;
}


