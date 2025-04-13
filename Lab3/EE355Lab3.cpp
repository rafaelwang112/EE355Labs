#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;

// Find the next power of 2^n to pre-process the matrix 
int nextPowerOfTwo(int x) {
    if (x < 1) return 1;

    int power = 1;
    while (power < x) {
        power *= 2;
    }
    return power;
}

// create space for a new matrices
int** allocateMatrix(int n) {
    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n]();
    }
    return matrix;
}

// free space
void FreeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Addition of two matrices
void addMatrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Subtraction between two matrice
void subMatrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Q1
void DivideAndConquer(int** A, int** B, int** C, int n){
    //Base case: when the final matrix is 1 by 1 matrix
    if (n == 1){
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    
    int new_n = n/2;

    // Allocate the space for the A matrix 
    int** A11 = allocateMatrix(new_n);
    int** A12 = allocateMatrix(new_n);
    int** A21 = allocateMatrix(new_n);
    int** A22 = allocateMatrix(new_n);

    // Allocate the space for the B matrix
    int** B11 = allocateMatrix(new_n);
    int** B12 = allocateMatrix(new_n);
    int** B21 = allocateMatrix(new_n);
    int** B22 = allocateMatrix(new_n);

    // Allocate the space for the C matrix
    int** M1 = allocateMatrix(new_n);
    int** M2 = allocateMatrix(new_n);
    int** M3 = allocateMatrix(new_n);
    int** M4 = allocateMatrix(new_n);
    int** M5 = allocateMatrix(new_n);
    int** M6 = allocateMatrix(new_n);
    int** M7 = allocateMatrix(new_n);
    int** M8 = allocateMatrix(new_n);

    // Fill in the A and B matrix partition
    for (int i = 0; i < new_n; i++) {
        for (int j = 0; j < new_n; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + new_n];
            A21[i][j] = A[i + new_n][j];
            A22[i][j] = A[i + new_n][j + new_n];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + new_n];
            B21[i][j] = B[i + new_n][j];
            B22[i][j] = B[i + new_n][j + new_n];
        }
    }
    DivideAndConquer(A11, B11, M1, new_n);
    DivideAndConquer(A12, B21, M2, new_n);

    DivideAndConquer(A11, B12, M3, new_n);
    DivideAndConquer(A12, B22, M4, new_n);

    DivideAndConquer(A21, B11, M5, new_n);
    DivideAndConquer(A22, B21, M6, new_n);

    DivideAndConquer(A21, B12, M7, new_n);
    DivideAndConquer(A22, B22, M8, new_n);

    int** temp = allocateMatrix(new_n);
    
    // Calculate each C value
    addMatrix(M1, M2, temp, new_n);     //C11 
    for (int i = 0; i < new_n; i++)
        for (int j = 0; j < new_n; j++)
            C[i][j] = temp[i][j];

    addMatrix(M3, M4, temp, new_n);     //C12
    for (int i = 0; i < new_n; i++)
        for (int j = 0; j < new_n; j++)
            C[i][j+new_n] = temp[i][j];

    addMatrix(M5, M6, temp, new_n);     //C21
    for (int i = 0; i < new_n; i++)
        for (int j = 0; j < new_n; j++)
            C[i+new_n][j] = temp[i][j];

    addMatrix(M7, M8, temp, new_n);     //C22
    for (int i = 0; i < new_n; i++)
        for (int j = 0; j < new_n; j++)
            C[i+new_n][j+new_n] = temp[i][j];
    
    FreeMatrix(A11, new_n);
    FreeMatrix(A12, new_n);
    FreeMatrix(A21, new_n);
    FreeMatrix(A22, new_n);
    FreeMatrix(B11, new_n);
    FreeMatrix(B12, new_n);
    FreeMatrix(B21, new_n);
    FreeMatrix(B22, new_n);
    FreeMatrix(M1, new_n);
    FreeMatrix(M2, new_n);
    FreeMatrix(M3, new_n);
    FreeMatrix(M4, new_n);
    FreeMatrix(M5, new_n);
    FreeMatrix(M6, new_n);
    FreeMatrix(M7, new_n);
    FreeMatrix(M8, new_n);
    FreeMatrix(temp, new_n);
}

