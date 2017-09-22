/* llist_node.c

   A singly-linked list implementation
   
   DID THE HOMEWORK WITH MIMI BENKOUSSA
*/

#include <stdlib.h>

#include "dlist_node.h"

// create (i.e., malloc) a new node
dlist_node* new_node(int data, dlist_node* next, dlist_node* prev){
 dlist_node* n = malloc(sizeof(dlist_node));
  n->data = data;
  n->next = next;
  n->prev = prev;
  return n;
}

// insert a new node after the given one
// Precondition: Supplied node is not NULL.
void insert_after(dlist_node* n, int data){
  n->next = new_node(data, n->next, n->prev);
}

// insert a new node before the given one
// Precondition: Supplied node is not NULL.
void insert_before(dlist_node* n, int data){
  n->prev = new_node(data, n->next, n->prev);
 
}

// delete the given node
// Precondition: Supplied node is not NULL.
void delete_node(dlist_node* n){
  //dlist_node* delendumn = n->next;
  //dlist_node* delendump = n->prev;
  if(n->prev == NULL){
  n->next = NULL;
  //n->next->prev = NULL;
  free(n);
  }
  else{
  n->prev->next = n->next;
  n->next->prev = n->prev;
  free(n);
  }
  //free(delendump);
}

// return a pointer to the nth node in the list. If n is
// the length of the list, this returns NULL, but does not error.
// Precondition: the list has at least n nodes
dlist_node* nth_node(dlist_node* head, int n)
{
  for(;n>0; n--, head = head->next)
    ;
  return head;
}

int length(dlist_node* head){
int len = 0;
  for( ; head; head = head->next, len++)
    ;
  return len;

}
// return a pointer to the nth previous node in the list. (That is,
// this uses `prev` pointers, not `next` pointers.) If n is
// the length of the list, this returns NULL, but does not error.
// Precondition: the list has at least n nodes
dlist_node* nth_node_prev(dlist_node* tail, int n)
{
int len = length(tail);
  for(;n<len; n--, tail = tail->prev)
    ;
  return tail;

//tail->prev = NULL;
//return tail->prev;
}

// free an entire linked list. The list might be empty.
void free_dlist(dlist_node* head)
{//think about prev too
dlist_node* cur = head;
  while(cur)
  {
    head = cur;
    cur = cur->next;
    free(head);
  }
}

// create a linked list that stores the same elements as the given array.
// Postcondition: returns the head element
dlist_node* from_array(int n, int a[n])
{
  // keep inserting after head
dlist_node* result = NULL;
 //result->prev = NULL;
 //seg fault
 //last element next should be null
  for(int i = n-1; i >= 0; i--)
  {
    result = new_node(a[i], result, NULL);
  }
  return result;
}

// fill in the given array with the elements from the list.
// Returns the number of elements filled in.
// Postcondition: if n is returned, the first n elements of the array
// have been copied from the linked list
int to_array(dlist_node* head, int n, int a[n]){
int i;
  for(i = 0; i < n && head; i++, head = head->next)
  {
    a[i] = head->data;
  }
  return i;
}

// gets the length of a list

