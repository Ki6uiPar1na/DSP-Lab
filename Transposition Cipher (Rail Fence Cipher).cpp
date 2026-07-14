#include <iostream>
#include <string>
#include <vector>

using namespace std;

string encryptRailFence(string text, int rails) {
    vector<string> fence(rails, "");
    int rail = 0;
    bool down = true;
    
    for (char c : text) {
        fence[rail] += c;
        if (rail == 0) down = true;
        else if (rail == rails - 1) down = false;
        
        rail += down ? 1 : -1;
    }
    
    string ciphertext = "";
    for (string r : fence) ciphertext += r;
    return ciphertext;
}

string decryptRailFence(string text, int rails) {
    vector<int> railLengths(rails, 0);
    int rail = 0;
    bool down = true;
    
    for (size_t i = 0; i < text.length(); i++) {
        railLengths[rail]++;
        if (rail == 0) down = true;
        else if (rail == rails - 1) down = false;
        rail += down ? 1 : -1;
    }
    
    vector<string> fence(rails);
    int idx = 0;
    for (int r = 0; r < rails; r++) {
        fence[r] = text.substr(idx, railLengths[r]);
        idx += railLengths[r];
    }
    
    string plaintext = "";
    rail = 0;
    down = true;
    vector<int> ptr(rails, 0);
    for (size_t i = 0; i < text.length(); i++) {
        plaintext += fence[rail][ptr[rail]++];
        if (rail == 0) down = true;
        else if (rail == rails - 1) down = false;
        rail += down ? 1 : -1;
    }
    return plaintext;
}

int main() {
    string text = "ATTACKATDAWN";
    int rails = 2;
    
    string encrypted = encryptRailFence(text, rails);
    string decrypted = decryptRailFence(encrypted, rails);
    
    cout << "--- Rail Fence Cipher ---" << endl;
    cout << "Original:  " << text << endl;
    cout << "Encrypted: " << encrypted << endl;
    cout << "Decrypted: " << decrypted << endl;
    return 0;
}