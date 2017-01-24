/* Test programs must be in main otherwise condition 1 will apply in 
 * alt_tests.h (will fail to parse entirely)
 */

main () {
   int z;
   z = 4;
   z = 3 + 4;
}
