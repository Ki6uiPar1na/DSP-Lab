#include <iostream>
#include <string>

using namespace std;

// Mock Round function F: (R ^ K)
char roundFunction(char r, char key) {
    return r ^ key;
}

pair<char, char> feistelRound(char L, char R, char key) {
    char newL = R;
    char newR = L ^ roundFunction(R, key);
    return {newL, newR};
}

string encryptFeistel(string text, string keys) {
    if (text.length() % 2 != 0) text += 'X';
    string result = "";
    for (size_t i = 0; i < text.length(); i += 2) {
        char L = text[i];
        char R = text[i+1];
        
        // 2 rounds of Feistel
        for (char key : keys) {
            auto out = feistelRound(L, R, key);
            L = out.first;
            R = out.second;
        }
        // Final swap undone
        result += R;
        result += L;
    }
    return result;
}

string decryptFeistel(string text, string keys) {
    string result = "";
    for (size_t i = 0; i < text.length(); i += 2) {
        char L = text[i];
        char R = text[i+1];
        
        // Decryption uses keys in reverse order
        for (int r = keys.length() - 1; r >= 0; r--) {
            auto out = feistelRound(L, R, keys[r]);
            L = out.first;
            R = out.second;
        }
        result += R;
        result += L;
    }
    return result;
}

int main() {
    string text = "FEISTELSTRUCT";
    string roundKeys = "AB"; // Two-round mock keys
    
    string encrypted = encryptFeistel(text, roundKeys);
    string decrypted = decryptFeistel(encrypted, roundKeys);
    
    cout << "--- Feistel Cipher Structure ---" << endl;
    cout << "Original:  " << text << endl;
    cout << "Encrypted: (Hex dump output) ";
    for (char c : encrypted) printf("\\x%02X", (unsigned char)c);
    cout << endl;
    cout << "Decrypted: " << decrypted << endl;
    return 0;
}