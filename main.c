/* main.c

   Name: Yasmine Ayad
*/

#include "matrix.h"
#include <stdio.h>
#include <time.h>

int main()
{
  int i, j;
  int mat[50][50], result[50][50];
  //puts random numbers in the array
  for(i =0; i < 50; i++){
    for(j = 0; j < 50; j++){
      mat[i][j] = rand();
      result[i][j] = rand();
}
}
  //for matrix_pow()
  clock_t start_clock = clock();

  matrix_pow(50, mat, 2, result);

  clock_t stop_clock = clock();

  printf("Processor time used for matrix_pow; %g sec. \n", (stop_clock - start_clock));
  //for matrix_pow_rec()
  clock_t tic = clock();

  matrix_pow_rec(50, mat, 2, result);

  clock_t toc = clock();

  printf("Processor time used for matrix_pow_rec: %g sec. \n", (toc - tic));
	 

  return 0;
}
