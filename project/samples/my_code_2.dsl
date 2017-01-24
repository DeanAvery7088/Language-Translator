/* This program shows the output of two fibonacci sequences,
   one generated using repeat and the other using while.
 */

main () { 
  int i ;
  int m ;
  int save ;
  int k ; 
  i = 0;
  m = 1;
  save = 0;

  repeat ( k = 0 to 10){
    print ( i );
    print (" ");
    save = m ; 
    m = i + m ;
    i = save ; 
  }
  print("\n\n");

  i = 0;
  m = 1;
  k = 0;
  while ( k <= 10){
    print ( i );
    print (" ");
    save = m ; 
    m = i + m ;
    i = save ; 
    k = k + 1;
  }
  print("\n");

}

