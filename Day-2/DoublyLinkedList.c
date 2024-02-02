#include <stdio.h>
#include <stdlib.h>

#define MENU "\n1. Insert\n2. Delete\n3. Display\n4. Display reversed list\n5. Exit\nEnter choice: "

typedef struct dnode{
	int data;
	struct dnode* prev;
	struct dnode* next;
} dnode;

dnode* getnode(int data){
	dnode* node = (dnode*) malloc(sizeof(dnode));
	node->data = data;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

int len(dnode* head){
	int l = 1;
	if(head == NULL) return 0;
	while(head->next){
		l++;
		head = head->next;
	}
	return l;
}

void append(dnode* head, int data){
	dnode* end = (dnode*) malloc(sizeof(dnode));
	while(head->next) head = head->next;
	end->data = data;
	end->prev = head;
	end->next = NULL;
	head->next = end;
}

void push(dnode** head, int data){
	dnode *newHead = (dnode*) malloc(sizeof(dnode)), *curr = *head;
	newHead->data= data;
	newHead->prev = NULL;
	newHead->next = *head;
	curr->prev = newHead;
	*head = newHead;
}

void insert(dnode* head, int index, int data){
	int i = 0, l = len(head);
	dnode *n = (dnode*) malloc(sizeof(dnode));
	for(i=0; i<index-1; i++) head = head->next;
	n->data = data;
	n->prev = head;
	n->next = head->next;
	head->next->prev = n;
	head->next = n;
}

void display(dnode* head){
	int l = len(head);
	if(!l) printf("List: []\n");
	else if(l==1) printf("List: [%d]\n", head->data);
	else{
		printf("List: [%d, ", head->data);
		while(head->next->next){
			printf("%d, ", head->next->data);
			head = head->next;
		}
		printf("%d]\n", head->next->data);
	}
}
 //display reversed list
void display_reverse(dnode* head){
	int l = len(head);
	if(!l) printf("Reversed List: []\n");
	else if(l==1) printf("Reversed List: [%d]\n", head->data);
	else{
		while(head->next) head = head->next;
		printf("Reversed List: [%d, ", head->data);
		while(head->prev->prev){
			printf("%d, ", head->prev->data);
			head = head->prev;
		}
		printf("%d]\n", head->prev->data);
	}
}

int del(dnode** head, int index, int* STAT){
	int i = 0, out, l = len(*head);
	dnode *curr = *head;
	if(index<0 || index>l-1){
		*STAT = 1;
		printf("Error: index out of range\n");
		return -1;
	}
	for(i=0; i<index; i++) curr = curr->next;
	out = curr->data;
	if(l==1){
		free(curr);
		*head=NULL;
		return out;
	}
	if(!index){
		curr = curr->next;
		free(curr->prev);
		curr->prev = NULL;
		*head = curr;
	}
	else if(curr->next == NULL){
		curr->prev->next = NULL;
		free(curr);
	}
	else{
		curr->next->prev = curr->prev;
		curr->prev->next = curr->next;
		free(curr);
	}
	return out;
}

int main(){
	int STATUS = 0; //useful if delete is called on an inexistent node
	dnode *list = NULL;
	int i, temp, ch, index, dat, l;
	printf("Enter initial length of list: ");
	scanf("%d", &l);
	printf("Enter elements, separated by whitespace: ");
	for(i=0; i<l; i++){
		scanf("%d", &dat);
		if(!i)
			list = getnode(dat);
		else
			append(list, dat);
	}
	display(list);
	//menu
	while(1){
		l = len(list);
		printf(MENU);
		scanf("%d", &ch);
		switch(ch){
			case 1:
				if(l){
					printf("Enter index at which data will be inserted: ");
					scanf("%d", &index);
				}
				printf("Enter value: ");
				scanf("%d", &dat);
				if(!l){
					list = getnode(dat);
					break;
				}
				if(index<=0) push(&list, dat);
				else if(index > 0 && index < l) insert(list, index, dat);
				else append(list, dat);
				break;
			
			case 2:
				printf("Enter index to delete: ");
				scanf("%d", &index);
				temp = del(&list, index, &STATUS);
				if(STATUS){
					STATUS = 0;
					continue;
				} //this block checks if an erroneous delete is attempted, and skips over the error
				printf("Removed value %d from list", temp);
				break;
			
			case 3:
				display(list);
				break;
			
			case 4:
				display_reverse(list);
				break;
			
			default:
				printf("\nQuitting...\n");
				return 0;
		}
	}
}