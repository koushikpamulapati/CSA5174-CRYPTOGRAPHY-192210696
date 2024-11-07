#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100

// Function to encrypt the plaintext using the key
void encrypt(char *plaintext, char *key, char *ciphertext) {
    int pt_len = strlen(plaintext);
    int key_len = strlen(key);
    int i, j = 0;

    for (i = 0; i < pt_len; i++) {
        // If plaintext character is alphabetic, encrypt it
        if (isalpha(plaintext[i])) {
            char shift = toupper(key[j % key_len]) - 'A';
            // If the character is uppercase
            if (isupper(plaintext[i])) {
                ciphertext[i] = ((plaintext[i] - 'A' + shift) % 26) + 'A';
            }
            // If the character is lowercase
            else if (islower(plaintext[i])) {
                ciphertext[i] = ((plaintext[i] - 'a' + shift) % 26) + 'a';
            }
            j++;  // Move to next character in the key
        }
        // If the character is not alphabetic, leave it unchanged
        else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';  // Null-terminate the ciphertext
}

// Main function
int main() {
    char plaintext[MAX_LENGTH], key[MAX_LENGTH], ciphertext[MAX_LENGTH];

    // Input plaintext and key
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  // Remove newline character if present

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';  // Remove newline character if present

    // Encrypt the plaintext
    encrypt(plaintext, key, ciphertext);

    // Output the encrypted message
    printf("Encrypted message: %s\n", ciphertext);

    return 0;
}

