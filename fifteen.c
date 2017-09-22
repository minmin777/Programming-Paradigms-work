/* fifteen.c
 *
 * Name: Yasmine Ayad
 * Desc: Allows the user to play the "Fifteen puzzle"
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdbool.h>
#include <stdlib.h>

// These lines define constants which can be used throughout your program
// to aid in your code. They are explained on p. 315 of King and have a
// nice introduction on this page:
// http://www.dummies.com/programming/c/how-to-declare-and-use-constants-in-the-c-language/

// representation for the empty spot in the puzzle
#define BLANK        0

// side-length of the puzzle
#define PUZZLE_SIZE  4 

// arrays do strange and wonderful things when passed as parameters, so we'll just
// use a global variable. This puzzle variable is accessible anywhere in your program.
int puzzle[PUZZLE_SIZE][PUZZLE_SIZE]
  = { {1, 10, 15,     4},
      {13, 6,  3,     8},
      {2,  9, 12,     7},
      {14, 5, BLANK, 11} }; // global puzzle array



// Solvable puzzle
int puzzlewon[PUZZLE_SIZE][PUZZLE_SIZE]
  = { {1, 2, 3,     4},
      {5, 6,  7,     8},
      {9,  10, 11,    12},
      {13, 14, 15, BLANK} };  // Winning puzzle

// the functions below are a suggestion for a way to write this assignment, though
// they are not a requirement

// prints the puzzle
void print_puzzle()
{
  int i, j;
  for(i=0; i < PUZZLE_SIZE; i++){
    for(j=0; j < PUZZLE_SIZE; j++){
      printf("%2d ", puzzle[i][j]);
    }
    printf("\n");
  }
}

// prompts the user to enter a tile number and returns that number
int prompt()
{
  int tile;
  printf("Enter the tile you would like to move: ");
  scanf("%d", &tile);
  printf("\n");
  return tile;
  
}

// moves the tile in the puzzle, if possible.
int move_tile(int tile)
{
  int blankrow, blankcol, tilerow, tilecol;
  int i, j;
  //if the tile is 0 then blankrow is the i and blankcolumn is j
  //if the tile is the tile that was input then the tilerow is i and tilecolumn is j
  for(i = 0; i < PUZZLE_SIZE; i++){
    for(j = 0; j < PUZZLE_SIZE; j++){
      if(puzzle[i][j] == 0){
	blankrow = i;
	blankcol = j;
      }
      else if(puzzle[i][j] == tile){
	tilerow = i;
	tilecol = j;
      }
    }
  }
  //the tile and blank are next to each other when blankrow and tilerow are the same and 
  if((blankrow == tilerow  && abs(blankcol - tilecol) == 1)||
     (blankcol == tilecol && abs(blankrow - tilerow) == 1)) {
    puzzle[blankrow][blankcol] = puzzle[tilerow][tilecol];//moves the tile wanted to the previously 0 tile
    puzzle[tilerow][tilecol] = 0;// makes the tile you moved to 0
	return 1; //tells that you can move the tile
    }
    return 0; //can't move the tile
}

// returns true when the puzzle is solved
bool solved()
{
  int i, j;
  for(i =0; i < PUZZLE_SIZE; i++)
    {
      for(j=0; j < PUZZLE_SIZE; j++){
	if(puzzle[i][j] != puzzlewon[i][j]){
	  return false; //if one piece of the tile doesn't match the expected tile then it wasn't won
	}
      }
    }
  return true; //otherwise game won
}

int main()
{
  int tile;
  print_puzzle();
    while(1){
      tile = prompt();
      if(move_tile(tile) == 1){
	print_puzzle();
      }
      else{
	printf("Invalid move \n");
	print_puzzle();
      }
      if(solved() == true){
	printf("you won! \n");
	break;
      }
    }
  return 0;
}
