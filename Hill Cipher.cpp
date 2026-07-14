#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Find Modular Inverse of a determinant modulo 26
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

// Compute matrix inverse modulo 26 for 2x2 matrix
bool invertMatrix(int key[2][2], int inv[2][2]) {
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
    if (det < 0) det += 26;
    
    int detInv = modInverse(det, 26);
    if (detInv == -1) return false; // Key matrix is not invertible
    
    inv[0][0] = (key[1][1] * detInv) % 26;
    inv[0][1] = (-key[0][1] * detInv) % 26;
    inv[1][0] = (-key[1][0] * detInv) % 26;
    inv[1][1] = (key[0][0] * detInv) % 26;
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (inv[i][j] < 0) inv[i][j] += 26;
        }
    }
    return true;
}

string encryptHill(string text, int key[2][2]) {
    string clean = "";
    for (char c : text) if (isalpha(c)) clean += toupper(c);
    if (clean.length() % 2 != 0) clean += 'X'; // Pad with X
    
    string ciphertext = "";
    for (size_t i = 0; i < clean.length(); i += 2) {
        int p1 = clean[i] - 'A';
        int p2 = clean[i+1] - 'A';
        
        ciphertext += ((key[0][0] * p1 + key[0][1] * p2) % 26) + 'A';
        ciphertext += ((key[1][0] * p1 + key[1][1] * p2) % 26) + 'A';
    }
    return ciphertext;
}

string decryptHill(string text, int key[2][2]) {
    int inv[2][2];
    if (!invertMatrix(key, inv)) return "Error: Matrix not invertible!";
    
    string plaintext = "";
    for (size_t i = 0; i < text.length(); i += 2) {
        int c1 = text[i] - 'A';
        int c2 = text[i+1] - 'A';
        
        plaintext += ((inv[0][0] * c1 + inv[0][1] * c2) % 26) + 'A';
        plaintext += ((inv[1][0] * c1 + inv[1][1] * c2) % 26) + 'A';
    }
    return plaintext;
}

int main() {
    string text = "HILL";
    int key[2][2] = { {3, 3}, {2, 5} }; // Determinant is 9, coprime to 26
    
    string encrypted = encryptHill(text, key);
    string decrypted = decryptHill(encrypted, key);
    
    cout << "--- Hill Cipher (2x2) ---" << endl;
    cout << "Original:  " << text << endl;
    cout << "Encrypted: " << encrypted << endl;
    cout << "Decrypted: " << decrypted << endl;
    return 0;
}