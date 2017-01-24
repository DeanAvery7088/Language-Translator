#include <iostream>
#include "Matrix.h"
#include <math.h>
using namespace std;
int main ( ) {
matrix matrix1 ( matrix::matrixRead("../samples/my_code_1_matrix1.data") ) ; 

cout << matrix1;
cout << "\n";
matrix matrix2 ( matrix::matrixRead("../samples/my_code_1_matrix2.data") ) ; 

cout << matrix2;
cout << "\n";
int numRows;
numRows = matrix1.numRows();

int numCols;
numCols = matrix2.numCols();

matrix newMatrix (numRows,numCols);
for (int a = 0; a < numRows; a++) {
for (int b = 0; b < numCols; b++) {
*(newMatrix.access(a, b)) = (a * b); 
} }

int a;
int b;
int c;
numRows = (newMatrix.numRows() - 1);

numCols = (newMatrix.numCols() - 1);

int newCols;
newCols = (matrix1.numCols() - 1);

newMatrix = (matrix1 * matrix2);

cout << "\n";
cout << newMatrix;
}
