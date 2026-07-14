#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

// 1. DES Expansion Permutation Table (Stretches 32 bits to 48 bits)
const int E_Table[48] = {
    32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
     8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1
};

// 2. Sample DES S-Box 1 (Reduces 6 bits to 4 bits)
// Real DES uses 8 distinct S-Boxes; we implement one to showcase the exact mapping logic.
const int S1[4][16] = {
    {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
    { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
    { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
    {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}
};

// 3. DES Straight Permutation Table (P-Box: Scrambles 32 bits)
const int P_Table[32] = {
    16,  7, 20, 21, 29, 12, 28, 17,
     1, 15, 23, 26,  5, 18, 31, 10,
     2,  8, 24, 14, 32, 27,  3,  9,
    19, 13, 30,  6, 22, 11,  4, 25
};

// Helper: Print a 32-bit integer block in Hexadecimal
void printBitsAsHex(string label, uint32_t block) {
    cout << label << ": 0x" << hex << setw(8) << setfill('0') << block << endl;
}

// The core DES Round Function F(R, K)
uint32_t desRoundFunctionF(uint32_t R, uint64_t roundKey48Bit) {
    
    // --- STEP 1: Expansion Permutation (32-bit R -> 48-bit Expanded block) ---
    uint64_t expandedR = 0;
    for (int i = 0; i < 48; i++) {
        // Extract the bit value at the position specified by E_Table
        int bitPos = 32 - E_Table[i]; 
        uint64_t bit = (R >> bitPos) & 1;
        expandedR |= (bit << (47 - i));
    }
    
    // --- STEP 2: XOR with the 48-bit Round Key ---
    uint64_t xorResult = expandedR ^ roundKey48Bit;
    
    // --- STEP 3: S-Box Substitution (48 bits -> 32 bits via 8 blocks of 6 bits) ---
    uint32_t sBoxOutput = 0;
    // We iterate through the first 6-bit chunk out of the 8 blocks as an exam calculation example
    for (int box = 0; box < 8; box++) {
        // Isolate 6 bits for the current S-Box
        int shiftAmount = 42 - (box * 6);
        uint8_t sixBits = (xorResult >> shiftAmount) & 0x3F;
        
        // S-Box Addressing Rule: 
        // Outer bits (1 and 6) = Row index. Inner bits (2, 3, 4, 5) = Column index.
        int row = ((sixBits & 0x20) >> 4) | (sixBits & 0x01);
        int col = (sixBits & 0x1E) >> 1;
        
        uint8_t fourBitsOut = S1[row][col]; // Using S1 as the baseline matrix lookup
        
        sBoxOutput |= (fourBitsOut << (28 - (box * 4)));
    }
    
    // --- STEP 4: P-Box Permutation (Straight 32-bit Permutation) ---
    uint32_t finalPBoxOutput = 0;
    for (int i = 0; i < 32; i++) {
        int bitPos = 32 - P_Table[i];
        uint32_t bit = (sBoxOutput >> bitPos) & 1;
        finalPBoxOutput |= (bit << (31 - i));
    }
    
    return finalPBoxOutput;
}

int main() {
    // Example Input: Right half of a 64-bit plaintext block (32 bits)
    uint32_t R_half = 0x3F2A1B0C; 
    
    // Example Input: Sub-key generated for the current round (48 bits used)
    uint64_t roundKey = 0x1A2B3C4D5E6F; 
    
    cout << "--- DES Round Function Execution Pipeline ---\n\n";
    printBitsAsHex("Initial Right Block (R)", R_half);
    cout << "Round Sub-Key (K):    0x" << hex << roundKey << endl;
    
    // Execute F(R, K)
    uint32_t f_output = desRoundFunctionF(R_half, roundKey);
    
    cout << "\n---------------------------------------------\n";
    printBitsAsHex("Output of F(R, K) (Ready to XOR with Left)", f_output);
    
    return 0;
}