#include <stdio.h>
#include <stdlib.h>

#define MENU ("\nOPTIONS\n1. Enter value\n2. Enter operator\n3. Show current stack\n4. Terminate.\nEnter (Choice, Input): ")

typedef struct PFStack{
	float item;
	struct PFStack* below;
	struct PFStack* above;
} PFS;

PFS* newStack(float data){
	PFS* ns = (PFS*) malloc(sizeof(PFS));
	ns->above = NULL;
	ns->below = NULL;
	ns->item = data;
	return ns;
}

void display(PFS* pf){
	printf("\n");
	if(!pf) printf("Empty stack\n");
	else{
		while(pf->below) pf = pf->below; //traverse to bottom of stack
		while(pf){
			printf("%f ", pf->item);
			pf= pf->above;
		} //print from bottom of stack
		printf("\n");
	}
}

void push(PFS** stack, float data){
	PFS* top = (PFS*) malloc(sizeof(PFS));
	top->above = NULL;
	top->below = *stack;
	top->item = data;
	if(*stack!=NULL) (*stack)->above = top;
	*stack = top;
}

float pop(PFS** top){
	float data;
	PFS* temp = *top;
	if(temp==NULL) exit(1); //should not arise under normal operation
	data = (*top)->item;
	if((*top)->below!=NULL)	(*top)->below->above = NULL;
	*top = (*top)->below;
	free(temp);
	return data;
}

void clear(PFS** stack){
	PFS* temp = *stack;
	while(temp){
		pop(stack);
		temp = *stack;
	}
}

void operate(PFS** stack, char op, int* STAT){
	float temp1, temp2;
	if(*stack==NULL){
		printf("Error: postfix notation cannot start without a value\n");
		*STAT = 1;
		return;
	}
	if((((*stack)->below)==NULL)&&(op!='$')){
		printf("Error: cannot use operator on single value\n");	
		*STAT = 1;
		return;
	}
	if(op=='+') push(stack, pop(stack)+pop(stack));
	else if(op=='-'){
		temp1 = pop(stack);
		temp2 = pop(stack);
		push(stack, temp2-temp1);
	}
	else if(op=='*') push(stack, pop(stack)*pop(stack));
	else if(op=='/'){
		temp1 = pop(stack);
		temp2 = pop(stack);
		if(temp1==0){
			printf("Error: cannot divide by 0\n");
			push(stack, temp2);
			push(stack, temp1);
			*STAT = 1;
			return;
		}
		push(stack, temp2/temp1);
	}
	else if(op=='$'){
		printf("\nResult: %f\nSTACK RESET\n", pop(stack));
		clear(stack);
	}
	else{
		printf("Error: unknown operator\n");
		*STAT = 1;
		return;
	}
}

int main(){
	int choice=0, STAT=0;
	float val;
	char op;
	PFS* pf = NULL;
	while(1){ //menu
		printf(MENU);
		scanf("%d", &choice);
		switch(choice){
			case 1:
				choice=0;
				//printf("Enter value: ");
				scanf("%f", &val);
				push(&pf, val);
				break;			
			case 2:
				choice=0;
				//printf("Enter operator: ");
				getchar(); //reject CRLF from ENTER key
				op = getchar();
				operate(&pf, op, &STAT); //STAT allows for handling errors
				if(STAT){
					STAT=0;
					continue;
				}
				break;
			case 3:
				display(pf);
				break;
			default:
				printf("Terminating...");
				return 0;
		}
	}
}