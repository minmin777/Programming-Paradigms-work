/* imdb_functions.c

   Name: YASMINE AYAD
   Resources used (websites / peers / etc):
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "imdb_functions.h"
#include "types.h"

#define STRING_SIZE  300
#define LEN "299"

// Discards all characters until the end of a line in the given file
 void skip_line(FILE* file)
 {
   while(!feof(file) && getc(file) != '\n')
     ;
 }
 

// copy the given string into a newly-malloc'd buffer
char* malloc_string(char* str)
{
  char* new = malloc(sizeof(char) * (strlen(str)+1));
  strcpy(new, str);
  return new;
}

// like strcmp, but ignores differences in case (why does this work?)
 int stricmp(char* s1, char* s2)
 {
   while(true)
   {
     char c1 = *s1++;
     char c2 = *s2++;
     int d = toupper(c1) - toupper(c2);
 
     if(d != 0 || !c1)
     {
       return d;
     }
   }
 }
 

// is the given string composed entirely of dashes?
bool all_dashes(char* str)
{
  while(*str)
  {
    if(*str++ != '-')
    {
      return false;
    }
  }
  return true;
}

// are there any non-ascii characters in the string?
 bool any_bad_chars(char* str)
 {
   while(*str)
   {
     char c = *str++;
     if(c < 0)
     {
       return true;
     }
   }
   return false;
 }
 
// Reads in a cast member from the given file
// preconditions: the file is open and at a line where a cast member begins
//                member points to a valid cast_member struct
//                all_movies is a map of all known movies
// postconditions: if a cast_member can successfully be read from the file,
//                 *member is filled in. Any new movies found while reading
//                 the cast member are added to all_movies, and SUCCESS is returned
//                 Otherwise, if the end of the list of members is reached,
//                 END_OF_LIST is returned. Otherwise, FAILURE is returned.
read_result read_cast_member(FILE* file, cast_member* member, map all_movies)
{
  char buf[STRING_SIZE];
  if(fscanf(file, "%" LEN "[^\t\n]", buf) != 1) return FAILURE;

  if(all_dashes(buf)) return END_OF_LIST;
  // non-ascii chars are alphabetized differently, so we can't handle them here
  if(any_bad_chars(buf)) return FAILURE;

  // WRITE CODE HERE
  // At this point, `buf` contains the name of the cast member, and you can
  // fill in the two data fields of *member.
  //int len = strlen(buf);
  member->name = malloc_string(buf); //making room for name of cast member
  strcpy(member->name, buf); //copying the cast member 
  member->movies = llist_new(); //empty llist
  
	
  while(fscanf(file, "%*[\t]%" LEN "[^\n]", buf) == 1)
  {
    skip_line(file); // eat rest of line
    
    // cut it off at the first instance of 2 spaces
    char* spaces = strstr(buf, "  ");
    if(spaces)
    {
      *spaces = '\0'; // cut off the string here
    }

    // WRITE CODE HERE
    // At this point, `buf` contains the name of the movie. You should:
    //   1. Look up the movie in all_movies to see if it already exists.
    //   2. If not, create (malloc) a new movie object and add it to the map.
    //   3. Update the movie to include the cast member.
    //   4. Update the cast member to include the movie.
    // llist 
    

    if(map_contains(all_movies, buf) == 0){
    	movie* new_movie = malloc(sizeof(movie));
    	new_movie->cast = array_new(); //free new_movie also free the array
    	new_movie->name = malloc_string(buf); 
    	strcpy(new_movie->name, buf); 
    	
    	map_put(all_movies, buf, new_movie);
    	llist_add(member->movies, new_movie);
    	array_add(new_movie->cast, member);
    	

    }
  }

  return SUCCESS;
}

// Merges two sorted arrays. Runs in time linear to the length of the two input arrays.
// preconditions: src1 and src2 are two valid arrays.
//                src1 and src2 are both in sorted order
// postconditions: returns a fresh array containing all the elements of src1 and src2
//                 in sorted order
// Note: You are responsible for freeing the returned array.
array merge_arrays(array src1, array src2)
{
  array src3 = array_new();
  int size1 = array_size(src1);
  int size2 = array_size(src2);
  int i=0, j=0;
  while(i < size1 && j < size2){
  	if(stricmp(array_get(src1, i)->name, array_get(src2, j)->name) < 0){ //array_get get's the element at the position
  		array_add(src3, array_get(src1, i)); //array_add puts an element in the desired array
  		i++;
  	}
  	else{
  		array_add(src3, array_get(src2, j));
  		j++;
  	}
  }
  if(i >= size1){
  	while(j < size2){
  		array_add(src3, array_get(src2, j));
  		j++;
  	}
  }
  if(j >= size2){
  	while(i < size1){
  		array_add(src3, array_get(src1, i)); //array_add puts an element in the desired array
  		i++; 
  	}
  }

return src3;
}

// Finds a cast member in a sorted array of cast members
// preconditions: cast is a valid, sorted array of cast members
//                name is a valid string
// postconditions: If the cast member can be found, returns a pointer to the member
//                 Otherwise, returns NULL.
cast_member* find_cast_member(array cast, char* name)
{
  int size = array_size(cast);
  int first = 0;
  int last = size - 1;
  int middle = (first + last)/2;
  while(first <= last){
  	
  	if(stricmp(array_get(cast, middle)->name, name) == 0){
  		return array_get(cast, middle);
  	}
  	else if(stricmp(array_get(cast, middle)->name, name) < 0){
  		first = middle + 1;
  	}
  	else if(stricmp(array_get(cast, middle)->name, name) > 0){
  		last = middle - 1;
  	}
  		middle = (first + last)/2;
  
  }

  return NULL;
}