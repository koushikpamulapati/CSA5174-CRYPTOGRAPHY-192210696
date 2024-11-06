#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char matrix[SIZE][SIZE];

// Function to check if a character is already in the matrix
int contains(char c, char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == c) return 1;
    }
    return 0;
}

// Function to create the 5x5 matrix based on a keyword
void createMatrix(char *key) {
    char used[26] = "";  // Keep track of added characters
    int row = 0, col = 0;

    // Add each character of the keyword to the matrix
    for (int i = 0; i < strlen(key); i++) {
        char c = toupper(key[i]);
        if (c == 'J') c = 'I';  // Treat J as I
        if (!contains(c, used) && isalpha(c)) {
            matrix[row][col++] = c;
            strncat(used, &c, 1);
            if (col == SIZE) { col = 0; row++; }
        }
    }

    // Add the remaining letters of the alphabet
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue;  // Skip 'J'
        if (!contains(c, used)) {
            matrix[row][col++] = c;
            strncat(used, &c, 1);
            if (col == SIZE) { col = 0; row++; }
        }
    }
}

// Function to find the row and column of a character in the matrix
void findPosition(char c, int *row, int *col) {
    if (c == 'J') c = 'I';
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to process plaintext into pairs and add filler if needed
void preprocessText(char *text) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == 'J') text[i] = 'I';  // Replace J with I
    }

    // Insert filler 'X' for repeated letters in pairs
    for (int i = 0; i < strlen(text); i += 2) {
        if (text[i] == text[i + 1]) {
            memmove(text + i + 1, text + i, strlen(text) - i + 1);
            text[i + 1] = 'X';
        }
    }

    // Add 'X' if the length is odd
    if (strlen(text) % 2 != 0) {
        strncat(text, "X", 1);
    }
}

// Function to encrypt text using the Playfair cipher
void encrypt(char *text) {
    int row1, col1, row2, col2;

    for (int i = 0; i < strlen(text); i += 2) {
        findPosition(toupper(text[i]), &row1, &col1);
        findPosition(toupper(text[i + 1]), &row2, &col2);

        // Apply Playfair cipher rules
        if (row1 == row2) {  // Same row
            text[i] = matrix[row1][(col1 + 1) % SIZE];
            text[i + 1] = matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {  // Same column
            text[i] = matrix[(row1 + 1) % SIZE][col1];
            text[i + 1] = matrix[(row2 + 1) % SIZE][col2];
        } else {  // Rectangle swap
            text[i] = matrix[row1][col2];
            text[i + 1] = matrix[row2][col1];
        }
    }
}

// Main function
int main() {
    char key[30];
    char text[100];

    // Input keyword and plaintext
    printf("Enter the keyword: ");
    scanf("%s", key);
    printf("Enter the plaintext: ");
    scanf("%s", text);

    // Create the 5x5 matrix and preprocess text
    createMatrix(key);
    preprocessText(text);

    // Encrypt the text
    encrypt(text);

    // Print the encrypted message
    printf("Encrypted message: %s\n", text);

    return 0;
}

