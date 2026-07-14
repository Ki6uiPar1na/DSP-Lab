#include <iostream>

using namespace std;

// Modular exponentiation: (base^exp) % mod
long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return res;
}

// Extended Euclidean Algorithm to solve a*x + b*y = gcd(a, b)
void extgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1; y = 0;
        return;
    }
    long long x1, y1;
    extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
}

int main() {
    // User Provided Parameters
    long long p = 7;
    long long q = 11;
    long long n = p * q; // Public key n = 77
    long long m = 20;    // Original Plaintext
    
    cout << "--- Rabin Cryptosystem Verification ---" << endl;
    cout << "Primes: p = " << p << ", q = " << q << " (Both congruent to 3 mod 4)" << endl;
    cout << "Public Key (n): " << n << endl;
    cout << "Original Plaintext (M): " << m << "\n\n";
    
    // --- ENCRYPTION ---
    // C = M^2 mod n
    long long c = (m * m) % n;
    cout << "[Encryption] Computed Ciphertext (C) = " << c << "\n\n";
    
    // --- DECRYPTION ---
    // Find square roots of C modulo p and modulo q
    long long r = power(c, (p + 1) / 4, p);
    long long s = power(c, (q + 1) / 4, q);
    
    // Use Extended Euclidean Algorithm to find CRT coefficients
    long long yp, yq;
    extgcd(p, q, yp, yq);
    
    // Calculate the 4 distinct square roots modulo n
    long long d1 = (yp * p * s + yq * q * r) % n;
    long long d2 = (yp * p * s - yq * q * r) % n;
    long long d3 = (-yp * p * s + yq * q * r) % n;
    long long d4 = (-yp * p * s - yq * q * r) % n;
    
    // Normalize negative results to stay within [0, n-1]
    long long roots[4];
    roots[0] = (d1 + n) % n;
    roots[1] = (d2 + n) % n;
    roots[2] = (d3 + n) % n;
    roots[3] = (d4 + n) % n;
    
    cout << "[Decryption] The 4 mathematically valid plaintext options are:" << endl;
    bool foundMatch = false;
    for (int i = 0; i < 4; i++) {
        cout << "  Option " << i + 1 << ": " << roots[i];
        if (roots[i] == m) {
            cout << " <-- MATCHES YOUR ORIGINAL PLAINTEXT!";
            foundMatch = true;
        }
        cout << endl;
    }
    
    if (foundMatch) {
        cout << "\nSUCCESS: The original message was successfully recovered!" << endl;
    } else {
        cout << "\nFAILURE: Message not found." << endl;
    }
    
    return 0;
}