#include <stdio.h>
#include <stdlib.h>

#define MENU "\n1. Insert\n2. Delete\n3. Display\n4. Exit\nEnter choice: "

typedef struct node{
	int data;
	struct node* next;
} node;

int len(node* tail){
	node *temp = tail;
	int l=0;
	if(tail==NULL) return 0;
	do{
		tail = tail->next;
		l++;
	}while(temp!=tail);
	return l;
}

//Initialize new node
node* getnode(int data){
	node* tail = (node*) malloc(sizeof(node));
	tail->data = data;
	tail->next = tail;
	return tail;
}

//insert into list
void insert(node** tail, int index, int data){
	node *curr = *tail, *prev = NULL, *newNode = (node*) malloc(sizeof(node));
	newNode->data = data;
	int i, l = len(*tail);
	
	if(!l){
		*tail = getnode(data);
		return;
	}
	
	if(index>=l-1){
		newNode->next = (*tail)->next;
		(*tail)->next = newNode;
		*tail = newNode;
	}
	else if(index<=0){
		newNode->next = (*tail)->next;
		(*tail)->next = newNode;
	}
	else{
		prev = curr;
		curr = curr->next;
		for(i=0;i<index;i++){
			prev = curr;
			curr = curr->next;
		}
		prev->next = newNode;
		newNode->next = curr;
	}
}

//delete node from list
int del(node** tail, int index, int* STAT){
	node *prev = NULL, *temp = *tail;
	int i, item, l = len(*tail);
	
	if(index<0 || index >l-1){
		*STAT = 1;
		printf("Error: index out of range\n");
		return -1;
	}
	
	if(index==l-1){
		do{
			prev = temp;
			temp = temp->next;
		}while(temp != (*tail));
		
		prev->next = temp->next;
		item = temp->data;
		*tail = prev;
		free(temp);
	}
	else{
		prev=temp;
		temp = temp->next;
		for(i=0;i<index;i++){
			prev = temp;
			temp = temp->next;
		}
		prev->next = temp->next;
		item = temp->data;
		free(temp);
	}
	
	if(l==1) (*tail) = NULL;
	
	return item;
}

void display(node* tail){
	int i, l = len(tail);
	node* temp = tail;
	if(!l){
		printf("List: []\n");
	}
	else if(l==1){
		printf("List: [%d]\n", tail->data);
	}
	else{
		tail = tail->next;
		printf("List: [%d, ", tail->data);
		while(tail->next != temp){
			printf("%d, ", tail->next->data);
			tail = tail->next;
		}
		printf("%d]\n", tail->next->data);
	}
}

int main(){
	int STATUS = 0; //useful if delete is called on an inexistent node
	node *list = NULL;
	int i, temp, ch, index, dat, l;
	printf("Enter initial length of list: ");
	scanf("%d", &l);
	printf("Enter elements, separated by whitespace: ");
	for(i=0; i<l; i++){
		scanf("%d", &dat);
		if(!i)
			list = getnode(dat);
		else
			insert(&list, i, dat);
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
				if(index<=0)
					insert(&list, 0, dat);
				else if(index > 0 && index < l)
					insert(&list, index, dat);
				else
					insert(&list, l-1, dat);
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
			
			default:
				printf("\nQuitting...\n");
				exit(0);
		}
	}		
	return 0;
}
