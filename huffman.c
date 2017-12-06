//YASMINE AYAD AND MIMI BENKOUSSA
//BIT COUNTER http://cs-fundamentals.com/tech-interview/c/c-program-to-count-number-of-ones-in-unsigned-integer.php
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

typedef struct code{
	int size;
	int num;
	//struct code* array; in main 
}code;

typedef struct bits_writer{
	FILE* f;
	int size;
	int fp; //use bitwise shifters and divide by 10 for the number I have


}bits_writer;


bits_writer* newWriter(){
	bits_writer* bw = malloc(sizeof(bits_writer));
	bw->f = fopen("test3.txt", "w");
	bw->size = 0;
	bw->fp = 0;
	return bw;
}



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






//insert function
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

//
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
//generate the codes - code[m] is just an array and when letter 'a' for example so code[97] would say its huffman code
//BETTER TO DO WITH SHIFT
int bitCount(unsigned int n) {
    unsigned int c; // the total bits in n
  	for (c = 0; n; n >>= 1)
  	{
    	c += (n & 1) | 1;
  	}
  	return c;
 }
 
void getcodes(huff_tree_node* root, code c[256], int code1, int ch){

	if(root->ch == ch){
		
		c[ch].num = code1;
		if(c[ch].num == 0){
			c[ch].size = 1;
		}
		else{
			c[ch].size = bitCount(c[ch].num);
		}
	}
	
	else if(root->left && root->right){
		getcodes(root->left, c, code1<<1, ch);
		getcodes(root->right, c, (code1<<1)+1, ch);
		
		
		
	
	}
	
	
}


//get frequency - using an array and ascii if the letter is a it's ascii code is 97 so array[97] would say its frequency
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

//changes the bits to byte so we can use putc to the file 
void put_bit(bits_writer* bw, int bit, int size){
	//use putc
	
	int byte = 0;
	int byte1 = 0;
	int b;
	int mask[bw->size];

	if(bw->size >= 8){
    	byte = bw->fp >> (bw->size - 8);
    	//printf("byte: %d bit: %d\n", byte, bw->fp);
    	fputc(byte, bw->f);
    	bw->fp = ((bw->fp & 0xF) >> 1) - 1; 
    	bw->size = bw->size - 8;
    	//printf("byte1: %d bit: %d size: %d\n", byte, bw->fp, bw->size);
    	
    		
	}
	else{
		bw->fp = (bw->fp << size)| bit;
		bw->size += size;
		//printf("%d size: %d\n", bw->fp, bw->size);
	}
	
	
	
    		
    	
    
 // For debugging purposes, prints the received data
/*for(int i = 0; i < 8; i++) {
printf("Bit: %d\n",bits[i]);
}*/
	
	
	
	
	
	
	
	
}



 
void node_free_string(huff_tree_node* root){
  			if(root){
    			node_free_string(root->left);
    			node_free_string(root->right);
    		}
  		
	}

int main(){
	int array[256];
	int array1[256];
	int c;
	int s = 0;
	code code1[256];
	bits_writer* bw;
	bw = newWriter();
	for(int e = 0; e < 256; e++){
		code1[e].size = 0;
		code1[e].num = 0;

	}

	huff_tree* tree = newTree();
	FILE* fp = fopen("test.txt", "r");
	FILE* ff = fopen("test.txt", "r");
	FILE* fw = fopen("test2.txt", "w");
	int charr = getc(ff);
	getfreq(fp, 256, array);
	for(int i = 0; i < 256; i++){
		if(array[i] != 0){
			s += 1;
		}
	}
	buildtree(tree, 256, array);
	for(int j = 0; j < 255; j++){
		if(array[j] != 0)
			getcodes(tree->array[0], code1, 0, j);
	}

	

	/*for(int h = 0; h< 255; h++){
		if(code1[h].num != 0){
			printf("code%d: %d size: %d\n", h, code1[h].num, code1[h].size);
		}
	}*/
	bw->size = code1[charr].size;
	bw->fp = code1[charr].num;
	charr = getc(ff);
	while(charr != EOF){
		put_bit(bw, code1[charr].num, code1[charr].size);
		charr = getc(ff);
	}
	bw->fp = bw->fp << (8 - bw->size);
	fputc(bw->fp, bw->f);
	
	fwrite(array, sizeof(int), 256, fw);
	FILE* f;
	f = fopen("test2.txt", "r");
	while(1){
		int c = fgetc(f);
		if(feof(f)){
			break;
		}
		printf("%d\n", c);
		
	
	}

	free(bw);

	for(int w = 0; w < s; w++){
			//node_free_string(
			free(tree->array[w]);
	}
	//node_free_string(tree->array[0]);
	free(tree->array);
	free(tree);

	fclose(fp);
	fclose(ff);
	

	
	
	return 0;
//look in a loop for the places that the frequencies that are not zero and create a new node from that and put it in the forrest (which is huff_tree_node* array[256])
}
