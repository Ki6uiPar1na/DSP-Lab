#include <iostream>
#include <vector>

using namespace std;

// Extended Euclidean Algorithm to find modular inverse coefficients
long long extGCD(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long gcd = extGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return gcd;
}

// Modular Exponentiation: (base^exp) mod mod
long long powerMod(long long base, long long exp, long long mod) {
    long long res = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

// Encryption: C = m^2 mod n
long long encryptRabin(long long m, long long n) {
    return (m * m) % n;
}

// Decryption produces 4 roots (CRT)
vector<long long> decryptRabin(long long C, long long p, long long q) {
    long long n = p * q;
    
    // Step 1: Modular Square Roots mod p and mod q (using shortcut p, q == 3 mod 4)
    long long r = powerMod(C, (p + 1) / 4, p);
    long long s = powerMod(C, (q + 1) / 4, q);
    
    // Step 2: Use Extended GCD to find c, d such that c*p + d*q = 1
    long long c, d;
    extGCD(p, q, c, d);
    
    // Step 3: Compute the 4 roots using CRT
    long long r1 = (r * d * q + s * c * p) % n;
    if (r1 < 0) r1 += n;
    
    long long r2 = n - r1;
    
    long long r3 = (r * d * q - s * c * p) % n;
    if (r3 < 0) r3 += n;
    
    long long r4 = n - r3;
    
    return {r1, r2, r3, r4};
}

int main() {
    // Private Key (Primes congruent to 3 mod 4)
    long long p = 7;
    long long q = 11;
    long long n = p * q; // Public Key modulus
    
    long long m = 20; // Plaintext message
    
    long long cipher = encryptRabin(m, n);
    cout << "Rabin Cryptosystem:\n";
    cout << "Ciphertext: " << cipher << endl;
    
    vector<long long> decrypted = decryptRabin(cipher, p, q);
    cout << "The 4 possible decrypted plaintexts are: ";
    for (long long val : decrypted) {
        cout << val << " ";
    }
    cout << "\n\n";
    return 0;
}