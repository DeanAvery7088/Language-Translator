/* Reads two matrices as inputs and prints them to the screen.  Then 
   multiplies the two and prints the resulting matrix.

   This program uses the EXTRA CREDIT matrix multiplication overload.
 */

main ( ) {

// First trying matrix multiplication on compatible matrices
matrix matrix1 = matrixRead( "../samples/my_code_1_matrix1.data" );
print(matrix1);
print ("\n");
matrix matrix2 = matrixRead( "../samples/my_code_1_matrix2.data" );
print(matrix2);
print ("\n");

int numRows;
numRows = numRows(matrix1);
int numCols;
numCols = numCols(matrix2);

matrix newMatrix1 [numRows : numCols] a : b = a * b;

// EXTRA CREDIT:  simply multiply using overloaded *
newMatrix1 = matrix1 * matrix2;

print(newMatrix1);
print ("\n");

// Try matrix multiplication on incompatible matrices
matrix matrix3 = matrixRead( "../samples/my_code_1_matrix3.data" );
print(matrix3);
print ("\n");
matrix matrix4 = matrixRead( "../samples/my_code_1_matrix4.data" );
print(matrix4);
print ("\n");

numRows = numRows(matrix3);
numCols = numCols(matrix4);

matrix newMatrix2 [numRows : numCols] a : b = a * b;

newMatrix2 = matrix3 * matrix4;


}
