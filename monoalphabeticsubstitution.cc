#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Define the plaintext and ciphertext alphabets
#define ALPHABET_SIZE 26

void encrypt(char *text, const char *cipher_alphabet) {
    for (int i = 0; i < strlen(text); i++) {
        // Encrypt uppercase letters
        if (isupper(text[i])) {
            text[i] = cipher_alphabet[text[i] - 'A'];
        }
        // Encrypt lowercase letters
        else if (islower(text[i])) {
            text[i] = tolower(cipher_alphabet[text[i] - 'a']);
        }
        // Non-alphabet characters remain the same
    }
}

int main() {
    // Define the plaintext alphabet and a corresponding ciphertext alphabet
    char plaintext_alphabet[ALPHABET_SIZE + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char cipher_alphabet[ALPHABET_SIZE + 1] = "QWERTYUIOPASDFGHJKLZXCVBNM";  // Example substitution alphabet

    // Input plaintext from user
    char text[100];
    printf("Enter a message to encrypt: ");
    fgets(text, sizeof(text), stdin);

    // Perform encryption
    encrypt(text, cipher_alphabet);

    // Display the encrypted message
    printf("Encrypted message: %s\n", text);

    return 0;
}

