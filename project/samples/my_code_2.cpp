#include <iostream>
#include "Matrix.h"
#include <math.h>
using namespace std;
int main ( ) {
int i;
int m;
int save;
int k;
i = 0;

m = 1;

save = 0;

for (k = 0; k <= 10; k++) { 
cout << i;
cout << " ";
save = m;

m = (i + m);

i = save;

}

cout << "\n\n";
i = 0;

m = 1;

k = 0;

while (k <= 10) { 
cout << i;
cout << " ";
save = m;

m = (i + m);

i = save;

k = (k + 1);

}

cout << "\n";
}
