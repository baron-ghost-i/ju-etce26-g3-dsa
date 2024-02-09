#include <stdio.h>
#include <stdlib.h>

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
	if(top == NULL){
		printf("Empty stack\n");
		return;
	}
	printf("\nFrom top: ");
	if(top && !top->prev) printf("%d", top->data);
	else{
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
	(*TOP)->next = newTop;
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
	if((*TOP)->prev){
		*TOP = (*TOP)->prev;
		(*TOP)->next = NULL;
	}
	else *TOP = NULL;
	free(temp);
	printf("\nPopped: %d\n", data);
	display(*TOP);
	return data;
}

int main(){
	stacknode* s = newStack(0);
	display(s);
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);
	pop(&s);
	pop(&s);
	pop(&s);
	pop(&s);
	return 0;
}
