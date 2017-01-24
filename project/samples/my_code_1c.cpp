#include <iostream>
#include "Matrix.h"
#include <math.h>
using namespace std;
int main ( ) {
matrix m (2,2);
for (int i = 0; i < 2; i++) {
for (int j = 0; j < 2; j++) {
*(m.access(i, j)) = (i * j); 
} }

int i;
int j;
for (i = 0; i <= 1; i++) { 
for (j = 0; j <= 1; j++) { 
*(m.access(i, j)) = 2 ;
}

}

matrix n (2,2);
for (int h = 0; h < 2; h++) {
for (int k = 0; k < 2; k++) {
*(n.access(h, k)) = (h * k); 
} }

int h;
int k;
for (h = 0; h <= 1; h++) { 
for (k = 0; k <= 1; k++) { 
*(n.access(h, k)) = 2 ;
}

}

*(n.access(0, 1)) = 3 ;
*(n.access(1, 1)) = 11 ;
*(m.access(0, 0)) = 22 ;
*(m.access(1, 1)) = 13 ;
matrix L (2,2);
for (int a = 0; a < 2; a++) {
for (int b = 0; b < 2; b++) {
*(L.access(a, b)) = (a * b); 
} }

int a;
int b;
int c;
for (a = 0; a <= 1; a++) { 
for (b = 0; b <= 1; b++) { 
*(L.access(a, b)) = 0 ;
}

}

L = (m * n);

cout << m;
cout << "\n";
cout << n;
cout << "\n";
cout << L;
}
