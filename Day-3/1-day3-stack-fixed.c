#include <stdio.h>
#include <stdlib.h>

#define UNDERFLOW(s) (((s)->top)==(-1)?(1):(0))
#define OVERFLOW(s) (((s)->top)==(((s)->length)-1)?(1):(0))

//fixed memory implementation

typedef struct stack{
	int length;
	int top;
	int* items;
} stack;

stack newStack(int length){
	stack s;
	s.length = length;
	s.top = -1;
	s.items = (int*) malloc(s.length*sizeof(int));
	return s;
}

void display(stack* s){
	int i;
	if(s->top==-1) printf("\nEmpty stack.\n");
	else{
		printf("\nFrom TOP: ");
		for(i=s->top; i>=0; i--) printf("%d ", s->items[i]);
		printf("\n");
	}
}

void push(stack* s, int item){
	if(OVERFLOW(s)){
		printf("Error: Overflow\n");
		exit(1);
	}
	s->items[++(s->top)] = item;
	display(s);
}

int pop(stack* s){
	int item;
	if(UNDERFLOW(s)){
		printf("Error: Underflow\n");
		exit(1);
	}
	item = s->items[(s->top)--];
	printf("\nPopped: %d\n", item);
	display(s);
	return item;
}

int main(){
	stack S1 = newStack(10);
	push(&S1, 1);
	push(&S1, 2);
	push(&S1, 3);
	//display(&S1);
	pop(&S1);
	pop(&S1);
	pop(&S1);
	pop(&S1);
	return 0;
}
