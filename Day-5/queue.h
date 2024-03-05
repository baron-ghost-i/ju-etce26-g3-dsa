#include <stdio.h>
#include <stdlib.h>
#define UNDERFLOW(q) (((*(q))==NULL)?(1):(0))

typedef struct btnode{
	int data;
	struct btnode* lchild;
	struct btnode* rchild;
} btnode; //defined Binary Tree node for typecasting

typedef struct qnode{
	btnode* data;
	struct qnode* next;
} qnode;

void insert(qnode** front, qnode** rear, btnode* item){
	qnode* newRear = (qnode*) malloc(sizeof(qnode));
	newRear->next = NULL;
	newRear->data = item;
	if(*front==NULL) *front = newRear;
	else (*rear)->next = newRear;
	*rear = newRear;
}

btnode* pop(qnode** front){
	if(UNDERFLOW(front)){
		printf("\nError: Queue is already empty.\n");
		exit(1);
	}
	btnode* out = (*front)->data;
	qnode* temp = *front;
	*front = (*front)->next;
	free(temp);
	return out;
}
 /*Useful for debugging*/
void display(qnode* front){
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