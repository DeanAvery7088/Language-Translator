/* Reads two matrices as inputs and prints them to the screen.  Then 
   multiplies the two and prints the resulting matrix.
 */

main ( ) {

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

// Create the new matrix to hold the result of multiplying the two above
matrix newMatrix [numRows : numCols] a : b = a * b;
int a;
int b;
int c;

numRows = numRows(newMatrix) - 1;
numCols = numCols(newMatrix) - 1;
int newCols;
newCols = numCols(matrix1) - 1;

newMatrix = matrix1 * matrix2;
/*
repeat(a = 0 to numRows){
  repeat(b = 0 to numCols){
    newMatrix[a:b] = 0;
    repeat(c = 0 to newCols){
      newMatrix[a:b] = newMatrix[a:b] + (matrix1[a:c] * matrix2[c:b]);
    }
  }
}
*/
print("\n");
print(newMatrix);

}
