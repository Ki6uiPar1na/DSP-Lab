#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

// Compute modular multiplicative inverse
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if (((a % m) * (x % m)) % m == 1) return x;
    }
    return -1;
}

// Encrypt binary message vector using Public Key B
int encryptKnapsack(const vector<int>& p, const vector<int>& B) {
    int ciphertext = 0;
    for (size_t i = 0; i < p.size(); i++) {
        ciphertext += p[i] * B[i];
    }
    return ciphertext;
}

// Decrypt back to binary message vector using Private Key params
vector<int> decryptKnapsack(int C, const vector<int>& W, int q, int m) {
    int m_inv = modInverse(m, q);
    int C_prime = (C * m_inv) % q;
    
    vector<int> p(W.size(), 0);
    // Solved greedily back-to-front because W is superincreasing
    for (int i = W.size() - 1; i >= 0; i--) {
        if (W[i] <= C_prime) {
            p[i] = 1;
            C_prime -= W[i];
        }
    }
    return p;
}

int main() {
    // Private Key Parameters
    vector<int> W = {2, 3, 7, 14, 30}; // Superincreasing sequence
    int q = 57;                         // modulus (q > sum(W))
    int m = 13;                         // multiplier (gcd(m, q) == 1)
    
    // Generate Public Key B: B_i = (W_i * m) mod q
    vector<int> B(W.size());
    for (size_t i = 0; i < W.size(); i++) {
        B[i] = (W[i] * m) % q;
    }
    
    vector<int> msg = {1, 1, 0, 1, 0}; // Binary message vector
    
    int cipher = encryptKnapsack(msg, B);
    cout << "Merkle-Hellman Knapsack:\n";
    cout << "Ciphertext value: " << cipher << endl;
    
    vector<int> decrypted = decryptKnapsack(cipher, W, q, m);
    cout << "Decrypted binary vector: ";
    for (int val : decrypted) cout << val << " ";
    cout << "\n\n";
    return 0;
}