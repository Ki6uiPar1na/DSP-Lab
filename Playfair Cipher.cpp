#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void generateMatrix(string key, char matrix[5][5]) {
    bool present[26] = {false};
    present['J' - 'A'] = true; // Merge I and J
    
    string temp = "";
    for (char c : key) {
        if (isalpha(c)) {
            char up = toupper(c);
            if (up == 'J') up = 'I';
            if (!present[up - 'A']) {
                temp += up;
                present[up - 'A'] = true;
            }
        }
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue;
        if (!present[c - 'A']) {
            temp += c;
        }
    }
    int idx = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = temp[idx++];
        }
    }
}

void findPosition(char matrix[5][5], char c, int &row, int &col) {
    if (c == 'J') c = 'I';
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == c) {
                row = i;
                col = j;
                return;
            }
        }
    }
}

string encryptPlayfair(string text, string key) {
    char matrix[5][5];
    generateMatrix(key, matrix);
    
    // Sanitize and pair up the text
    string clean = "";
    for (char c : text) {
        if (isalpha(c)) clean += toupper(c);
    }
    
    string paired = "";
    for (size_t i = 0; i < clean.length(); i++) {
        paired += clean[i];
        if (i + 1 < clean.length()) {
            if (clean[i] == clean[i+1]) {
                paired += 'X'; // Padding duplicate
            } else {
                paired += clean[++i];
            }
        } else {
            paired += 'X'; // Pad trailing odd character
        }
    }
    
    string ciphertext = "";
    for (size_t i = 0; i < paired.length(); i += 2) {
        int r1, c1, r2, c2;
        findPosition(matrix, paired[i], r1, c1);
        findPosition(matrix, paired[i+1], r2, c2);
        
        if (r1 == r2) {
            ciphertext += matrix[r1][(c1 + 1) % 5];
            ciphertext += matrix[r2][(c2 + 1) % 5];
        } else if (c1 == c2) {
            ciphertext += matrix[(r1 + 1) % 5][c1];
            ciphertext += matrix[(r2 + 1) % 5][c2];
        } else {
            ciphertext += matrix[r1][c2];
            ciphertext += matrix[r2][c1];
        }
    }
    return ciphertext;
}

string decryptPlayfair(string text, string key) {
    char matrix[5][5];
    generateMatrix(key, matrix);
    
    string plaintext = "";
    for (size_t i = 0; i < text.length(); i += 2) {
        int r1, c1, r2, c2;
        findPosition(matrix, text[i], r1, c1);
        findPosition(matrix, text[i+1], r2, c2);
        
        if (r1 == r2) {
            plaintext += matrix[r1][(c1 + 4) % 5];
            plaintext += matrix[r2][(c2 + 4) % 5];
        } else if (c1 == c2) {
            plaintext += matrix[(r1 + 4) % 5][c1];
            plaintext += matrix[(r2 + 4) % 5][c2];
        } else {
            plaintext += matrix[r1][c2];
            plaintext += matrix[r2][c1];
        }
    }
    return plaintext;
}

int main() {
    string key = "MONARCHY";
    string text = "INSTRUMENTS";
    
    string encrypted = encryptPlayfair(text, key);
    string decrypted = decryptPlayfair(encrypted, key);
    
    cout << "--- Playfair Cipher ---" << endl;
    cout << "Original:  " << text << endl;
    cout << "Encrypted: " << encrypted << endl;
    cout << "Decrypted: " << decrypted << endl;
    return 0;
}