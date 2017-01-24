/* Test programs must be in main otherwise condition 1 will apply in 
 * alt_tests.h (will fail to parse entirely)
 */

main () {
   int x;
   x = 5;
   int y;
   y = 0;
   if (x > 3) {
 	y = 7;
   }
   else {
      y = 4;
   }
   while (x > 3) {
 	y = 7;
   } 
}


