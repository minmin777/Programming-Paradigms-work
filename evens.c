/* evens.c
 *
 * Name: Yasmine Ayad
 * Desc:
 */

#include <stdio.h>

int main(){

  int i, num;
  int array[10] = {0,0,0,0,0,0,0,0,0,0}; //did this because the program was assigning some numbers in the array numbers I didn't put in

  printf("Enter a number(up to ten numbers): ");
  scanf("%d", &num);
  while(num != 0){
    array[i] = num;
    i++;
    scanf("%d", &num);
  }

  for(i = 0; i < 10; i++){
    if(array[i]%2 == 0 && array[i] != 0){
      printf("%d\n", array[i]);
    }
  }

  for(i = 0; i < 10; i++){
    if(array[i]%2 == 1){
      printf("%d\n", array[i]);
    }
  }

  return 0;
}
