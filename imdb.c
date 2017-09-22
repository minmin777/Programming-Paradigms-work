/* imdb.c

   Main program for interactive IMDB viewer.

   Name: YASMINE AYAD
   Resources used (websites / peers / etc):
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "array.h"
#include "map.h"
#include "llist.h"
#include "llist_node.h"
#include "types.h"

#include "imdb_functions.h"

// the IMDB files contain 239 header lines
#define HEADER_LINES 241


// Reads in a file containing a list of cast members
// preconditions: all_movies exists and maps all movies encountered so far
// postconditions: If the file can be read successfully, returns an array
//                 of all cast members in the file, and updates all_movies
//                 to map all movies encountered. If there is an error reading
//                 the file, returns NULL.
// Note: You are responsible for freeing the returned array (if it's not NULL).


array read_cast_member_file(char* filename, map all_movies)
{

  FILE* file = fopen(filename, "r");
  if(!file)
  {
    printf("Cannot open file.");
    return NULL;
  }

  // skip header
  for(int i = 0; i < HEADER_LINES; i++)
  {
    skip_line(file);
  }

  array cast = array_new();
  while(!feof(file))
  {
    cast_member* member = malloc(sizeof(cast_member));
    read_result result = read_cast_member(file, member, all_movies);
    
    switch(result)
    {
    case SUCCESS:
      array_add(cast, member);
      // This is helpful for seeing progress as you're loading a file.
      if(array_size(cast) % 1000 == 0)
	  printf("Added cast member %s\n", member->name);
      
      break;
    case FAILURE:
      free(member);
      skip_line(file); // this makes sure we're always moving forward
      break;
      
    case END_OF_LIST:
      free(member);
      return cast;
    }
  }

  return cast; // shouldn't get here unless file is truncated
}

// Our main program loop.
// See King, p. 302, about argc and argv.
int main(int argc, char** argv)
{
  if(argc < 2)
  {
    printf("Usage: %s [cast_member lists]\n", argv[0]);
    return 1;
  }
	   
  map all_movies = map_new();
  array all_cast = array_new();

  // start i at one to skip program name
  for(int i = 1; i < argc; i++)
  {
    array some_cast = read_cast_member_file(argv[i], all_movies);

    if(!some_cast)
    {
       // file reading failed, but read_cast_member_file alerted the user already
      continue;
    }

    // WRITE CODE HERE
    // At this point, some_cast has the cast members most recently read in,
    // and all_cast has all previous cast members.
    // You need to merge (with a call to merge_arrays) these two arrays, producing
    // a new all_cast that contains both.
    all_cast = merge_arrays(some_cast, all_cast);
  }
  char arr[200]; // here better
  char ano[300];
  for(;;)//idk what to put for the loop
  { 
  	
	printf("Enter a cast member or hit enter to quit: ");
  	fgets(arr, 200, stdin);
  	size_t ln = strlen(arr)-1;
	if (arr[ln] == '\n'){
    	   arr[ln] = '\0';
        }
    if(strncmp(arr, "", 200) == 0){
    	break;}
    //FOR FLEX POINTS OUTPUT MOVIES AND ASK PERSON TO ENTER MOVIE AND THE CAST MEMBERS WILL COME OUT
    if(find_cast_member(all_cast, arr) != NULL){
    	printf("%s found.\n", find_cast_member(all_cast, arr)->name);
    	//THIS IS FOR PRINTING OUT ALL THE MOVIES ASSOCIATED WITH THE PERSON
		while(find_cast_member(all_cast, arr)->movies->head != NULL){
			printf("%s\n", find_cast_member(all_cast, arr)->movies->head->data->name);
			find_cast_member(all_cast, arr)->movies->head = find_cast_member(all_cast, arr)->movies->head->next;
		}
		//ASKING THE USER TO INPUT THE PERSON"S MOVIE
		printf("Enter a movie, if no movies hit enter: ");
		fgets(ano, 300, stdin);
		size_t len = strlen(ano)-1;
		if (ano[len] == '\n'){
    	   ano[len] = '\0';
        }
        //TAKING THE MOVIE AND PRINTING OUT THE CAST MEMBERS OF THE MOVIE
        if(map_contains(all_movies, ano) == 1){
        	int q = array_size(map_get(all_movies, ano)->cast);
        	//Array to print out the cast members that the array cast points to
        	for(int t = 0; t < q; t++){
        		printf("Cast Members of Movie:\n %s\n", array_get(map_get(all_movies, ano)->cast, t)->name);
        }
        }
	}
    
    else{
    	printf("Cast Member not found.\n");
    }
     // did this to see if it will print out the name of the cast member
    //ALSO PRINT OUT ALL OF THE MOVIES OF THE NAME
    
    
    // WRITE CODE HERE
    // THIS IS NUMBER 3 ON THE HOMEWORK
    // This is the main interactive loop, which you must write, as described
    // in the assignment.
    // When the user is done, this should `break`.
  
  }
  
  
  //Freeing pointers the the array all_cast points to
  for(int j=0; j < array_size(all_cast); j++){
  	cast_member* current = array_get(all_cast, j);
  	//array_free(all_cast);
  	free(current->name);
  	llist_free(current->movies);
  	free(current);
  }
  	
  //malloc map_entry struct movie and then put entries from map into movie and free the entries, but when I printed
  //the movies entries they were all the same movie so it's freeing the same thing
  map_entry* movie = malloc(map_size(all_movies)*sizeof(map_entry));
  for(int m=0; m < map_size(all_movies)*sizeof(map_entry); m++){
  	map_get_entries(all_movies, &movie[m]);
	free(&(movie+m)->value->name);
  	array_free((movie+m)->value->cast);
  }
  free(movie);
  
  array_free(all_cast);
  map_free(all_movies);
  // WRITE CODE HERE
  // Free all used memory before exiting.
  
  return 0;
}

