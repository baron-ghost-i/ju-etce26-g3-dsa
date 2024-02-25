#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE (5)
#define OVERFLOW(q) ((((q).rear)==MAXSIZE-1)?(1):(0))
#define UNDERFLOW(q) ((((q).rear)==-1)?(1):(0))

#define MENU ("1. Insert to queue\n2. Delete from queue\n3. Display queue\n4. Exit\nEnter choice: ")

typedef struct qitem{
	int priority;
	int data;
} qitem;

typedef struct PriorityQueue{
	qitem* items;
	int rear;
} PriorityQueue;

PriorityQueue newQueue(){
	PriorityQueue nQ;
	nQ.items = (qitem*) malloc(sizeof(qitem)*MAXSIZE);
	nQ.rear = -1;
	return nQ;
}

void display(PriorityQueue *q){
	if(q->rear==-1) printf("\nEmpty queue\n\n");
	else{
		printf("\nQueue: ");
		for(int i=0; i<=q->rear; i++) printf("%d ", q->items[i].data);
	printf("\n\n");
	}
}

void enqueue(PriorityQueue *q, qitem item){
	int i, cmax = 0, cmax_ind = -1;
	if(OVERFLOW(*q)){
		printf("\nError: Overflow");
		exit(1);
	}
	for(i=0; i<=q->rear; i++){
		if((q->items[i].priority >= cmax) && (q->items[i].priority <= item.priority)){
			cmax = q->items[i].priority;
			cmax_ind = i;
		}
	}
	q->rear++;
	for(i=q->rear; i>cmax_ind+1; i--) q->items[i] = q->items[i-1];
	q->items[cmax_ind+1] = item;
	display(q);
}

qitem peek(PriorityQueue *q){
	if(UNDERFLOW(*q)){
		printf("\nError: Underflow");
		exit(1);
	}
	return q->items[0];
}

qitem dequeue(PriorityQueue *q){
	int i;
	qitem out = peek(q);
	for(i=0; i<(q->rear); i++) q->items[i] = q->items[i+1];
	q->rear--;
	printf("\nRemoved %d from queue\n", out.data);
	display(q);
	return out;
}

int main(){
	int i, ch;
	qitem temp;
	PriorityQueue q = newQueue();
	while(1){
		printf(MENU);
		scanf("%d", &ch);
		switch(ch){
			case 1:
				printf("Enter (value priority): ");
				scanf("%d %d", &(temp.data), &(temp.priority));
				enqueue(&q, temp);
				break;
			case 2:
				temp = dequeue(&q);
				break;
			case 3:
				display(&q);
				break;
			default:
				printf("\nQuitting...\n");
				return 0;
		}
	}
}