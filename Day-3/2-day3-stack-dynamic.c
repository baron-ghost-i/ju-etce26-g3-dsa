#include <stdio.h>
#include <stdlib.h>

#define MENU "\nOptions\n1. Push to stack\n2. Pop from stack\n3. Quit\nEnter choice: "

typedef struct stacknode{
	int data;
	struct stacknode* prev;
	struct stacknode* next;
} stacknode;

stacknode* newStack(int data){
	stacknode* node = (stacknode*) malloc(sizeof(stacknode));
	node->data = data;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

int len(stacknode* top){
	int l = 1;
	if(top == NULL) return 0;
	while(top->next){
		l++;
		top = top->next;
	}
	return l;
}

void display(stacknode* top){
	int i;
	if(!top) printf("Empty stack");
	else{
		printf("\nFrom top: ");
		while(top){
			printf("%d ", top->data);
			top = top->prev;
		}
	}
	printf("\n");
}

void push(stacknode** TOP, int data){
	stacknode* newTop = (stacknode*) malloc(sizeof(stacknode));
	newTop->data = data;
	newTop->next = NULL;
	newTop->prev = *TOP;
	if(*TOP!=NULL) (*TOP)->next = newTop;
	*TOP = newTop;
	display(*TOP);
}

int pop(stacknode** TOP){
	int data;
	stacknode *temp = *TOP;
	if(*TOP==NULL){
		printf("Error: Underflow");
		exit(1);
	}
	data = (*TOP)->data;
	if((*TOP)->prev!=NULL)	(*TOP)->prev->next = NULL;
	*TOP = (*TOP)->prev;
	free(temp);
	printf("\nPopped: %d\n", data);
	display(*TOP);
	return data;
}

int main(){
	int ch, item;
	stacknode* S = NULL;
	while(1){
		printf(MENU);
		scanf("%d", &ch);
		switch(ch){
			case 1:
				printf("Enter value to be pushed: ");
				scanf("%d", &item);
				push(&S, item);
				break;
			case 2:
				item = pop(&S);
				//printf("Popped value %d from stack", item);
				break;
			default:
				printf("Quitting...");
				return 0;
		}
	}
}