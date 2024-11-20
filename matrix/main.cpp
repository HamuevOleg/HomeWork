#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
using namespace std;

double** matrixCreation(int& rows, int& cols) {
    cout << "Please write number of equations (rows): ";
    cin >> rows;
    cout << "Please write number of variables (columns): ";
    cin >> cols;

    auto** matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[cols + 1];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols + 1; j++) {
            if (j < cols) {
                cout << "Please write x" << j + 1 << " in eq " << i + 1 << ": ";
            } else {
                cout << "Please write res for eq " << i + 1 << ": ";
            }
            cin >> matrix[i][j];
        }
    }

    cout << "\nInitial Matrix:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols + 1; j++) {
            cout << setw(10) << matrix[i][j] << " ";
        }
        cout << endl;
    }
    return matrix;
}

double** copyMatrix(double** originalMatrix, int rows, int cols) {
    double** newMatrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        newMatrix[i] = new double[cols + 1];
        for (int j = 0; j <= cols; j++) {
            newMatrix[i][j] = originalMatrix[i][j];
        }
    }
    return newMatrix;
}

int calculateRank(double** matrix, int rows, int cols) {
    vector<bool> rowUsed(rows, false);
    int rank = 0;

    for (int col = 0; col < cols; ++col) {
        int pivotRow = -1;
        for (int row = 0; row < rows; ++row) {
            if (!rowUsed[row] && matrix[row][col] != 0) {
                pivotRow = row;
                break;
            }
        }

        if (pivotRow == -1) continue;

        rowUsed[pivotRow] = true;
        ++rank;

        for (int row = 0; row < rows; ++row) {
            if (row != pivotRow && matrix[row][col] != 0) {
                double factor = matrix[row][col] / matrix[pivotRow][col];
                for (int c = 0; c <= cols; ++c) {
                    matrix[row][c] -= factor * matrix[pivotRow][c];
                }
            }
        }
    }

    return rank;
}

void analyzeSolution(double** matrix, int rows, int cols) {
    double** extendedMatrix = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        extendedMatrix[i] = new double[cols + 1];
        for (int j = 0; j <= cols; ++j) {
            extendedMatrix[i][j] = matrix[i][j];
        }
    }

    int rankMain = calculateRank(matrix, rows, cols);
    int rankAugmented = calculateRank(extendedMatrix, rows, cols + 1);

    for (int i = 0; i < rows; ++i) {
        delete[] extendedMatrix[i];
    }
    delete[] extendedMatrix;

    if (rankMain < rankAugmented) {
        cout << "No solutions exist (inconsistent system)." << endl;
    } else if (rankMain == cols) {
        cout << "Unique solution exists." << endl;
    } else {
        cout << "Infinite solutions exist." << endl;
        cout << "The basis of solutions is:" << endl;

        for (int i = 0; i < rows; ++i) {
            if (i >= rankMain) {
                cout << "Free variable x" << i + 1 << endl;
            }
        }
    }
}

void GaussJordanElimination(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        if (matrix[i][i] == 0) {
            for (int k = i + 1; k < rows; k++) {
                if (matrix[k][i] != 0) {
                    swap(matrix[i], matrix[k]);
                    break;
                }
            }
        }

        double lead = matrix[i][i];
        if (lead == 0) continue;

        for (int j = 0; j < cols + 1; j++) {
            matrix[i][j] /= lead;
        }

        for (int k = 0; k < rows; k++) {
            if (k != i) {
                double factor = matrix[k][i];
                for (int j = 0; j < cols + 1; j++) {
                    matrix[k][j] -= factor * matrix[i][j];
                }
            }
        }
    }

    cout << "\nMatrix after Gauss-Jordan Elimination:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols + 1; j++) {
            cout << setw(10) << matrix[i][j] << " ";
        }
        cout << endl;
    }

    analyzeSolution(matrix, rows, cols);
}

//(0,0) (0,1) (0,2) (0,3) (0,4) (0,5) (0,6) (0,7) (0,8)
//(1,0) (1,1) (1,2) (1,3) (1,4) (1,5) (1,6) (1,7) (1,8)
//(2,0) (2,1) (2,2) (2,3) (2,4) (2,5) (2,6) (2,7) (2,8)
//(3,0) (3,1) (3,2) (3,3) (3,4) (3,5) (3,6) (3,7) (3,8)
//(4,0) (4,1) (4,2) (4,3) (4,4) (4,5) (4,6) (4,7) (4,8)
//(5,0) (5,1) (5,2) (5,3) (5,4) (5,5) (5,6) (5,7) (5,8)
//(6,0) (6,1) (6,2) (6,3) (6,4) (6,5) (6,6) (6,7) (6,8)
//(7,0) (7,1) (7,2) (7,3) (7,4) (7,5) (7,6) (7,7) (7,8)
//(8,0) (8,1) (8,2) (8,3) (8,4) (8,5) (8,6) (8,7) (8,8)

