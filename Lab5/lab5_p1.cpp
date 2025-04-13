#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // for atoi
using namespace std;

// Code for part 1
class Part1 {
    public: 
        int n;
        int max;
        int min;
        string in;
        int *arr;
    public:
        Part1 (string input_file) : in(input_file) {};

        // Create an array from the file
        void createArray() {
            ifstream file(in);
            if (!file.is_open()) {
                cout << "Error opening file: " << endl;
                return;
            }
            file >> n;
            arr = new int[n]; 
            int* ptr = arr; 
            for (int i = 0; i < n; i++) {
                file >> *ptr;
                ptr++;
            }
            file.close();
        }
        // Print out the array with pointer 
        void displayArray(ofstream& output_file) {
            int* ptr = arr;
            for (int i = 0; i < n; i++) {
                output_file << *ptr << " ";
                ptr++;
            }
            cout << endl;
        }
        // Double the even and Square the odd
        void transformation(){
            int *ptr = arr;
            for (int i = 0; i < n; i++) {
                if (*ptr % 2 == 0) {
                    *ptr = *ptr * 2;
                } else {
                    *ptr = *ptr * *ptr;
                }
                ptr++;
            }
        }
        // Max and Min
        void searchMaxMin(){
            int *ptr = arr;
            max = *ptr;
            min = *ptr;
            for (int i = 0; i < n; i++) {
                if (*ptr > max) {
                    max = *ptr;
                }
                if (*ptr < min) {
                    min = *ptr;
                }
                ptr++;
            }
        }
        // Prefix sum
        void prefixSum(){
            int *ptr = arr;
            for (int i = 1; i < n; i++) {
                *(ptr + i) = *(ptr + i) + *(ptr + i - 1);
            }
        }
    };

int main() {
    // Code for part1: 
    ofstream out1("output_q1.txt");
    Part1 part1("input.txt");
    part1.createArray();
    out1 << "Orignial Array: " << " ";
    part1.displayArray(out1);
    out1 << endl << endl;
    out1 << "Modified arrays:" << endl;
    part1.transformation();
    out1 << "  - Doubled even numbers & Squared odd numbers:" << " ";
    part1.displayArray(out1);
    out1 << endl << endl;
    part1.searchMaxMin();
    out1 << "Max Value: "  << part1.max << endl;
    out1 << "Min Value: " << part1.min << endl << endl;
    part1.prefixSum();
    part1.displayArray(out1);
    out1.close();

    return 0; 
}