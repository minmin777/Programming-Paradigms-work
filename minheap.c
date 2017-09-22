/*
  YASMINE AYAD AND MIMI BENKOUSSA
  minheap.c
  Description: a minheap is a binary tree such that the data contained in each
  node is <= the data in that node's children. The binary tree must be complete.
  Represented as an array; heaps are "partially ordered"
    For node at i: (i begins at 1; so i>0)
    Left child is at 2i
    Right child is at 2i+1
    Parent is at i/2
  Functions: NEW HEAP, INSERT (@ end of heap, and then percolate by comparing 
  to the parent at index i/2), REMOVE MIN MOST ELEMENT (remove root), FREE HEAP
http://wikistack.com/c-program-for-min-heap/
*/

#include <stdlib.h>
#include <stdio.h>
#include "minheap.h"


// index 0 cell of array is skipped --> for a[i], root is at i=1 (a[1]). i = position
#define LEFTC(i) 2i+1     // left child is at 2i --> 2i+1 since root @ a[1]
#define RIGHTC(i) 2i+2     // right child is at 2i+1 --> 2i+2 since root @ a[1]
#define PARENT(i) (i-1)/2  // parent is at i/2 --> (i-1)/2 since root @ a[1]


// minheap_node struct
typedef struct minheap_node{
  int data;
} minheap_node;


// minheap struct
typedef struct minheap{
  minheap_node *elem;      // pointer to the heap
  int size;                // size of the min heap
} minheap;


// minheap_init; returns an empty minheap. CALL FREE FUNCTION WHEN DONE
minheap_init minheap_empty(){
  minheap_init mh = malloc(sizeof(minheap));
  mh->elem = NULL;
  mh->size = 0;
  return mh;
}


// creates a new minheap with given size
void new_minheap(minHeap *mh, int *arr, int size){
  int i;
  for(i=0; i<size; i++){ // goes through minheap
    if(mh->size){
      mh->elem = realloc(mh->elem, (mh->size + 1) * sizeof(minheap_node));
    }
    else(){
      mh->elem = malloc(sizeof(minheap_node));
    }
    minheap_node mhnd;
    nd->data = arr[i];  // data inside this node is that of the array at position i
    mh->elem[(mh->size)++] = mhnd; // increments mh->size
  }
}


// new node; adds a node to the minheap depending on the node's data
void insert_node(minHeap *mh, int data){
  if(mh->size){
    mh->elem = realloc(mh->elem, (mh->size + 1) * sizeof(minheap_node));
  }
  else(){
    mh->elem = malloc(sizeof(minheap_node));
  }
  minheap_node mhnd;
  //mhnd->data = data;
  int i = (mh->size)++;
  while(i && mhnd->data < mh->elem[PARENT(i)]->data){
    mh->elem[i] = mh->elem[PARENT(i)];
    i = PARENT(i);
  }
    mh->elem[i] = mhnd;

    
// remove min
void deleteNode(minHeap *mh){
  if(mh->size){
    mh->elem[0] = mh->elem[--(mh->size)];
    mh->elem = realloc(mh->elem, mh->size * sizeof(minheap_node));
  }
  else{
    free_minheap(mh->elem);
  }
}


// free - not sure how to implement
void free_minheap(minheap_node* root){
  if(PARENT(1)){
    free_minheap(LCHILD);
    free_minheap(RCHILD);
    free_minheap(PARENT);
  }
}
