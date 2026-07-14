#include <iostream>
#include <vector>

using namespace std;

// Extended Euclidean Algorithm
long long extGCD(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    long long x1, y1;
    long long gcd = extGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return gcd;
}

// Modular inverse
long long modInverse(long long e, long long phi) {
    long long x, y;
    extGCD(e, phi, x, y);
    return (x % phi + phi) % phi;
}

// Modular Exponentiation (base^exp) mod mod
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

int main() {
    // 1. Pick primes
    long long p = 3;
    long long q = 11;
    
    // 2. Compute modulus n
    long long n = p * q; // 33
    
    // 3. Compute Totient phi(n)
    long long phi = (p - 1) * (q - 1); // 20
    
    // 4. Choose public exponent e (must be coprime to 20)
    long long e = 7;
    
    // 5. Calculate private exponent d
    long long d = modInverse(e, phi); // 3
    
    long long message = 2;
    
    // Encryption: C = M^e mod n
    long long cipher = powerMod(message, e, n);
    // Decryption: M = C^d mod n
    long long decrypted = powerMod(cipher, d, n);
    
    cout << "RSA Cryptosystem:\n";
    cout << "Public Key: (" << e << ", " << n << ")\n";
    cout << "Private Key: (" << d << ", " << n << ")\n";
    cout << "Ciphertext: " << cipher << endl;
    cout << "Decrypted:  " << decrypted << "\n\n";
    
    return 0;
}