//Q2 
void strassen(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int new_n = n / 2;

    // Allocate submatrices
    int** A11 = allocateMatrix(new_n);
    int** A12 = allocateMatrix(new_n);
    int** A21 = allocateMatrix(new_n);
    int** A22 = allocateMatrix(new_n);

    int** B11 = allocateMatrix(new_n);
    int** B12 = allocateMatrix(new_n);
    int** B21 = allocateMatrix(new_n);
    int** B22 = allocateMatrix(new_n);

    int** C11 = allocateMatrix(new_n);
    int** C12 = allocateMatrix(new_n);
    int** C21 = allocateMatrix(new_n);
    int** C22 = allocateMatrix(new_n);

    int** M1 = allocateMatrix(new_n);
    int** M2 = allocateMatrix(new_n);
    int** M3 = allocateMatrix(new_n);
    int** M4 = allocateMatrix(new_n);
    int** M5 = allocateMatrix(new_n);
    int** M6 = allocateMatrix(new_n);
    int** M7 = allocateMatrix(new_n);

    int** temp1 = allocateMatrix(new_n);
    int** temp2 = allocateMatrix(new_n);

    // Divide matrices into submatrices
    for (int i = 0; i < new_n; i++) {
        for (int j = 0; j < new_n; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + new_n];
            A21[i][j] = A[i + new_n][j];
            A22[i][j] = A[i + new_n][j + new_n];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + new_n];
            B21[i][j] = B[i + new_n][j];
            B22[i][j] = B[i + new_n][j + new_n];
        }
    }

    // Compute M1 to M7 using recursion
    addMatrix(A11, A22, temp1, new_n);
    addMatrix(B11, B22, temp2, new_n);
    strassen(temp1, temp2, M1, new_n);

    addMatrix(A21, A22, temp1, new_n);
    strassen(temp1, B11, M2, new_n);

    subMatrix(B12, B22, temp2, new_n);
    strassen(A11, temp2, M3, new_n);

    subMatrix(B21, B11, temp2, new_n);
    strassen(A22, temp2, M4, new_n);

    addMatrix(A11, A12, temp1, new_n);
    strassen(temp1, B22, M5, new_n);

    subMatrix(A21, A11, temp1, new_n);
    addMatrix(B11, B12, temp2, new_n);
    strassen(temp1, temp2, M6, new_n);

    subMatrix(A12, A22, temp1, new_n);
    addMatrix(B21, B22, temp2, new_n);
    strassen(temp1, temp2, M7, new_n);

    // Compute submatrices of C
    addMatrix(M1, M4, temp1, new_n);
    subMatrix(temp1, M5, temp2, new_n);
    addMatrix(temp2, M7, C11, new_n);

    addMatrix(M3, M5, C12, new_n);
    addMatrix(M2, M4, C21, new_n);

    addMatrix(M1, M3, temp1, new_n);
    subMatrix(temp1, M2, temp2, new_n);
    addMatrix(temp2, M6, C22, new_n);

    // Combine results into C
    for (int i = 0; i < new_n; i++) {
        for (int j = 0; j < new_n; j++) {
            C[i][j] = C11[i][j];
            C[i][j + new_n] = C12[i][j];
            C[i + new_n][j] = C21[i][j];
            C[i + new_n][j + new_n] = C22[i][j];
        }
    }

    // Free allocated memory
    FreeMatrix(A11, new_n);
    FreeMatrix(A12, new_n);
    FreeMatrix(A21, new_n);
    FreeMatrix(A22, new_n);
    FreeMatrix(B11, new_n);
    FreeMatrix(B12, new_n);
    FreeMatrix(B21, new_n);
    FreeMatrix(B22, new_n);
    FreeMatrix(C11, new_n);
    FreeMatrix(C12, new_n);
    FreeMatrix(C21, new_n);
    FreeMatrix(C22, new_n);
    FreeMatrix(M1, new_n);
    FreeMatrix(M2, new_n);
    FreeMatrix(M3, new_n);
    FreeMatrix(M4, new_n);
    FreeMatrix(M5, new_n);
    FreeMatrix(M6, new_n);
    FreeMatrix(M7, new_n);
    FreeMatrix(temp1, new_n);
    FreeMatrix(temp2, new_n);
}

// Print the matrix 
void printMatrix(int** matrix, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}


int main() {
    ifstream inputFile("/Users/robert/C++/EE355Labs/Lab3/input.txt");
    if (!inputFile) {
        cout << "Error: Unable to open file" << endl;
        return 1;
    }

    int n;
    inputFile >> n;

    int N = nextPowerOfTwo(n);

    int** A = allocateMatrix(N);
    int** B = allocateMatrix(N);
    int** C = allocateMatrix(N);      // Divide-and-Conquer result
    int** C_str = allocateMatrix(N);  // Strassen result

    // Read matrix A and B
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            inputFile >> A[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            inputFile >> B[i][j];
    inputFile.close();

    time_t startDC = clock();      //start time 
    DivideAndConquer(A, B, C, N);
    time_t endDC = clock();        //stop time
    // Time in clock ticks
    time_t running_time_DC = endDC - startDC;

    // Write out C to output_m1.txt
    {
        ofstream outFile1("output_m1.txt");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                outFile1 << C[i][j] << (j + 1 < n ? " " : "");
            }
            outFile1 << "\n";
        }
    }

    time_t startStr = clock();
    strassen(A, B, C_str, N);
    time_t endStr = clock();

    time_t running_time_str = endStr - startStr;

    // Write out C_str to output_m2.txt
    {
        ofstream outFile2("output_m2.txt");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                outFile2 << C_str[i][j] << (j + 1 < n ? " " : "");
            }
            outFile2 << "\n";
        }
    }

    // Write out time to output.q3.txt
    {
        ofstream outFileQ3("output_q3.txt");
        outFileQ3 << running_time_DC << " ";   
        outFileQ3 << running_time_str << "\n"; 
    }

    FreeMatrix(A, N);
    FreeMatrix(B, N);
    FreeMatrix(C, N);
    FreeMatrix(C_str, N);

    return 0;
}
