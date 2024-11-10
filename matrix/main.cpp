#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
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
                cout << "Please write x" << j + 1 << " in equation " << i + 1 << ": ";
            } else {
                cout << "Please write result for equation " << i + 1 << ": ";
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

void GaussJordanElimination(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        double lead = matrix[i][i];
        if (lead == 0) {
            cout << "System can't be solved, because of division by zero" << endl;
            return;
        }

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

    cout << "\nMatrix after Gauss-Jordan Elimination (Final Step):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols + 1; j++) {
            cout << setw(10) << matrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nSolution:\n";
    for (int i = 0; i < rows; i++) {
        cout << "x" << i + 1 << " = " << matrix[i][cols] << endl;
    }
}

double numberModule(double x)
{
    return (x < 0) ? -x : x;
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

void checkAndSwap(double** matrix, int rows, int cols)
{
    if(cols == 2 && rows == 2)
    {
        if(numberModule(matrix[0][0]) < numberModule(matrix[0][1]))
        {
            if(numberModule(matrix[1][0]) > numberModule(matrix[1][1]))
            {
                swap(matrix[0][0], matrix[1][0]);
                swap(matrix[0][1], matrix[1][1]);
            }
            else
                cout << "Matrix can't be solved by using Seidel Method" << endl;
        }
    }
    if(cols == 3 && rows == 3)
    {
        if(numberModule(matrix[0][0]) < numberModule(matrix[0][1]) + numberModule(matrix[0][2]))
        {
            if(numberModule(matrix[1][0]) > numberModule(matrix[1][1]) + numberModule(matrix[1][2]))
            {
                swap(matrix[0][0] , matrix[1][0]);
                swap(matrix[0][1] , matrix[1][1]);
                swap(matrix[0][2] , matrix[1][2]);
            }
            else if(numberModule(matrix[2][0]) > numberModule(matrix[2][1]) + numberModule(matrix[2][2]))
            {
                swap(matrix[0][0] , matrix[2][0]);
                swap(matrix[0][1] , matrix[2][1]);
                swap(matrix[0][2] , matrix[2][2]);
            }
        }
        else if(numberModule(matrix[1][1]) < numberModule(matrix[1][0]) + numberModule(matrix[1][2]))
        {
            if(numberModule(matrix[0][1]) > numberModule(matrix[0][0]) + numberModule(matrix[0][2]))
            {
                swap(matrix[1][0] , matrix[0][0]);
                swap(matrix[1][1] , matrix[0][1]);
                swap(matrix[1][2] , matrix[0][2]);
            }
            else if(numberModule(matrix[2][1]) > numberModule(matrix[2][0]) + numberModule(matrix[2][2]))
            {
                swap(matrix[1][0] , matrix[2][0]);
                swap(matrix[1][1] , matrix[2][1]);
                swap(matrix[1][2] , matrix[2][2]);
            }
        }
        else if(numberModule(matrix[2][2]) < numberModule(matrix[2][0]) + numberModule(matrix[2][1]))
        {
            if(numberModule(matrix[0][2]) > numberModule(matrix[0][0]) + numberModule(matrix[0][1]))
            {
                swap(matrix[2][0] , matrix[0][0]);
                swap(matrix[2][1] , matrix[0][1]);
                swap(matrix[2][2] , matrix[0][2]);
            }
            else if(numberModule(matrix[1][2]) > numberModule(matrix[1][0]) + numberModule(matrix[1][1]))
            {
                swap(matrix[2][0] , matrix[1][0]);
                swap(matrix[2][1] , matrix[1][1]);
                swap(matrix[2][2] , matrix[1][2]);
            }
        }
        else
            cout << "Matrix can't be solved by using Seidel Method" << endl;
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
            GaussJordanElimination(matrix, rows, cols);
        } else if (method == 2) {
            SeidelMethod(matrix, rows, cols);
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
