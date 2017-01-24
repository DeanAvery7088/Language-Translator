/* Test program that multiplies two 2x2 matrices and prints the result */

main () { 
  matrix m [ 2 : 2 ] i : j = i * j ;
  int i ;
  int j ;
  repeat ( i = 0 to 1 ) {
    repeat ( j = 0 to 1) {
      m[i:j] = 2 ;
    }
  }

  matrix n [ 2 : 2 ] h : k = h * k ;
  int h ;
  int k ;
  repeat ( h = 0 to 1 ) {
    repeat ( k = 0 to 1) {
      n[h:k] = 2 ;
    }
  }
  n[0:1] = 3;
  n[1:1] = 11;
  m[0:0] = 22;
  m[1:1] = 13;
  matrix L [ 2 : 2 ] a : b = a * b ;
  int a ; 
  int b ;
  int c ;
  repeat ( a = 0 to 1 ) {
    repeat ( b = 0 to 1 ) {
	L[a:b] = 0 ; 		   
    }
  }
  L = m * n;

  //repeat (a = 0 to 1) {
  //  repeat (b = 0 to 1) {
  //    print (L[a:b]) ;
  //    print ( " ") ; 
  //  }
  //  print ( "\n" ) ; 
  //}

  print(m);
  print("\n");
  print(n);
  print("\n");
  print(L);

}



