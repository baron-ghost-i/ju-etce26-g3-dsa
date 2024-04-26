#include <stdio.h>
#include <stdlib.h>
#define tUNDERFLOW(q) (((*(q))==NULL)?(1):(0))

typedef struct btnode{
	int data;
	struct btnode* lchild;
	struct btnode* rchild;
} btnode; //defined Binary Tree node for typecasting

typedef struct tqnode{
	btnode* data;
	struct tqnode* next;
} tqnode;

void tinsert(tqnode** front, tqnode** rear, btnode* item){
	tqnode* newRear = (tqnode*) malloc(sizeof(tqnode));
	newRear->next = NULL;
	newRear->data = item;
	if(*front==NULL) *front = newRear;
	else (*rear)->next = newRear;
	*rear = newRear;
}

btnode* tpop(tqnode** front){
	if(tUNDERFLOW(front)){
		printf("\nError: Queue is already empty.\n");
		exit(1);
	}
	btnode* out = (*front)->data;
	tqnode* temp = *front;
	*front = (*front)->next;
	free(temp);
	return out;
}
 /*Useful for debugging*/
void tdisplay(tqnode* front){
	if(front==NULL){
		printf("\nEmpty queue\n");
		return;
	}
	printf("\nItems: ");
	while(front!=NULL){
		printf("%d ", front->data->data);
		front = front->next;
	}
	printf("\n");
}