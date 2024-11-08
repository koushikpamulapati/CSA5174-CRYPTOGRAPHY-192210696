#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MATRIX_SIZE 5
#define ALPHABET_SIZE 26
// Function to clean the plaintext (remove spaces, convert to uppercase, and handle 'I' and 'J' as the same)
void cleanText(char *text) {
    int j = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            // Handle 'I' and 'J' as the same letter
            if (toupper(text[i]) == 'J') {
                text[j++] = 'I';
            } else {
                text[j++] = toupper(text[i]);
            }
        }
    }
    text[j] = '\0';  // Null-terminate the cleaned text
}
// Function to create the Playfair matrix from the given matrix string
void createPlayfairMatrix(char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    char playfair[] = "MFHIJKUNOPQZVWXYELARGDSTBC"; // Provided matrix letters as a single string
    int k = 0;
    // Fill the matrix with the provided characters
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrix[i][j] = playfair[k++];
        }
    }
}
// Function to find the position of a letter in the Playfair matrix
void findPosition(char letter, char matrix[MATRIX_SIZE][MATRIX_SIZE], int *row, int *col) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (matrix[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
// Function to process the plaintext into digraphs (pairs of letters)
void createDigraphs(char *text, char digraphs[][2], int *numDigraphs) {
    int len = strlen(text);
    int j = 0;
    *numDigraphs = 0;
    for (int i = 0; i < len; i += 2) {
        if (i + 1 < len && text[i] != text[i + 1]) {
            // If both letters are different, create a digraph
            digraphs[j][0] = text[i];
            digraphs[j][1] = text[i + 1];
            j++;
        } else {
            // If both letters are the same, replace the second one with 'X'
            digraphs[j][0] = text[i];
            digraphs[j][1] = 'X';
            j++;
        }
    }
    *numDigraphs = j;  // Store the total number of digraphs
}
// Function to encrypt the digraphs using the Playfair cipher rules
void encryptDigraphs(char digraphs[][2], int numDigraphs, char matrix[MATRIX_SIZE][MATRIX_SIZE], char *ciphertext) {
    int row1, col1, row2, col2;
    int j = 0;
    for (int i = 0; i < numDigraphs; i++) {
        findPosition(digraphs[i][0], matrix, &row1, &col1);
        findPosition(digraphs[i][1], matrix, &row2, &col2);
        // Rule 1: If both letters are in the same row, take the letter to the immediate right
        if (row1 == row2) {
            ciphertext[j++] = matrix[row1][(col1 + 1) % MATRIX_SIZE];
            ciphertext[j++] = matrix[row2][(col2 + 1) % MATRIX_SIZE];
        }
        // Rule 2: If both letters are in the same column, take the letter immediately below
        else if (col1 == col2) {
            ciphertext[j++] = matrix[(row1 + 1) % MATRIX_SIZE][col1];
            ciphertext[j++] = matrix[(row2 + 1) % MATRIX_SIZE][col2];
        }
        // Rule 3: If the letters form a rectangle, swap the corners
        else {
            ciphertext[j++] = matrix[row1][col2];
            ciphertext[j++] = matrix[row2][col1];
        }
    }
    ciphertext[j] = '\0';  // Null-terminate the ciphertext
}
int main() {
    char matrix[MATRIX_SIZE][MATRIX_SIZE];
    char plaintext[] = "Must see you over Cadogan West. Coming at once.";
    char digraphs[100][2];  // Array to hold the digraphs
    char ciphertext[256];   // To store the encrypted message
    int numDigraphs;
    // Clean the plaintext
    cleanText(plaintext);
    // Create the Playfair matrix
    createPlayfairMatrix(matrix);
    // Process the plaintext into digraphs
    createDigraphs(plaintext, digraphs, &numDigraphs);
    // Encrypt the digraphs using the Playfair cipher
    encryptDigraphs(digraphs, numDigraphs, matrix, ciphertext);
    // Print the encrypted message
    printf("Encrypted Message: %s\n", ciphertext);
    return 0;
}

