#include <stdio.h>
#include <stdlib.h>

#define MAXQ (10)
#define OVERFLOW(q) ((((q)->rear)==MAXQ-1)?1:0)
#define UNDERFLOW(q) ((((q)->rear)==-1)?1:0)
#define MENU ("1. Insert to queue\n2. Delete from queue\n3. Display queue\n4. Exit\nEnter choice: ")

typedef struct queue{
	int rear;
	int* items;
} queue;

queue newQueue(){
	queue q;
	q.rear = -1;
	q.items = (int*) malloc(sizeof(int)*MAXQ);
	return q;
}

void insert(queue* q, int item){
	if(OVERFLOW(q)){
		printf("\nError: Overflow\n");
		exit(1);
	}
	q->items[++(q->rear)] = item;
}

int del(queue* q){
	int i, out;
	if(UNDERFLOW(q)){
		printf("\nError: Underflow\n");
		exit(1);
	}
	out = q->items[0];
	q->rear -= 1;
	for(i=0; i<=(q->rear); i++) q->items[i] = q->items[i+1];
	return out;
}

void display(queue q){
	int i;
	if(q.rear == -1) printf("\nEmpty queue\n");
	else{
		printf("\nItems: ");
		for(i=0; i<=q.rear; i++) printf("%d ", q.items[i]);
		printf("\n\n");
	}
}

int main(){
	int i, ch, temp;
	queue q = newQueue();
	while(1){
		printf(MENU);
		scanf("%d", &ch);
		switch(ch){
			case 1:
				printf("Enter input: ");
				scanf("%d", &temp);
				insert(&q, temp);
				break;
			case 2:
				temp = del(&q);
				printf("\nRemoved %d from queue\n\n", temp);
				break;
			case 3:
				display(q);
				break;
			default:
				printf("\nQuitting...\n");
				return 0;
		}
	}
}