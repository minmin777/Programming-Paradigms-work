/* matrix.c

   Name: Yasmine Ayad
   Resources used (websites, books other than our texts, peers): Mimi Benkoussa

*/

#include "matrix.h"


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// checks to see if two NxM matrices are the same
bool eq_matrix(int n, int m, int mat1[n][m], int mat2[n][m])
{
  int i, j;
  for(i = 0; i < n; i++){
    for(j = 0; j < m; j++){
      if(mat1[i][j] != mat2[i][j]){
	return false;
      }
    }
  }
  return true;
}


// prints an NxM matrix
void print_matrix(int n, int m, int mat[n][m])
{
  int i, j;
  for(i=0; i< n; i++){
    for(j=0; j< m; j++){
      printf("%2d ",mat[i][j]);
    }
    printf("\n");
  }
}

// fills in an NxN matrix with the identity matrix
void identity_mat(int n, int mat[n][n])
{
  int i, j;
  for(i=0; i < n; i++){
    for(j=0; j < n; j++){
      if(i == j){
	mat[i][j] = 1;
      }
      else{
	mat[i][j] = 0;
      }
    }
  }
}

// multiplies an NxM matrix by a scalar; stores the result in `result`
void scalar_mult(int scalar, int n, int m, int mat[n][m], int result[n][m])
{
  int i, j;
  for(i = 0; i < n; i++){
    for(j = 0; j < m; j++){
      result[i][j] = mat[i][j]*scalar; 
    }
  }
}

// multiplies an N1xM1 matrix by a M1xM2 matrix, storing the result in `result`
void matrix_mult(int n1, int m1, int mat1[n1][m1],
                 int m2, int mat2[m1][m2],
                 int result[n1][m2])
{
  int i, j, k;
  //initialize the arrays
  for(i = 0; i < n1; i++){
    for(j = 0; j < m2; j++){
      result[i][j] = 0;
    }
  }

  //does the matrix multiplication
  for(i = 0; i < n1; i++){
    for(j=0; j< m2; j++){
      for(k = 0; k < m1; k++){
	result[i][j] += mat1[i][k] * mat2[k][j];
      }
    }
  }


}

// Exponentiate an NxN matrix. The result is stored in `result`.
void matrix_pow(int n, int mat[n][n], int power, int result[n][n])
{

  int mat1[n][n];
  if(power == 0){
    identity_mat(n, result);
  }
  //stores mat into mat1
  scalar_mult(1, n, n, mat, mat1);
  
  while(power != 0){
    if(power == 1){
      scalar_mult(1, n, n, mat1, result);
      power--;
      }
    else{
      matrix_mult(n, n, mat, n, mat1, result);
      scalar_mult(1, n, n, result, mat1);
      power--;
    }
  }
}

// Exponentiate an NxN matrix. The result is stored in `result`.

void matrix_pow_rec(int n, int mat[n][n], int power, int result[n][n])
{
  int mat1[n][n], mymat1[n][n],mymat2[n][n],mymat3[n][n];
  if(power == 0){
      identity_mat(n, result);
    }
  if(power == 1){
      scalar_mult(1, n, n, mat, result);
    }
    //when power is even; works with the unit testing if the odd isn't there
  if(power%2 == 0){
      matrix_mult(n, n, mat, n, mat, result);
      scalar_mult(1, n, n, result, mat1);
      matrix_pow_rec(n, mat1, power/2,result);
    }
    //function works for evens if you delete if power is odd below
  else{
      matrix_mult(n, n, mat, n, mat, result);
      scalar_mult(1, n, n, result, mat1);
      matrix_pow_rec(n, mat1, (power-1)/2,result);
      scalar_mult(1, n, n, result, mymat1);
      matrix_mult(n, n, mat, n, mymat1, result);
      
    }
    
}

