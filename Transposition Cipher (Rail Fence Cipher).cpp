#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
    
    // Step 1: Trace out the zig-zag path using placeholder stars '*'
    for (size_t i = 0; i < ciphertext.length(); i++) {
        fence[row][i] = '*';
        if (row == 0 || row == rails - 1) down = !down;
        row += down ? 1 : -1;
    }
    
    // Step 2: Fill the path sequentially with the ciphertext letters
    int strIdx = 0;
    for (int r = 0; r < rails; r++) {
        for (size_t c = 0; c < ciphertext.length(); c++) {
            if (fence[r][c] == '*' && strIdx < ciphertext.length()) {
                fence[r][c] = ciphertext[strIdx++];
            }
        }
    }
    
    // Step 3: Re-read the zig-zag path to reconstruct the plaintext
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

int main() {
    string msg = "MEET ME AT THE PARK";
    int rails = 3;
    
    string cipher = encryptRailFence(msg, rails);
    cout << "Rail Fence Cipher:\n";
    cout << "Ciphertext: " << cipher << endl;
    cout << "Decrypted:  " << decryptRailFence(cipher, rails) << "\n\n";
    return 0;
}