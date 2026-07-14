#include <iostream>
#include <cmath>

using namespace std;

// Greatest common divisor
long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

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

int main() {
    // Choose two prime numbers
    long long p = 61;
    long long q = 53;
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    
    // Choose e such that 1 < e < phi and coprime with phi
    long long e = 17;
    while (e < phi) {
        if (gcd(e, phi) == 1) break;
        e++;
    }
    
    // Calculate private key d (multiplicative inverse of e mod phi)
    long long d = 1;
    while ((d * e) % phi != 1) {
        d++;
    }
    
    long long message = 42; // Numerical message
    long long encrypted = power(message, e, n);
    long long decrypted = power(encrypted, d, n);
    
    cout << "--- RSA Cryptosystem ---" << endl;
    cout << "Public Key:  {" << e << ", " << n << "}" << endl;
    cout << "Private Key: {" << d << ", " << n << "}" << endl;
    cout << "Original:    " << message << endl;
    cout << "Encrypted:   " << encrypted << endl;
    cout << "Decrypted:   " << decrypted << endl;
    return 0;
}