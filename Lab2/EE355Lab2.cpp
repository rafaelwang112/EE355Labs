//EE355
//Xinsong Fan 
//7072371273

#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

class Matrix {
public:
    vector<vector<int> > value;
    static const int SIZE = 10;
    int target_row_idx;
    int maximum;
    int minimum;

    Matrix() {
    value.resize(SIZE, vector<int>(SIZE, 0));
}

    Matrix(const string& filename) {
        value.resize(SIZE, vector<int>(SIZE, 0));
        ifstream file(filename);
        if (!file) {
            cout << "Error opening file: " << filename << endl;
            exit(1);
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                file >> value[i][j];
            }
        }
        file.close();
    }

    int linear_search(int target) {
    maximum = value[0][0];
    minimum = value[0][0];
    int found_row = -1;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == 0 && j == 0){
                continue;
            }

            if (value[i][j] == target && found_row == -1) {
                found_row = i;  
            }

            if (value[i][j] > maximum) {
                maximum = value[i][j];
            }

            if (value[i][j] < minimum) {
                minimum = value[i][j];
            }
        }
    }
    return found_row; 
}

    Matrix mat_add(const Matrix& other_mat) {
        Matrix result(*this);
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                result.value[i][j] += other_mat.value[i][j];
            }
        }
        return result;
    }

    Matrix mat_mul(const Matrix& other_mat) {
        Matrix result;
        for (int i = 0; i < SIZE; i++) {    //iterate through rows 
            for (int j = 0; j < SIZE; j++) {    //iterate through cols
                result.value[i][j] = 0;
                for (int k = 0; k < SIZE; k++) {    //iterates all rows in that col
                    result.value[i][j] += value[i][k] * other_mat.value[k][j];
                }
            }
        }
        return result;
    }

    void save_to_file(const string& filename) {
        ofstream file(filename);
        if (!file) {
            cout << "Error opening output file: " << filename << endl;
            exit(1);
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                file << value[i][j] << " ";
            }
            file << endl;
        }
        file.close();
    }
};

int main() {
    Matrix matrix1("/Users/robert/Downloads/matrix_1.txt");
    Matrix matrix2("/Users/robert/Downloads/matrix_2.txt");
    
    int firstNum = matrix1.value[0][0];
    int row = matrix1.linear_search(firstNum);

    ofstream out1("output_Q1_1.txt");
    if (row == -1){
        out1 << "Target value in matrix is not shown." << endl;
    }
    else {
        out1 << "Target value in matrix is shown in: " << row << endl;
    }
    out1 << "Maximum value is: " << matrix1.maximum << ", Minimum value: " << matrix1.minimum << endl;
    out1.close();

    row = matrix2.linear_search(firstNum);
    ofstream out2("output_Q1_2.txt");
    if (row == -1){
        out2 << "Target value in matrix is not shown." << endl;
    }
    else {
        out2 << "Target value in matrix is shown in: " << row << endl;
    }
    out2 << "Maximum value is: " << matrix2.maximum << ", Minimum value: " << matrix2.minimum << endl;
    out2.close();

    Matrix sumMatrix = matrix1.mat_add(matrix2);
    sumMatrix.save_to_file("output_Q2.txt");

    Matrix productMatrix = matrix1.mat_mul(matrix2);
    productMatrix.save_to_file("output_Q3.txt");

    return 0;
}
