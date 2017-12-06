// Minheap header file - used to implement minheap in huffman.c
// Prototypes for minheap functions
//YASMINE AYAD AND MIMI BENKOUSSA

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
minheap_init minheap_empty();

// creates a new minheap with given size
void new_minheap(minHeap *mh, int *arr, int size);

// new node; adds a node to the minheap depending on the node's data
void insert_node(minHeap *mh, int data);

// remove min
void deleteNode(minHeap *mh);

// free - not sure how to implement
void free_minheap(minheap_node* root);
