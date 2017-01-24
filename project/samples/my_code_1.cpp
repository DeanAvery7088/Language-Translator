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

matrix newMatrix1 (numRows,numCols);
for (int a = 0; a < numRows; a++) {
for (int b = 0; b < numCols; b++) {
*(newMatrix1.access(a, b)) = (a * b); 
} }

newMatrix1 = (matrix1 * matrix2);

cout << newMatrix1;
cout << "\n";
matrix matrix3 ( matrix::matrixRead("../samples/my_code_1_matrix3.data") ) ; 

cout << matrix3;
cout << "\n";
matrix matrix4 ( matrix::matrixRead("../samples/my_code_1_matrix4.data") ) ; 

cout << matrix4;
cout << "\n";
numRows = matrix3.numRows();

numCols = matrix4.numCols();

matrix newMatrix2 (numRows,numCols);
for (int a = 0; a < numRows; a++) {
for (int b = 0; b < numCols; b++) {
*(newMatrix2.access(a, b)) = (a * b); 
} }

newMatrix2 = (matrix3 * matrix4);

}
