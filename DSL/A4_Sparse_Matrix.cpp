#include <iostream>
using namespace std;

#define MAX_TERMS 100

// Structure to store each non-zero element
class Element {
public:
    int row;
    int col;
    int value;
};

// Sparse Matrix Class
class SparseMatrix {
    Element elements[MAX_TERMS]; // Array to store non-zero elements
    int totalRows;
    int totalCols;
    int nonZeroCount;

public:
    SparseMatrix() {
        totalRows = totalCols = nonZeroCount = 0;
    }

    // 1. Read sparse matrix
    void readMatrix() {
        cout << "Enter number of rows, columns and non-zero elements: ";
        cin >> totalRows >> totalCols >> nonZeroCount;

        elements[0].row = totalRows;
        elements[0].col = totalCols;
        elements[0].value = nonZeroCount;

        cout << "Enter row, column, and value for each non-zero element:\n";
        for (int i = 1; i <= nonZeroCount; i++) {
            cout << "Element " << i << " (row col value): ";
            cin >> elements[i].row >> elements[i].col >> elements[i].value;
        }
    }

    // 2. Display sparse matrix
    void displayMatrix() {
        cout << "\nSparse Matrix (row col value):\n";
        for (int i = 0; i <= nonZeroCount; i++) {
            cout << elements[i].row << " " << elements[i].col << " " << elements[i].value << "\n";
        }
    }

    // 3. Add two sparse matrices
    void addMatrix(SparseMatrix otherMatrix, SparseMatrix &resultMatrix) {
        if (totalRows != otherMatrix.totalRows || totalCols != otherMatrix.totalCols) {
            cout << "Matrices cannot be added (different sizes).\n";
            return;
        }

        resultMatrix.totalRows = totalRows;
        resultMatrix.totalCols = totalCols;

        int index1 = 1, index2 = 1, resultIndex = 1;

        while (index1 <= nonZeroCount && index2 <= otherMatrix.nonZeroCount) {
            if (elements[index1].row == otherMatrix.elements[index2].row &&
                elements[index1].col == otherMatrix.elements[index2].col) {
                resultMatrix.elements[resultIndex] = elements[index1];
                resultMatrix.elements[resultIndex].value += otherMatrix.elements[index2].value;
                index1++;
                index2++;
            }
            else if ((elements[index1].row < otherMatrix.elements[index2].row) ||
                     (elements[index1].row == otherMatrix.elements[index2].row &&
                      elements[index1].col < otherMatrix.elements[index2].col)) {
                resultMatrix.elements[resultIndex] = elements[index1];
                index1++;
            }
            else {
                resultMatrix.elements[resultIndex] = otherMatrix.elements[index2];
                index2++;
            }
            resultIndex++;
        }

        // Copy remaining elements
        while (index1 <= nonZeroCount) {
            resultMatrix.elements[resultIndex++] = elements[index1++];
        }
        while (index2 <= otherMatrix.nonZeroCount) {
            resultMatrix.elements[resultIndex++] = otherMatrix.elements[index2++];
        }

        resultMatrix.nonZeroCount = resultIndex - 1;
        resultMatrix.elements[0].row = totalRows;
        resultMatrix.elements[0].col = totalCols;
        resultMatrix.elements[0].value = resultMatrix.nonZeroCount;
    }

    // 4. Simple Transpose
    void simpleTranspose(SparseMatrix &transposedMatrix, int &stepCounter) {
        transposedMatrix.totalRows = totalCols;
        transposedMatrix.totalCols = totalRows;
        transposedMatrix.nonZeroCount = nonZeroCount;
        transposedMatrix.elements[0] = {totalCols, totalRows, nonZeroCount};

        int newIndex = 1;
        for (int currentCol = 0; currentCol < totalCols; currentCol++) {
            for (int i = 1; i <= nonZeroCount; i++) {
                stepCounter++;
                if (elements[i].col == currentCol) {
                    transposedMatrix.elements[newIndex].row = elements[i].col;
                    transposedMatrix.elements[newIndex].col = elements[i].row;
                    transposedMatrix.elements[newIndex].value = elements[i].value;
                    newIndex++;
                }
            }
        }
    }

    // 5. Fast Transpose
    void fastTranspose(SparseMatrix &transposedMatrix, int &stepCounter) {
        int countPerColumn[totalCols] = {0};
        int startingPosition[totalCols] = {0};

        transposedMatrix.totalRows = totalCols;
        transposedMatrix.totalCols = totalRows;
        transposedMatrix.nonZeroCount = nonZeroCount;
        transposedMatrix.elements[0] = {totalCols, totalRows, nonZeroCount};

        // Step 1: Count how many elements in each column
        for (int i = 1; i <= nonZeroCount; i++) {
            countPerColumn[elements[i].col]++;
            stepCounter++;
        }

        // Step 2: Find starting position for each column
        startingPosition[0] = 1;
        for (int i = 1; i < totalCols; i++) {
            startingPosition[i] = startingPosition[i - 1] + countPerColumn[i - 1];
            stepCounter++;
        }

        // Step 3: Place elements at correct position in transposed matrix
        for (int i = 1; i <= nonZeroCount; i++) {
            int pos = startingPosition[elements[i].col]++;
            transposedMatrix.elements[pos].row = elements[i].col;
            transposedMatrix.elements[pos].col = elements[i].row;
            transposedMatrix.elements[pos].value = elements[i].value;
            stepCounter++;
        }
    }
};

// Main menu
int main() {
    SparseMatrix matrix1, matrix2, resultMatrix;
    int choice;
    int simpleSteps = 0, fastSteps = 0;

    do {
        cout << "\n====== Sparse Matrix Menu ======\n";
        cout << "1. Read Sparse Matrix\n";
        cout << "2. Display Sparse Matrix\n";
        cout << "3. Add Two Sparse Matrices\n";
        cout << "4. Transpose (Simple Method)\n";
        cout << "5. Transpose (Fast Method)\n";
        cout << "6. Compare Transpose Steps\n";
        cout << "0. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nEnter Matrix Data:\n";
                matrix1.readMatrix();
                break;

            case 2:
                matrix1.displayMatrix();
                break;

            case 3:
                cout << "\nEnter Second Matrix to Add:\n";
                matrix2.readMatrix();
                matrix1.addMatrix(matrix2, resultMatrix);
                cout << "\nResult of Addition:\n";
                resultMatrix.displayMatrix();
                break;

            case 4:
                matrix1.simpleTranspose(resultMatrix, simpleSteps);
                cout << "\nSimple Transpose:\n";
                resultMatrix.displayMatrix();
                break;

            case 5:
                matrix1.fastTranspose(resultMatrix, fastSteps);
                cout << "\nFast Transpose:\n";
                resultMatrix.displayMatrix();
                break;

            case 6:
                cout << "\nSimple Transpose Steps: " << simpleSteps;
                cout << "\nFast Transpose Steps: " << fastSteps << "\n";
                break;

            case 0:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid option. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
