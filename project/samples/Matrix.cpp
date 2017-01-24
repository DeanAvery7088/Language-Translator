#include "Matrix.h"

using namespace std;

// Construct a matrix of dimensions i and j
matrix::matrix(int i, int j) {
    rows = i;
    cols = j;
    data = new float*[rows];
    for(int k = 0; k < rows; k++) {
        data[k] = new float[cols];
    }
}

// matrix constructor using matrix at address m
matrix::matrix(const matrix& m) {
    rows = m.rows;
    cols = m.cols;
    data = m.data;
}

int matrix::numRows() {
    return rows;
}

int matrix::numCols() {
    return cols;
}

// Access the matrix data at coordinates i and j
float *matrix::access(const int i, const int j) const {
    return ( &data[i][j] );
}

/* The output stream is constructed to match that of the matrix address passed in.  
   The format is as shown below.  The first two numbers represent #rows #cols.

   4 5         
   1 2 3 4 5
   2 3 4 5 6
   3 4 5 6 7
   4 5 6 7 8
*/
std::ostream& operator<<(std::ostream &os, matrix &m) {
    int numRows = m.numRows();
    int numCols = m.numCols();

    // Output the top row to the output stream
    os << numRows << " " << numCols << endl;

    // Complete output of the remaining matrix
    for(int i=0; i < numRows; i++) {
        for(int j=0; j < numCols; j++) {
	    os << *m.access(i, j);
	    os << "  ";
	}

	os << endl;
    }	
}

// Overload multiplication operator, version 1
matrix operator*(const matrix &m1, const matrix &m2) {
    int numRows = m1.rows;
    int numCols = m2.cols;

    if(m1.cols != m2.rows) {
        cout << "ERROR: Trying to perform multiplication on incompatible matrices\n";
    }

    else { 
        matrix newMatrix (numRows, numCols);
        numRows = (newMatrix.numRows() - 1);
        numCols = (newMatrix.numCols() - 1);
        int newCols = (m1.cols - 1);

        for (int a = 0; a <= numRows; a++) { 
            for (int b = 0; b <= numCols; b++) { 
                *(newMatrix.access(a, b)) = 0;
                for (int c = 0; c <= newCols; c++) { 
                    *(newMatrix.access(a, b)) = (*(newMatrix.access(a, b)) + (*(m1.access(a, c)) * *(m2.access(c, b)))) ;
                }
            }
        }

        return newMatrix;
    }

}

// Overload multiplication operator, version 2
/*
matrix matrix::operator * (matrix &m1){
  int numRows = this -> numRows();
  int numCols = m1.numCols(); 

  matrix newMatrix(numRows,numCols);
  
  numRows = newMatrix.numRows() - 1;
  numCols = newMatrix.numCols() - 1;
  int newCols = this->numCols() - 1 ;

  for (int a = 0; a <= numRows; a++){
    for ( int b = 0; b <= numCols; b++){
      *(newMatrix.access(a,b)) = 0;
      for ( int c = 0; c <= newCols; c++){
        *(newMatrix.access(a,b)) = *(newMatrix.access(a,b)) + (*(this -> access(a,c)) * *(m1.access(c,b))) ; 
      }
    } 
  }
  return newMatrix;
   
} 
*/


matrix matrix::matrixRead(std::string filename) {
    // Create an internal file stream matrixFile
    ifstream matrixFile(filename.c_str());
    if (matrixFile.is_open()) {  // Ensure matrixFile was able to be opened 
	// Grab the first two integers from matrixFile; representing rows and columns
        // and then create a new matrix of the indicated size
        int numRows = 0; 
	int numCols = 0;
        matrixFile >> numRows >> numCols;
        matrix *m = new matrix(numRows, numCols);
    
	// Read the matrix data from the incoming matrixFile, using it to fill in matrix m 
        for(int i=0; i < (m->rows) ; i++) {
            for(int j=0; j < (m->cols) ; j++) {
	        matrixFile >> (m->data[i][j]) ;
            }
        }

        matrixFile.close();
        return *m;
    }

    else {
        cout << "ERROR: matrixRead ifstream was unable to open matrixFile";
    }

}

