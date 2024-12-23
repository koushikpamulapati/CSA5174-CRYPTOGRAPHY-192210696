#include <stdio.h>
#include <string.h>
#include <ctype.h>
// Function to encrypt the plaintext using the Vigen�re cipher
void encrypt(char *plaintext, char *key, char *ciphertext) {
    int i, j = 0;
    int keyLength = strlen(key);
    int textLength = strlen(plaintext);
    for (i = 0; i < textLength; i++) {
        char p = plaintext[i];
        if (isalpha(p)) { // Encrypt only alphabetic characters
            char k = toupper(key[j % keyLength]); // Repeat the key if it's shorter than the plaintext
            int shift = k - 'A'; // Shift amount is based on the key letter
            
            if (isupper(p)) {
                ciphertext[i] = (p - 'A' + shift) % 26 + 'A'; // Encrypt uppercase letter
            } else {
                ciphertext[i] = (p - 'a' + shift) % 26 + 'a'; // Encrypt lowercase letter
            }
            j++; // Move to the next character in the key
        } else {
            ciphertext[i] = p; // Non-alphabet characters remain unchanged
        }
    }
    ciphertext[i] = '\0'; // Null-terminate the ciphertext
}
int main() {
    char plaintext[256], key[256], ciphertext[256];
    // Input the key and plaintext
    printf("Enter the key (letters only): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline character if any
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character if any
    // Ensure the key is only alphabetic
    for (int i = 0; key[i] != '\0'; i++) {
        if (!isalpha(key[i])) {
            printf("Error: The key must contain only alphabetic characters.\n");
            return 1;
        }
    }
    // Encrypt the plaintext using the key
    encrypt(plaintext, key, ciphertext);
    // Display the resulting ciphertext
    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}

