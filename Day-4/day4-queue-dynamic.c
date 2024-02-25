#include <stdio.h>
#include <stdlib.h>

#define MENU ("\n1. Insert to queue\n2. Delete from queue\n3. Display queue\n4. Exit\nEnter choice: ")
#define UNDERFLOW(q) ((*(q))==NULL?1:0)

typedef struct qnode{
	int data;
	struct qnode* next;
} qnode;

void insert(qnode** front, qnode** rear, int item){
	qnode* newRear = (qnode*) malloc(sizeof(qnode));
	newRear->next = NULL;
	newRear->data = item;
	if(*rear==NULL){
		*front = newRear;
		*rear = newRear;
	}
	else (*rear)->next = newRear;
	*rear = newRear;
}

int del(qnode** front){
	if(UNDERFLOW(front)){
		printf("\nError: Queue is already empty.\n");
		exit(1);
	}
	int out = (*front)->data;
	qnode* temp = *front;
	*front = (*front)->next;
	free(temp);
	return out;
}

void display(qnode* front){
	if(front==NULL){
		printf("\nEmpty queue\n");
		return;
	}
	printf("\nItems: ");
	while(front!=NULL){
		printf("%d ", front->data);
		front = front->next;
	}
	printf("\n");
}

int main(){
	int i, ch, temp;
	qnode *front = NULL;
	qnode *rear = front;
	while(1){
		printf(MENU);
		scanf("%d", &ch);
		switch(ch){
			case 1:
				printf("Enter input: ");
				scanf("%d", &temp);
				insert(&front, &rear, temp);
				break;
			case 2:
				temp = del(&front);
				printf("\nRemoved %d from queue\n", temp);
				break;
			case 3:
				display(front);
				break;
			default:
				printf("\nQuitting...\n");
				return 0;
		}
	}
}