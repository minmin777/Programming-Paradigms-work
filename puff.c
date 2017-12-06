#include <stdio.h>
#include <stdlib.h>

//#include "huff.h"



/*
typedef struct huff_tree_node{
	int ch;
	int freq;
	
	struct huff_tree_node* left;
  	struct huff_tree_node* right;
} huff_tree_node;
*/


typedef struct huff_tree_node{
	int ch;
	int freq;
	
	struct huff_tree_node* left;
  	struct huff_tree_node* right;
} huff_tree_node;

typedef struct huff_tree{
	int size;
	struct huff_tree_node** array;

}huff_tree;

huff_tree_node* newNode(int ch, int freq){
	huff_tree_node* n = malloc(sizeof(huff_tree_node));
	//printf("%lu\n", sizeof(huff_tree_node));
	n->ch = ch;
	n->freq = freq;
	n->left = NULL;
	n->right = NULL;
	return n;

}

huff_tree* newTree(){
	huff_tree* tree = (huff_tree*)(malloc(sizeof(huff_tree_node)));
	tree->size = 0;
	tree->array = (huff_tree_node**)(malloc(sizeof(huff_tree_node*)));
	return tree;
}

void insert(huff_tree* huff, huff_tree_node* node){
	++huff->size;
	//printf("%d\n", huff->size);
	huff->array[huff->size-1] = node;
}
//just look for the minimum and take out the smallest
huff_tree_node* findMin(huff_tree* huff){
	int smallest = huff->array[0]->freq;
	//printf("smallest: %d\n", smallest);
	//printf("size: %d\n", huff->size);
	int location = 0;
	for(int i =1; i < huff->size; i++){
		//printf("location: %d\n", i);
		if(huff->array[i]->freq < smallest){
			smallest = huff->array[i]->freq;
			location = i;
			//printf("small: %d\n", smallest);
		}
	}
	
	for(int j = 0; j < huff->size -1; j++){
		if(huff->array[j]->freq == smallest && huff->array[j]->ch > huff->array[location]->ch){
			smallest = huff->array[location]->freq;
			//location = j;
		}
	}
	
	huff_tree_node* temp = huff->array[location];
	huff->array[location] = huff->array[huff->size - 1];
	--huff->size;
	return temp;
}

void buildtree(huff_tree* hufftree, int m, int array[m]){
	//huff_tree* hufftree = newTree();
	huff_tree_node* left;
	huff_tree_node* right;
	huff_tree_node* root;
	int ch = -1;
	for(int i = 0; i < m; i++){
		if(array[i] != 0){
			newNode(i, array[i]);
			insert(hufftree, newNode(i, array[i]));
		}
	}
	while(hufftree->size != 1){
		left = findMin(hufftree);
		right = findMin(hufftree);
		root = newNode(ch, left->freq + right->freq);
		root->left = left;
		root->right = right;
		ch -= 1;
		insert(hufftree, root);
	}
	
	//return hufftree->array[0];
}

//void puff(huff_tree_node* root, int bit, FILE* f){
void puff(huff_tree_node** root, int bit, FILE* f){
/*
puff function - the problem with this function is that it only reads a single leaf, and won't 
move on to the next root. Richard mentioned using a double pointer in the parameter (huff_tree_node** root)
so that updates to the parameter are reflected in the calling function.
*/
  //int m;
  //m = sizeof(array[]);                 // array ex "11001101" with size m
  // while(m>0){                          // so long as there is more than 1 node in the tree
    if(!root[0]->left && root[0]->right){   // once reached a root node  with no more left and right nodes
      //return root->ch;   // return the character of that node
      fputc(root[0]->ch, f);
    }
    else if(bit==1){                      // there is at least 1 left/right traversal
      /*int cur = array[0];              // starts at first element 
      if(cur == '0'){                  // 0 means traverse left
      array = puff(root->left, array[m-2]); // repeats process for left node and m-2 (there are 2 less nodes now)*/
      //root = root->left;
      puff(&root[0]->left, bit, f);
      }
    else if(bit == 0){                          // else cur = 1 means traverse right
      //root = root->right;
      puff(&root[0]->right, bit, f);
      //array = puff(root->right, array[m-2]);
      }
    }
    //}
    //return array;


void getfreq(FILE* f, int m, int array[m]){ //int array like hw04
	int c = getc(f);
	for(int i =0; i < m; i++){
		array[i] = 0;
	}
	while(c != EOF){
		array[c] += 1;
		c= getc(f);
	}
}

int main(){
	 int array[256];
	 int freq = 0;
	 int f = 0;
	 int bit;
	 huff_tree* tree = newTree();
	 //huff_tree_node* root = newNode();
	 FILE* fp = fopen("test3.txt", "r");
	 FILE* fw = fopen("sample.txt", "w");
	 int c = fgetc(fp);
	 getfreq(fp, 256, array);
	 
	 buildtree(tree, 256, array);
	 for(int i =0; i< 256; i++){
	   if(array[i] != 0){
	     freq += array[i];
	   }
	 }
	 
	 
	 for(int h =0; h< 256; h++){
	   if(array[h] != 0){
	     //freq += array[h];
	     printf("i: %d freq: %d\n", h , array[h]); 
	   }
	 }
	 printf("total: %d\n", freq);
	 while(c != EOF || f != freq){
	   for(int j = 0; j < 8; j++){
	     bit = (c & (1 << j)) >> j;
	     puff(tree->array, bit, fw);
	     
	   }
	   c = fgetc(fp);

	 }

return 0;
}
