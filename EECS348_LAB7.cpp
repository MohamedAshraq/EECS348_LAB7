#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Matrix {
private:
    vector<vector<int>> data;
    int size;

public:
    // Constructor to read matrix from file
    Matrix(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            file >> size;  // Read size
            data.resize(size, vector<int>(size));
            for (int i = 0; i < size; ++i)
                for (int j = 0; j < size; ++j)
                    file >> data[i][j];
            file.close();
        } else {
            cerr << "Error: Unable to open file\n";
        }
    }

    // Function to display the matrix
    void display() const {
        for (const auto& row : data) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
    }

    // Overload + operator for matrix addition
    Matrix operator+(const Matrix& other) const {
        Matrix result(*this);
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                result.data[i][j] += other.data[i][j];
        return result;
    }

    // Overload * operator for matrix multiplication
    Matrix operator*(const Matrix& other) const {
        Matrix result(*this);
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j) {
                result.data[i][j] = 0;
                for (int k = 0; k < size; ++k)
                    result.data[i][j] += data[i][k] * other.data[k][j];
            }
        return result;
    }

    // Function to calculate the sum of main and secondary diagonal elements
    void sumDiagonals() const {
        int mainDiagSum = 0, secDiagSum = 0;
        for (int i = 0; i < size; ++i) {
            mainDiagSum += data[i][i];
            secDiagSum += data[i][size - i - 1];
        }
        cout << "Main diagonal sum: " << mainDiagSum << endl;
        cout << "Secondary diagonal sum: " << secDiagSum << endl;
    }

    // Function to swap two rows
    void swapRows(int row1, int row2) {
        if (row1 >= 0 && row2 >= 0 && row1 < size && row2 < size) {
            swap(data[row1], data[row2]);
            cout << "Rows " << row1 << " and " << row2 << " swapped.\n";
        } else {
            cerr << "Invalid row indices.\n";
        }
        display();
    }
};

int main() {
    Matrix matrix1("matrix-data.txt");
    matrix1.display();
    cout << endl;

    // Example usage of operator overloading for addition
    Matrix matrix2("matrix-data.txt");
    Matrix sumMatrix = matrix1 + matrix2;
    cout << "Matrix after addition:\n";
    sumMatrix.display();
    cout << endl;

    // Example usage of operator overloading for multiplication
    Matrix productMatrix = matrix1 * matrix2;
    cout << "Matrix after multiplication:\n";
    productMatrix.display();
    cout << endl;

    // Display sum of diagonals
    matrix1.sumDiagonals();
    cout << endl;

    // Swap rows and display
    matrix1.swapRows(0, 2);

    return 0;
}
