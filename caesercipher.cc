#include <stdio.h>
#include <string.h>
#include <ctype.h>

void caesarCipher(char *text, int key) {
    for (int i = 0; i < strlen(text); i++) {
        // Check if character is an uppercase letter
        if (isupper(text[i])) {
            text[i] = ((text[i] - 'A' + key) % 26) + 'A';
        }
        // Check if character is a lowercase letter
        else if (islower(text[i])) {
            text[i] = ((text[i] - 'a' + key) % 26) + 'a';
        }
        // Non-alphabetical characters remain the same
    }
}

int main() {
    char text[100];
    int key;

    // Input the plaintext and shift key
    printf("Enter a message to encrypt: ");
    fgets(text, sizeof(text), stdin);  // Get input including spaces

    printf("Enter shift key (1-25): ");
    scanf("%d", &key);

    // Ensure key is in the valid range
    if (key < 1 || key > 25) {
        printf("Invalid key! Please enter a number between 1 and 25.\n");
        return 1;
    }

    // Perform Caesar Cipher encryption
    caesarCipher(text, key);

    printf("Encrypted message: %s\n", text);

    return 0;
}

