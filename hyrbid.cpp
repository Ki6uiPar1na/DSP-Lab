#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// ==========================================
// 1. KEYLESS TRANSPOSITION (Rail Fence)
// ==========================================

string encryptRailFence(string text, int rails) {
    string prep = "";
    for (char c : text) {
        if (isalpha(c)) prep += toupper(c);
    }
    
    vector<string> fence(rails, string(prep.length(), ' '));
    int row = 0;
    bool down = false;
    
    for (size_t i = 0; i < prep.length(); i++) {
        fence[row][i] = prep[i];
        if (row == 0 || row == rails - 1) down = !down;
        row += down ? 1 : -1;
    }
    
    string ciphertext = "";
    for (int r = 0; r < rails; r++) {
        for (size_t c = 0; c < prep.length(); c++) {
            if (fence[r][c] != ' ') ciphertext += fence[r][c];
        }
    }
    return ciphertext;
}

string decryptRailFence(string ciphertext, int rails) {
    vector<string> fence(rails, string(ciphertext.length(), ' '));
    int row = 0;
    bool down = false;
    
    // Step 1: Trace the zig-zag path using '*'
    for (size_t i = 0; i < ciphertext.length(); i++) {
        fence[row][i] = '*';
        if (row == 0 || row == rails - 1) down = !down;
        row += down ? 1 : -1;
    }
    
    // Step 2: Fill the path with ciphertext letters
    int strIdx = 0;
    for (int r = 0; r < rails; r++) {
        for (size_t c = 0; c < ciphertext.length(); c++) {
            if (fence[r][c] == '*' && strIdx < ciphertext.length()) {
                fence[r][c] = ciphertext[strIdx++];
            }
        }
    }
    
    // Step 3: Reconstruct the plaintext
    string plaintext = "";
    row = 0;
    down = false;
    for (size_t i = 0; i < ciphertext.length(); i++) {
        plaintext += fence[row][i];
        if (row == 0 || row == rails - 1) down = !down;
        row += down ? 1 : -1;
    }
    return plaintext;
}


// ==========================================
// 2. KEYED TRANSPOSITION (Columnar)
// ==========================================

// Determines the alphabetical reading order of the key
vector<int> getColumnOrder(string key) {
    int n = key.length();
    vector<int> order(n);
    map<char, vector<int>> charIndices;
    
    for (int i = 0; i < n; i++) {
        charIndices[toupper(key[i])].push_back(i);
    }
    
    int colNum = 0;
    for (auto const& [ch, indices] : charIndices) {
        for (int idx : indices) {
            order[idx] = colNum++;
        }
    }
    return order;
}

string encryptKeyedTransposition(string plaintext, string key) {
    string prep = "";
    for (char c : plaintext) {
        if (isalpha(c)) prep += toupper(c);
    }
    
    int colCount = key.length();
    // Pad the string so it fits perfectly in a rectangular grid
    while (prep.length() % colCount != 0) prep += 'X'; 
    
    int rowCount = prep.length() / colCount;
    vector<string> grid(rowCount, string(colCount, ' '));
    
    int strIdx = 0;
    for (int r = 0; r < rowCount; r++) {
        for (int c = 0; c < colCount; c++) {
            grid[r][c] = prep[strIdx++];
        }
    }
    
    vector<int> order = getColumnOrder(key);
    string ciphertext = "";
    
    for (int targetOrder = 0; targetOrder < colCount; targetOrder++) {
        int targetColIdx = -1;
        for (int j = 0; j < colCount; j++) {
            if (order[j] == targetOrder) {
                targetColIdx = j;
                break;
            }
        }
        for (int r = 0; r < rowCount; r++) {
            ciphertext += grid[r][targetColIdx];
        }
    }
    return ciphertext;
}

string decryptKeyedTransposition(string ciphertext, string key) {
    int colCount = key.length();
    int rowCount = ciphertext.length() / colCount;
    
    vector<string> grid(rowCount, string(colCount, ' '));
    vector<int> order = getColumnOrder(key);
    
    int strIdx = 0;
    for (int targetOrder = 0; targetOrder < colCount; targetOrder++) {
        int targetColIdx = -1;
        for (int j = 0; j < colCount; j++) {
            if (order[j] == targetOrder) {
                targetColIdx = j;
                break;
            }
        }
        for (int r = 0; r < rowCount; r++) {
            grid[r][targetColIdx] = ciphertext[strIdx++];
        }
    }
    
    string plaintext = "";
    for (int r = 0; r < rowCount; r++) {
        for (int c = 0; c < colCount; c++) {
            plaintext += grid[r][c];
        }
    }
    return plaintext;
}


// ==========================================
// 3. HYBRID TRANSPOSITION SYSTEM
// ==========================================

string encryptHybrid(string plaintext, int rails, string key) {
    // Stage 1: Keyless Rail Fence Transposition
    string intermediate = encryptRailFence(plaintext, rails);
    
    // Stage 2: Keyed Columnar Transposition
    string finalCiphertext = encryptKeyedTransposition(intermediate, key);
    
    return finalCiphertext;
}

string decryptHybrid(string ciphertext, int rails, string key) {
    // Stage 1: Undo Keyed Columnar Transposition
    string intermediate = decryptKeyedTransposition(ciphertext, key);
    
    // Stage 2: Undo Keyless Rail Fence Transposition
    string originalPlaintext = decryptRailFence(intermediate, rails);
    
    return originalPlaintext;
}

int main() {
    string msg = "DEFEND THE EAST WALL";
    int rails = 3;         // Keyless Parameter
    string key = "SECURE";  // Keyed Parameter
    
    cout << "--- Hybrid Transposition Cipher ---" << endl;
    cout << "Original Message:  " << msg << endl;
    cout << "Step 1 Rails (Depth): " << rails << endl;
    cout << "Step 2 Key Word:      " << key << endl;
    
    // Encrypt
    string cipher = encryptHybrid(msg, rails, key);
    cout << "\nFinal Ciphertext:  " << cipher << endl;
    
    // Decrypt
    string decrypted = decryptHybrid(cipher, rails, key);
    cout << "Decrypted Message: " << decrypted << "\n\n";
    
    return 0;
}