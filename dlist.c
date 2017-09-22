/* dlist.c

   Implementation of an singly linked list sequence
   
   WORKED WITH MIMI BENKOUSSA
*/

#include <stdlib.h>

#include "dlist.h"
#include "dlist_node.h"

typedef struct dlist_record{
  dlist_node* head;
  dlist_node* tail;
  int size;
}dlist_record;

// return an empty dlist. Make sure to call dlist_free when you're done
// with it.
dlist dlist_new(){
  dlist l = malloc(sizeof(dlist_record));
  l->head = NULL;
  l->tail = NULL;
  l->size = 0;
  return l;
}

// returns the number of elements in the dlist. Runs in constant time.
int dlist_size(dlist l){
  return l->size;
}

// appends a new element to the beginning of the dlist. Runs in constant time.
void dlist_push(dlist l, int elt){
  l->head = new_node(elt, l->head, l->tail);
  l->size++;
}

// removes and returns the first element in the dlist. Runs in constant time.
// precondition: there is at least one element in the dlist.
int dlist_pop(dlist l){

  if(l->size == 1){ //if one element 
    //dlist_node* old_head = l->head;
    //int val = old_head->data;
    free(l);
    l->size--;
    //free(old_head); //is this correct?
    return l->head->data;
    //free(l);
    //l->size--;
  }
  else{
    dlist_node* old_head = l->head;
    int val = old_head->data;
    l->head = old_head->next;
    l->head->prev = NULL;
    l->size--;
    free(old_head);
    return val;  // account for the prev pointer, that accounts for empty space -> set it to NULL
  }
  
}

// returns the first element in the dlist, without changing the dlist.
// Runs in constant time.
// precondition: there is at least one element in the dlist.
int dlist_peek(dlist l){
  return l->head->data;
}

// appends a new element to the end of the dlist. Runs in constant time.
void dlist_push_end(dlist l, int elt){
  l->tail = new_node(elt, l->head, l->tail);
  l->size++;
}

// removes and returns the last element in the dlist. Runs in constant time.
// precondition: there is at least one element in the dlist.
int dlist_pop_end(dlist l){
  dlist_node* old_tail = l->tail;
  int val = old_tail->data;
  l->tail = old_tail->prev;
  //l->tail->next = NULL;  Our tests worked when we commented this out but that doesn't make sense since the new tail's next has to be NULL
  l->size--;
  free(old_tail);
  return val;
}

// returns the last element in the dlist, without changing the dlist.
// Runs in constant time.
// precondition: there is at least one element in the dlist.
int dlist_peek_end(dlist l)
{
  return l->tail->data;
}

// adds a new element into the dlist, after n existing elements.
// Traverses from whichever side of the dlist is closer.
// precondition: the list has at least n elements
void dlist_insert(dlist l, int n, int elt)
{
  if(n <= l->size - n) //if n is closer to head than tail, or in middle
  {
  	dlist_node* one_before = nth_node(l->head, n);
    insert_after(one_before, elt);
    l->size++;
    
  }
  else //if n is closer to tail - traverse from tail
  {
  	dlist_node* one_before = nth_node_prev(l->tail, n);
    insert_after(one_before, elt);
    l->size++;
    //l->next = new_node(elt, l->head, l->tail); //inserts after n
  }
}
    // dlist :  h x x n x x x x t

// retrieves the nth element of the dlist.
// Traverses from whichever side of the dlist is closer.
// precondition: the list has at least (n+1) elements
int dlist_get(dlist l, int n)
{
  if(n <= l->size -n) //if n is closer to head than tail, or in middle
  {
    return nth_node(l->head, n)->data;
  }
  else //if n is closer to tail - traverse from tail
  {
    return nth_node(l->tail, n)->data;  // ????
  }
}

// sets the nth element of the dlist to a new value.
// Traverses from whichever side of the dlist is closer.
// precondition: the list has at least (n+1) elements
// postcondition: returns the old value of the element that was set
int dlist_set(dlist l, int n, int new_elt)
{
  if(n <= l->size -n) //if n is closer to head than tail, or in middle
  {
    dlist_node* node = nth_node(l->head,n);
    int old_elt = node->data;
    node->data = new_elt;
    return old_elt;
  }
  else //if n is closer to tail - traverse from tail
  {
    dlist_node* node = nth_node_prev(l->tail,n);
    int old_elt = node->data;
    node->data = new_elt;
    return old_elt;
  }
}

// removes the nth element of the dlist.
// Traverses from whichever side of the dlist is closer.
// precondition: the list has at least (n+1) elements
// postcondition: returns the removed element
int dlist_remove(dlist l, int n){
if(n == 0)
  {
    return dlist_pop(l);
  }
else if(n == l->size){
  return dlist_pop_end(l);
 }
else if(n <= l->size -n){
 dlist_node* one = nth_node(l->head, n);
    int elt = one->data;
    delete_node(one);
    l->size--;
    return elt;
 }
 else{
 dlist_node* one = nth_node(l->tail, n);
    int elt = one->data;
    delete_node(one);
    l->size--;
    return elt;
 }
 
}

// frees an dlist. Takes O(size(l)) steps.
void dlist_free(dlist l){
  free_dlist(l->head);
  free_dlist(l->tail);
  free(l); // think about next and prev
}
