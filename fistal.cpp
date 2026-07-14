#include <iostream>
#include <iomanip>

using namespace std;

// A sample non-invertible Round Function F(R, K)
// In a Feistel cipher, this function can be completely chaotic and one-way.
uint32_t roundFunctionF(uint32_t R, uint32_t K) {
    // A simple mix of bitwise rotation, multiplication, and XOR
    return ((R << 5) | (R >> 27)) ^ (R * K) ^ 0x55555555;
}

// Helper: Print the Left and Right halves combined as a full 64-bit block
void printBlock(string label, uint32_t L, uint32_t R) {
    uint64_t fullBlock = ((uint64_t)L << 32) | R;
    cout << label << ": 0x" << hex << setw(16) << setfill('0') << fullBlock 
         << " [L: 0x" << setw(8) << L << ", R: 0x" << setw(8) << R << "]" << endl;
}

// Generic Feistel Round Execution
void feistelRound(uint32_t &L, uint32_t &R, uint32_t key, bool isFinalRound) {
    uint32_t nextL = R;
    uint32_t nextR = L ^ roundFunctionF(R, key);
    
    if (isFinalRound) {
        // The Final Round Trick: Do NOT swap the halves in the very last round.
        // This allows the decryption logic to use the exact same algorithm structure.
        L = nextR;
        R = nextL;
    } else {
        L = nextL;
        R = nextR;
    }
}

int main() {
    // Example Input: A 64-bit plaintext block split into two 32-bit halves
    uint32_t L_half = 0xABCDEF12; 
    uint32_t R_half = 0x3456789A;
    
    // Example Sub-keys generated for Round 1 and Round 2
    uint32_t K1 = 0x11111111;
    uint32_t K2 = 0x22222222;
    
    cout << "--- STARTING FEISTEL ENCRYPTION ---" << endl;
    printBlock("Initial Plaintext", L_half, R_half);
    
    // --- ENCRYPTION PIPELINE ---
    // Round 1
    feistelRound(L_half, R_half, K1, false);
    printBlock("After Round 1    ", L_half, R_half);
    
    // Round 2 (Final Round - No Swap)
    feistelRound(L_half, R_half, K2, true);
    printBlock("Ciphertext (R2)  ", L_half, R_half);
    
    cout << "\n--- STARTING FEISTEL DECRYPTION ---" << endl;
    cout << "(Using the exact same function framework, but reversing subkeys: K2 then K1)\n" << endl;
    
    // --- DECRYPTION PIPELINE ---
    // Round 1 (Uses K2)
    feistelRound(L_half, R_half, K2, false);
    printBlock("After Decrypt R1 ", L_half, R_half);
    
    // Round 2 (Final Round - Uses K1, No Swap)
    feistelRound(L_half, R_half, K1, true);
    printBlock("Recovered Text   ", L_half, R_half);
    
    return 0;
}