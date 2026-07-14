#include <iostream>
#include <string>
#include <vector>

using namespace std;

// This combines a Keyed Transposition with a Rail Fence Cipher step
string encryptHybrid(string text, vector<int> key, int rails) {
    // 1. Keyed Transposition
    int blockSize = key.size();
    while (text.length() % blockSize != 0) text += 'X';
    string intermediate = "";
    for (size_t i = 0; i < text.length(); i += blockSize) {
        string block = text.substr(i, blockSize);
        string permuted = block;
        for (int k = 0; k < blockSize; k++) permuted[k] = block[key[k]];
        intermediate += permuted;
    }
    // 2. Rail Fence
    vector<string> fence(rails, "");
    int rail = 0; bool down = true;
    for (char c : intermediate) {
        fence[rail] += c;
        if (rail == 0) down = true;
        else if (rail == rails - 1) down = false;
        rail += down ? 1 : -1;
    }
    string ciphertext = "";
    for (string r : fence) ciphertext += r;
    return ciphertext;
}

string decryptHybrid(string text, vector<int> key, int rails) {
    // 1. Decrypt Rail Fence
    vector<int> railLengths(rails, 0);
    int rail = 0; bool down = true;
    for (size_t i = 0; i < text.length(); i++) {
        railLengths[rail]++;
        if (rail == 0) down = true;
        else if (rail == rails - 1) down = false;
        rail += down ? 1 : -1;
    }
    vector<string> fence(rails); int idx = 0;
    for (int r = 0; r < rails; r++) {
        fence[r] = text.substr(idx, railLengths[r]);
        idx += railLengths[r];
    }
    string intermediate = "";
    rail = 0; down = true; vector<int> ptr(rails, 0);
    for (size_t i = 0; i < text.length(); i++) {
        intermediate += fence[rail][ptr[rail]++];
        if (rail == 0) down = true;
        else if (rail == rails - 1) down = false;
        rail += down ? 1 : -1;
    }
    cout << intermediate << endl; // Debug: Show intermediate after Rail Fence decryption   
    // 2. Decrypt Keyed Transposition
    int blockSize = key.size();
    string plaintext = "";
    for (size_t i = 0; i < intermediate.length(); i += blockSize) {
        string block = intermediate.substr(i, blockSize);
        string original = block;
        for (int k = 0; k < blockSize; k++) original[key[k]] = block[k];
        plaintext += original;
    }
    return plaintext;
}

int main() {
    string text = "ATTACKATDAWN";
    vector<int> key = {3, 1, 4, 2};
    int rails = 2;
    
    string encrypted = encryptHybrid(text, key, rails);
    string decrypted = decryptHybrid(encrypted, key, rails);
    
    cout << "--- Hybrid Transposition ---" << endl;
    cout << "Original:  " << text << endl;
    cout << "Encrypted: " << encrypted << endl;
    cout << "Decrypted: " << decrypted << endl;
    return 0;
}