void checkAndSwap(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        int maxRow = i;
        double rowSum = 0;

        for (int j = 0; j < cols; j++) {
            if (j != i) {
                rowSum += abs(matrix[i][j]);
            }
        }

        if (abs(matrix[i][i]) <= rowSum) {
            bool found = false;

            for (int k = i + 1; k < rows; k++) {
                double potentialMaxValue = abs(matrix[k][i]);
                double potentialRowSum = 0;

                for (int j = 0; j < cols; j++) {
                    if (j != i) {
                        potentialRowSum += abs(matrix[k][j]);
                    }
                }

                if (potentialMaxValue > potentialRowSum) {
                    maxRow = k;
                    found = true;
                    break;
                }
            }

            if (found) {
                swap(matrix[i], matrix[maxRow]);
            } else {
                cout << "Failed to ensure diagonal dominance for row " << i + 1 << endl;
            }
        }
    }
}

void SeidelMethod(double** matrix, int rows, int cols) {
    double epsilon;
    cout << "Enter the precision value (epsilon): ";
    cin >> epsilon;
    checkAndSwap(matrix,rows, cols);

    cout << "\nMatrix after checkAndSwap (for Seidel Method):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols + 1; j++) {
            cout << setw(10) << matrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nEquations ready for use with Seidel's method\n";
    for (int i = 0; i < rows; i++) {
        double diagElement = matrix[i][i];
        cout << "x" << i + 1 << " = ";

        for (int j = 0; j < cols; j++) {
            if (j != i) {
                double coefficient = -matrix[i][j] / diagElement;
                cout << (coefficient >= 0 ? " + " : " - ") << abs(coefficient) << "*x" << j + 1;
            }
        }

        double freeTerm = matrix[i][cols] / diagElement;
        cout << " + " << freeTerm << endl;
    }
    //Method Realisation

    double* x = new double[rows];
    for (int i = 0; i < rows; i++) {
        x[i] = 0;
    }

    cout << "\nStart of iterations of Seidel's method:\n";
    bool continueIteration;
    int iterationCount = 0;

    do {
        continueIteration = false;
        iterationCount++;

        for (int i = 0; i < rows; i++) {
            double old_xi = x[i];
            double sum = matrix[i][cols];

            for (int j = 0; j < cols; j++) {
                if (j != i) {
                    sum -= matrix[i][j] * x[j];
                }
            }

            x[i] = sum / matrix[i][i];

            if (abs(x[i] - old_xi) > epsilon) {
                continueIteration = true;
            }
        }

        cout << "Iteration " << iterationCount << ": ";
        for (int i = 0; i < rows; i++) {
            cout << "x" << i + 1 << " = " << x[i] << " ";
        }
        cout << endl;

    } while (continueIteration);

    cout << "\nSolution\n";
    for (int i = 0; i < rows; i++) {
        cout << "x" << i + 1 << " = " << x[i] << endl;
    }

    delete[] x;
}

int main() {
    int rows, cols;
    double **matrix = matrixCreation(rows, cols);

    int method = 0;
    while (true) {
        cout << "\nChoose method:\n 1. Gauss-Jordan Elimination\n 2. Seidel method\n 3. Leave Program" << endl;
        cout << "Write please:";
        cin >> method;

        if (method == 1) {
            double** matrixCopy = copyMatrix(matrix, rows, cols);
            GaussJordanElimination(matrixCopy, rows, cols);
            for (int i = 0; i < rows; i++) {
                delete[] matrixCopy[i];
            }
            delete[] matrixCopy;
        } else if (method == 2) {
            double** matrixCopy = copyMatrix(matrix, rows, cols);
            SeidelMethod(matrixCopy, rows, cols);
            for (int i = 0; i < rows; i++) {
                delete[] matrixCopy[i];
            }
            delete[] matrixCopy;
        } else if (method == 3) {
            for (int i = 0; i < rows; i++) {
                delete[] matrix[i];
            }
            delete[] matrix;
            return 0;
        } else {
            cout << "Invalid method selected. Please choose again." << endl;
            method = 0;
        }
    }
}
