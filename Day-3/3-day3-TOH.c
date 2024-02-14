#include <stdio.h>
#include <stdlib.h>

/*
underlying structure
UNDERFLOW and OVERFLOW have been neglected since the solution to TOH has been designed such that those cases do not occur
*/

typedef struct stack{
	int MAX;
	int top;
	int* items;
	char* name; //to store the name of the stack, which gets printed
} stack;

stack newStack(int length, char* name){
	stack s;
	s.MAX = length;
	s.top = -1;
	s.items = (int*) malloc(s.MAX*sizeof(int));
	s.name = name;
	return s;
}

void display(stack* s){
	int i;
	printf("%s: ", s->name);
	for(i=s->top; i>=0; i--) printf("%d ", s->items[i]);
	printf("\n");
}

void push(stack* s, int item){
	s->items[++(s->top)] = item;
}

int pop(stack* s){
	return s->items[(s->top)--];
}
/*End of underlying structure*/

//Tower of Hanoi - Recursive solution using stacks
void TOH(int n, stack* src, stack* dest, stack* aux, int* moves){
	int disc;
	if(n==1){
		disc = pop(src);
		printf("%d. Moved disc %d from %s to %s\n", ++(*moves), n, src->name, dest->name);
		push(dest, disc);
	}
	else{
		TOH(n-1, src, aux, dest, moves);
		disc = pop(src);
		printf("%d. Moved disc %d from %s to %s\n", ++(*moves), n, src->name, dest->name);
		push(dest, disc);
		TOH(n-1, aux, dest, src, moves);
	}
}

int main(){
	int i, N_DISCS, moves=0;
	char *SRC = "src", *DEST = "dest", *AUX = "aux";
	stack src, dest, aux;
	printf("Enter number of discs: ");
	scanf("%d", &N_DISCS);
	if(N_DISCS==0){
		printf("Number of discs cannot be zero\n");
		exit(1);
	}
	src = newStack(N_DISCS, "src");
	dest = newStack(N_DISCS, "dest");
	aux = newStack(N_DISCS, "aux");
	for(i=N_DISCS; i>0; i--) push(&src, i); //initialize source
	printf("\nInitial state:\n");                                                                    
	display(&src);                                             
	display(&aux);
	display(&dest);
	printf("\n");
	TOH(N_DISCS, &src, &dest, &aux, &moves);
	printf("\nAfter solving:\n");
	display(&src);           
	display(&aux);
	display(&dest);
	printf("\nSolved in %d moves\n", moves);
	return 0;
}