/* pointers.c

   Name: Yasmine Ayad
   Resources used (websites, books other than our texts, peers): Mimi Benkoussa 

*/

#include <stdlib.h>
#include <stdio.h>
#include "pointers.h"


/* Returns whether or not the region pointed to by p1 (of length n)
   overlaps with the region pointed to by p2 (of length m). Do not
   assume that p2 is greater than p1. */
bool overlaps(int n, int* p1, int m, int* p2)
{ bool temp;
  int i, j;
  if(((p2+m) < p1) | (p2 > (p1+n)) | ((p1+n) == p2)){
    return false;
  }
  else{
    return true;
  }

}

/* Changes the value in *a, *b, and *c so that *a, *b, and *c are
   in non-decreasing order. */
/*minisort_helper() is a helper function for mini sort so the code doesn't get repetitive*/
  void minisort_helper(int* x, int* y){
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
  }
void minisort(int* a, int* b, int* c)
{ int temp, temp1, temp2;

  if(*a > *b){
    minisort_helper(a, b);

  }
  if(*b > *c){
    minisort_helper(b, c);

  }
  if(*a > *c){
    minisort_helper(a, c);

  }


}

/* Computes the sum of the ints that sit in memory between p
   (inclusive) and q (exclusive). You may assume that q comes
   after p -- that is, q >= p. */
int partial_sum(int* p, int* q)
{
  int sum = 0;
  for(; p < q; p++){
    sum += *p;

  }
  return sum;
}

/* Check whether `n` array elements, starting at `start` and
   incrementing be `step`, all match, according to the rules
   of Tic Tac Toe. Returns X or O if there is a winner, or
   BLANK otherwise. */
int check_line(int* start, int step, int n)
{

  int count=1, temp = 0;
  while(count <= n){
    for(int i = 0; i < n;){

      if(*start != *(start + i*step)){
	return BLANK;
	//++temp;
      }
      i += step;
      count++;
    }
  }
  return *start;
}

/* Check for a winner of Tic Tac Toe. Precondition:
   board points to a region of memory containing at least
   n^2 ints. Returns the winner of Tic Tac Toe, or BLANK
   if there is no winner. */
int tic_tac_toe_winner(int n, int* board)
{
  int i,k;
  int line[n];

  // check rows, horizontal win
  for (i = 0; i < n; i++) {
    for (k = 0; k < n; k++){
      line[k] = board[i+k];
      if(check_line(line,1, n) == 1 | check_line(line, 1, n) == 2) {
	 return line[0];
       }
    }
  }

  //check columns, vertical win
  for (i = 0; i < n; i++) {
    for (k = 0; k < n; k++){
      line[k] = board[i+k];
      if(check_line(line,1, n) == 1  | check_line(line, 1, n) == 2) {
	return line[0];
        }
      }
    }

   
    // check first diagonal
  for (i = 0; i < n; i++){
    line[i] = board[i+i];
    if(check_line(line,1, n) == 1  | check_line(line, 1, n) == 2) {
      return line[0];
    }
  }
  // check second diagonal
  for (i = 0; i < n; i++){
    line[i] = board[i + n-i-1];
    if(check_line(line,1, n) == 1  | check_line(line, 1, n) == 2) {
      return line[0];
    }
  }
						     

   
  return BLANK;
}

