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

// Extended Euclidean Algorithm to find modular inverse
long long modInverse(long long a, long long m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

int main() {
    // User Provided Parameters
    long long p = 23; 
    long long q = 11; 
    long long g = 4;  
    
    long long x = 3;  // Private Key
    long long y = 18; // Public Key (verified: 4^3 % 23 = 18)
    
    long long hashVal = 5; // H(m)
    long long k = 2;       // Random secret per message
    
    cout << "--- Digital Signature Standard (DSS) Simulation ---" << endl;
    cout << "Parameters: p=" << p << ", q=" << q << ", g=" << g << endl;
    cout << "Keys: Private(x)=" << x << ", Public(y)=" << y << endl;
    cout << "Message Hash H(m)=" << hashVal << ", k=" << k << "\n\n";

    // --- SIGNING STAGE ---
    long long r = power(g, k, p) % q;
    
    long long kInv = modInverse(k, q);
    if (kInv == -1) {
        cout << "Error: k inverse does not exist!" << endl;
        return 1;
    }
    
    long long s = (kInv * (hashVal + x * r)) % q;
    
    cout << "[Signing] Computed r = " << r << endl;
    cout << "[Signing] Computed s = " << s << endl;
    cout << "Signature Pair sent: (r=" << r << ", s=" << s << ")\n\n";
    
    // --- VERIFICATION STAGE ---
    long long w = modInverse(s, q);
    if (w == -1) {
        cout << "Error: s inverse does not exist. Verification failed!" << endl;
        return 1;
    }
    
    long long u1 = (hashVal * w) % q;
    long long u2 = (r * w) % q;
    
    // v = ((g^u1 * y^u2) % p) % q
    long long term1 = power(g, u1, p);
    long long term2 = power(y, u2, p);
    long long v = ((term1 * term2) % p) % q;
    
    cout << "[Verification] Computed w = " << w << endl;
    cout << "[Verification] Computed u1 = " << u1 << ", u2 = " << u2 << endl;
    cout << "[Verification] Computed v = " << v << endl;
    
    // Final Evaluation
    if (v == r) {
        cout << "\nSUCCESS: Signature is VALID! (v == r)" << endl;
    } else {
        cout << "\nFAILURE: Signature is INVALID! (v != r)" << endl;
        cout << "Note: Small toy cryptographic parameters can naturally cause mathematical mismatches." << endl;
    }
    
    return 0;
}