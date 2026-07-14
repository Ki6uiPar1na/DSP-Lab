#include <iostream>
#include <vector>

using namespace std;

long long modInverse(long long a, long long m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

int main() {
    // Private Key: Superincreasing sequence w, modulus q, multiplier r
    vector<int> w = {2, 7, 11, 21, 42, 89};
    int sum = 0;
    for (int x : w) sum += x;
    
    int q = 180; // q must be greater than total sum
    int r = 77;  // r must be coprime with q
    
    // Public Key Generation (b = (w * r) mod q)
    vector<int> b(w.size());
    for (size_t i = 0; i < w.size(); i++) {
        b[i] = (w[i] * r) % q;
    }
    
    // Plaintext bits (6 bits matching size of w)
    vector<int> plaintext = {1, 0, 1, 1, 0, 1}; // 101101
    
    // Encryption
    int ciphertext = 0;
    for (size_t i = 0; i < plaintext.size(); i++) {
        if (plaintext[i] == 1) {
            ciphertext += b[i];
        }
    }
    
    // Decryption
    int rInv = modInverse(r, q);
    int tc = (ciphertext * rInv) % q; // Solvable superincreasing knapsack value
    
    vector<int> decrypted(w.size(), 0);
    for (int i = w.size() - 1; i >= 0; i--) {
        if (tc >= w[i]) {
            decrypted[i] = 1;
            tc -= w[i];
        }
    }
    
    cout << "--- Knapsack Cryptosystem ---" << endl;
    cout << "Original Plaintext bits: ";
    for (int bit : plaintext) cout << bit;
    cout << endl;
    
    cout << "Encrypted Cipher value:  " << ciphertext << endl;
    
    cout << "Decrypted Plaintext bits: ";
    for (int bit : decrypted) cout << bit;
    cout << endl;
    
    return 0;
}