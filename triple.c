/* triple.c
 *
 * Name: Yasmine Ayad
 * Desc: This finds a triple in a sequence of numbers put in and then see if the sequence has a triple and returns the numbers not in triple and then if no triple found then it outputs "No run"
 */

#include <stdio.h>

int main(){

  int i=0, found=0, j;
  int a[10] = {0,0,0,0,0,0,0,0,0,0}, ifound[10] = {0,0,0,0,0,0,0,0,0,0};
  //array a is to put the numbers put in that was entered; array ifound is for the numbers that aren't in the run
  printf("Give an interger number: ");
  scanf("%d", &(a[i]));
  while(a[i] != 0){
    if(i > 1){
      if(a[i-2] == (a[i-1]-1) && a[i-1] == (a[i] - 1)){
	found = 1; //run found is true
	ifound[i] = 1; ifound[i-1] = 1; ifound[i-2] = 1;
      }
      }
    i++;
    scanf("%d", &(a[i]));
  }
  if(found == 1){
    printf("Run found \n");
    for(j=0; j<i; ++j){
      if(ifound[j] == 0){
	printf("%d\n", a[j]);
      }
    }
  }

  else{
    printf("No Run \n");
  }

 return 0;
}
