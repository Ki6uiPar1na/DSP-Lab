#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

// Helper to sanitize text (uppercase only, removes spaces/punctuation for classical autokey)
string cleanText(string text) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) result += toupper(c);
    }
    return result;
}

string encryptAutokey(string text, int seedKey) {
    string pText = cleanText(text);
    string cText = "";
    int currentKey = seedKey;

    for (size_t i = 0; i < pText.length(); i++) {
        int pVal = pText[i] - 'A';
        int cVal = (pVal + currentKey) % 26;
        cText += (cVal + 'A');
        
        // The current plaintext character becomes the key for the next character
        currentKey = pVal; 
    }
    return cText;
}

string decryptAutokey(string cText, int seedKey) {
    string pText = "";
    int currentKey = seedKey;

    for (size_t i = 0; i < cText.length(); i++) {
        int cVal = cText[i] - 'A';
        int pVal = (cVal - currentKey + 26) % 26;
        pText += (pVal + 'A');
        
        // The decrypted plaintext character becomes the key for the next character
        currentKey = pVal;
    }
    return pText;
}

int main() {
    string message = "HELLO";
    int seedKey = 7; // Numerical shift key for the first character

    string encrypted = encryptAutokey(message, seedKey);
    string decrypted = decryptAutokey(encrypted, seedKey);

    cout << "--- Autokey Cipher ---" << endl;
    cout << "Original:  " << message << endl;
    cout << "Encrypted: " << encrypted << endl;
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}