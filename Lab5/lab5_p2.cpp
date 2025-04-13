#include <iostream>
#include <fstream>
#include <cstdlib> // for atoi
using namespace std;

// Function to extract and display command-line arguments using pointer-to-pointer
void extractCommandLineArgs(int argc, char** argv, ofstream &outputFile) {
    outputFile << "Original Numbers: ";
    char** argPtr = argv + 1; 
    while(argPtr < argv + argc) {
        outputFile << *argPtr << " ";
        argPtr++;
    }
    outputFile << endl << endl;

    outputFile << "Extracted Command-Line Arguments:" << endl;
    char** current = argv;
    for(int i = 0; i < argc; i++){
        outputFile << "  - argv[" << i << "] = " << *(current+i) << endl;
    }
    outputFile << endl;
}

// Function to swap two integers using pass-by-value (no effect)
void swapByValue(int a, int b) {
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

// Function to swap two integers using pass-by-reference (modifies values)
void swapByReference(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Function to modify array: Double each value (using pass-by-pointer)
void doubleValues(int* arr, int size) {
    for(int i = 0; i < size; i++){
        *(arr+i) *= 2;
    }
}

// Function to compute sum and product using pass-by-reference
void computeSumAndProduct(int* arr, int size, int &sum, int &product) {
    for(int i = 0; i < size; i++){
        sum += *(arr+i);
        product *= *(arr+i);
        cout << product << endl;
    }
}

// Function to reverse an array using pointers (without array indexing)
void reverseArray(int* arr, int size) {
    int* left = arr;
    int* right = arr + size - 1;

    while (left < right){
        swapByReference(*left, *right);
        left++;
        right--;
    }
}

// Main function
int main(int argc, char* argv[]) {
    
    // Convert command-line arguments to integers
    int size = argc - 1;
    int* arr = new int[size];       // the array that has numeric values of the command line 
    int* arrPtr = arr;              // the pointer that tracks the element of the array
    char** argPtr = argv + 1;
    for(int i = 0; i < size; i++){
        *(arrPtr+i) = atoi(*(argPtr+i));
    }

    // Open output file
    ofstream out("output_q2.txt");
    if(!out.is_open()){
        cerr << "Error opening output file!" << endl;
        return 1;
    }

    // Extract command-line arguments using pointer-to-pointer
    // extractCommandLineArgs(); // Fill in the arguments
    extractCommandLineArgs(argc, argv, out);

    // Demonstrate pass-by-value (no effect)
    out << "Pass-by-Value Swap (No Effect):" << endl;
    // swapByValue(); // Fill in the arguments
    out << "  - Swap(" << *(arr) << ", " << *(arr + 1) << ") → ";
    swapByValue(*(arr), *(arr + 1));
    out << "a = " << *(arr) << ", b = " << *(arr + 1) << " (Unchanged)" << endl << endl;

    // Demonstrate pass-by-reference (modifies values)
    // swapByReference(); // Fill in the arguments
    out << "Pass-by-Reference Swap (Successful):" << endl;
    // swapByValue(); // Fill in the arguments
    out << "  - Swap(" << *(arr) << ", " << *(arr + 1) << ") → ";
    swapByReference(*(arr), *(arr + 1));
    out << "a = " << *(arr) << ", b = " << *(arr + 1) << endl << endl;
    // Modify array (double values using pointer)
    // doubleValues(); // Fill in the arguments
    doubleValues(arr, size);
    out << "Pass-by-Pointer Modification:" << endl;
    out << "  - Doubled Values: ";
    int *p = arr;
    for (int i = 0; i < size; i++){
        out << *(p+i) << " ";
    }
    out << endl << endl;

    // Compute sum and product
    // computeSumAndProduct(); // Fill in the arguments
    int sum, product = 1;
    computeSumAndProduct(arr, size, sum, product);
    out << "Sum of Numbers: " << sum << endl;
    out << "Product of Numbers: " << product << endl << endl;
    // Reverse array
    // reverseArray(); // Fill in the arguments
    reverseArray(arr, size);
    out << "Reversed Order: ";
    int* revPtr = arr;
    for (int i = 0; i < size; i++){
        out << *(revPtr+i) << " ";
    }
    out << endl << endl;

    return 0;
}