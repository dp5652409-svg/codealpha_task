#include <stdio.h>
#include <stdlib.h>

#define MAX 10

// Function prototypes
void readMatrix(int matrix[MAX][MAX], int rows, int cols);
void displayMatrix(int matrix[MAX][MAX], int rows, int cols);
void matrixAddition(int A[MAX][MAX], int B[MAX][MAX], int result[MAX][MAX], int rows, int cols);
void matrixMultiplication(int A[MAX][MAX], int B[MAX][MAX], int result[MAX][MAX], int rows1, int cols1, int rows2, int cols2);
void matrixTranspose(int matrix[MAX][MAX], int transposed[MAX][MAX], int rows, int cols);
void menu();

int main() {
    int choice;
    int rows1, cols1, rows2, cols2;
    int A[MAX][MAX], B[MAX][MAX], result[MAX][MAX];
    
    do {
        menu();
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: // Matrix Addition
                printf("\n=== MATRIX ADDITION ===\n");
                printf("Enter rows and columns for matrices: ");
                scanf("%d %d", &rows1, &cols1);
                
                printf("\nEnter elements for Matrix A:\n");
                readMatrix(A, rows1, cols1);
                printf("\nEnter elements for Matrix B:\n");
                readMatrix(B, rows1, cols1);
                
                if(rows1 == cols1) {
                    matrixAddition(A, B, result, rows1, cols1);
                    printf("\nMatrix A:\n");
                    displayMatrix(A, rows1, cols1);
                    printf("\nMatrix B:\n");
                    displayMatrix(B, rows1, cols1);
                    printf("\nSum (A + B):\n");
                    displayMatrix(result, rows1, cols1);
                } else {
                    printf("Error: Matrices must have the same dimensions for addition!\n");
                }
                break;
                
            case 2: // Matrix Multiplication
                printf("\n=== MATRIX MULTIPLICATION ===\n");
                printf("Enter rows and columns for Matrix A: ");
                scanf("%d %d", &rows1, &cols1);
                printf("Enter rows and columns for Matrix B: ");
                scanf("%d %d", &rows2, &cols2);
                
                if(cols1 == rows2) {
                    printf("\nEnter elements for Matrix A:\n");
                    readMatrix(A, rows1, cols1);
                    printf("\nEnter elements for Matrix B:\n");
                    readMatrix(B, rows2, cols2);
                    
                    matrixMultiplication(A, B, result, rows1, cols1, rows2, cols2);
                    printf("\nMatrix A:\n");
                    displayMatrix(A, rows1, cols1);
                    printf("\nMatrix B:\n");
                    displayMatrix(B, rows2, cols2);
                    printf("\nProduct (A x B):\n");
                    displayMatrix(result, rows1, cols2);
                } else {
                    printf("Error: Number of columns in A must equal number of rows in B!\n");
                }
                break;
                
            case 3: // Matrix Transpose
                printf("\n=== MATRIX TRANSPOSE ===\n");
                printf("Enter rows and columns for matrix: ");
                scanf("%d %d", &rows1, &cols1);
                
                printf("\nEnter elements for Matrix:\n");
                readMatrix(A, rows1, cols1);
                
                matrixTranspose(A, result, rows1, cols1);
                printf("\nOriginal Matrix:\n");
                displayMatrix(A, rows1, cols1);
                printf("\nTransposed Matrix:\n");
                displayMatrix(result, cols1, rows1);
                break;
                
            case 4: // Display All Operations
                printf("\n=== ALL MATRIX OPERATIONS ===\n");
                
                // Example matrices
                rows1 = cols1 = 3;
                rows2 = 3; cols2 = 2;
                
                // Initialize sample matrices
                int sampleA[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
                int sampleB[3][3] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
                int sampleC[3][2] = {{1, 2}, {3, 4}, {5, 6}};
                
                // Copy to our matrices
                for(int i = 0; i < 3; i++) {
                    for(int j = 0; j < 3; j++) {
                        A[i][j] = sampleA[i][j];
                        B[i][j] = sampleB[i][j];
                    }
                }
                
                for(int i = 0; i < 3; i++) {
                    for(int j = 0; j < 2; j++) {
                        result[i][j] = sampleC[i][j];
                    }
                }
                
                printf("Sample Matrix A (3x3):\n");
                displayMatrix(A, 3, 3);
                
                printf("\nSample Matrix B (3x3):\n");
                displayMatrix(B, 3, 3);
                
                printf("\nSample Matrix C (3x2):\n");
                displayMatrix(result, 3, 2);
                
                // Addition
                printf("\n1. Addition (A + B):\n");
                matrixAddition(A, B, result, 3, 3);
                displayMatrix(result, 3, 3);
                
                // Multiplication
                printf("\n2. Multiplication (A x C):\n");
                matrixMultiplication(A, result, B, 3, 3, 3, 2);
                displayMatrix(B, 3, 2);
                
                // Transpose
                printf("\n3. Transpose of A:\n");
                matrixTranspose(A, result, 3, 3);
                displayMatrix(result, 3, 3);
                break;
                
            case 5:
                printf("Exiting program. Goodbye!\n");
                break;
                
            default:
                printf("Invalid choice! Please enter a number between 1 and 5.\n");
        }
        
        if(choice != 5) {
            printf("\nPress Enter to continue...");
            getchar(); // Clear newline
            getchar(); // Wait for Enter
        }
        
    } while(choice != 5);
    
    return 0;
}

// Function to read matrix elements
void readMatrix(int matrix[MAX][MAX], int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        printf("Enter %d elements for row %d: ", cols, i+1);
        for(int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

// Function to display matrix
void displayMatrix(int matrix[MAX][MAX], int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        printf("| ");
        for(int j = 0; j < cols; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("|\n");
    }
}

// Function to add two matrices
void matrixAddition(int A[MAX][MAX], int B[MAX][MAX], int result[MAX][MAX], int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Function to multiply two matrices
void matrixMultiplication(int A[MAX][MAX], int B[MAX][MAX], int result[MAX][MAX], int rows1, int cols1, int rows2, int cols2) {
    // Initialize result matrix to 0
    for(int i = 0; i < rows1; i++) {
        for(int j = 0; j < cols2; j++) {
            result[i][j] = 0;
        }
    }
    
    // Perform matrix multiplication
    for(int i = 0; i < rows1; i++) {
        for(int j = 0; j < cols2; j++) {
            for(int k = 0; k < cols1; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Function to find transpose of a matrix
void matrixTranspose(int matrix[MAX][MAX], int transposed[MAX][MAX], int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }
}

// Function to display menu
void menu() {
    system("clear || cls"); // Clear screen (works on both Linux and Windows)
    printf("========================================\n");
    printf("           MATRIX OPERATIONS\n");
    printf("========================================\n");
    printf("1. Matrix Addition\n");
    printf("2. Matrix Multiplication\n");
    printf("3. Matrix Transpose\n");
    printf("4. Display All Operations (Sample)\n");
    printf("5. Exit\n");
    printf("========================================\n");
}