#include <stdio.h>
#include <stdlib.h>

#define MAXQ (10)
#define MENU ("\n1. Insert to queue\n2. Delete from queue\n3. Display queue\n4. Exit\nEnter choice: ")

typedef struct queue{
	int front;
	int rear;
	int* items;
} queue;

queue newQueue(){
	queue q;
	q.front = -1;
	q.rear = -1;
	q.items = (int*) malloc(sizeof(int)*MAXQ);
	return q;
}

int OVERFLOW(queue* q){
	if((q->front==0 && q->rear==MAXQ-1) || (q->front-q->rear==1)) return 1;
	return 0;
}

int UNDERFLOW(queue* q){
	if(q->rear==-1 && q->front==-1) return 1;
	return 0;
}

void insert(queue* q, int item){
	if(OVERFLOW(q)){
		printf("\nError: Overflow");
		exit(1);
	}
	q->items[(++q->rear)%MAXQ] = item;
	if(q->front == -1) q->front = 0;
}

int del(queue* q){
	int i, out;
	if(UNDERFLOW(q)){
		printf("\nError: Underflow");
		exit(1);
	}
	out = q->items[q->front];
	if(q->front==q->rear){
		q->front = -1;
		q->rear = -1;
	}
	else q->front = (q->front+1)%MAXQ;
	return out;
}

void display(queue q){
	int i, f = q.front, r = q.rear;
	if(UNDERFLOW(&q)) printf("\nEmpty queue");
	else{
		printf("\nItems: ");
		if(r<f) r = r + MAXQ;
		for(i=f; i<=r; i++) printf("%d ", q.items[i%MAXQ]);
	}
	printf("\n");
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
				printf("\nRemoved %d from queue\n", temp);
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