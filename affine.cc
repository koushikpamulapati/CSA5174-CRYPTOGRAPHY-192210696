#include <stdio.h>
#include <string.h>
#include <ctype.h>
// Function to find the greatest common divisor (gcd)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
// Function to encrypt the plaintext using the affine cipher
void affineEncrypt(char *plaintext, int a, int b, char *ciphertext) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        char p = plaintext[i];
        if (isalpha(p)) {
            if (isupper(p)) {
                ciphertext[i] = (a * (p - 'A') + b) % 26 + 'A';
            } else {
                ciphertext[i] = (a * (p - 'a') + b) % 26 + 'a';
            }
        } else {
            ciphertext[i] = p;  // Non-alphabet characters remain unchanged
        }
    }
    ciphertext[i] = '\0';  // Null-terminate the ciphertext
}
// Function to check if the key 'a' is valid (i.e., gcd(a, 26) == 1)
int isValidKeyA(int a) {
    return gcd(a, 26) == 1;
}
int main() {
    char plaintext[256], ciphertext[256];
    int a, b;
    // Input the keys 'a' and 'b'
    printf("Enter the value for 'a' (should be coprime with 26): ");
    scanf("%d", &a);
    // Check if 'a' is valid
    if (!isValidKeyA(a)) {
        printf("Error: 'a' must be coprime with 26. Try again.\n");
        return 1;
    }
    printf("Enter the value for 'b' (shift value, any integer between 0-25): ");
    scanf("%d", &b);
    // Input the plaintext
    printf("Enter the plaintext: ");
    getchar();  // Consume the newline character left by scanf
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  // Remove newline from input
    // Encrypt the plaintext using the affine cipher
    affineEncrypt(plaintext, a, b, ciphertext);
    // Display the resulting ciphertext
    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}
