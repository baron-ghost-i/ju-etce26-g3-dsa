#include <stdio.h>
#include <stdlib.h>

#define MENU "\n1. Insert\n2. Delete\n3. Display\n4. Exit\nEnter choice: "

//linked list node; using typedef to avoid typing "struct" repeatedly
typedef struct node{
	int data;
	struct node* next;
} node;

//Initialize new node
node* getnode(int data){
	node* head = (node*) malloc(sizeof(node));
	head->data = data;
	head->next = NULL;
	return head;
}

//Determine length of list
int len(node* list){
	int l=1;
	if(list==NULL)
		return 0;
	while(list->next){
		list = list->next;
		++l;
	}
	return l;
}

//insert at front of list
void push(node** head, int data){
	node *n= (node*) malloc(sizeof(node));
	n->data=data;
	n->next=*head;
	*head=n;
}

//insert at end of list
void append(node *q, int data){
	node *n = (node*) malloc(sizeof(node));
	while(q->next)
		q = q->next;
	n->data = data;
	q->next = n;
	n->next=NULL;
}

//insert anywhere within list
void insert(node* list, int index, int data){
	int i;
	node* n = (node*) malloc(sizeof(node));
	for(i=0;i<index-1;i++)
		list = list->next;
	n->data = data;
	n->next = list->next;
	list->next = n;
}

//delete node from list
int delete(node** head, int index, int* STAT){
	node *prev = NULL, *temp = *head;
	int i, item, l = len(*head);
	
	if(index<0 || index>l-1){
		*STAT = 1;
		printf("Error: index out of range\n");
		return -1;
	}
	
	if(index==0){
		*head = (*head)->next;
		item = temp->data;
		free(temp);
	}
	else{
		for(i=0;i<index;i++){
			prev = temp;
			temp = temp->next;
		}
		prev->next = temp->next;
		item = temp->data;
		free(temp);
	}
	
	if(l==0) *head = NULL;
	
	return item;
}

void display(node* list){
	int l = len(list);
	if(l==0) printf("\nList: []\n");
	else if(l==1){
		printf("\nList: [%d]\n", list->data);
	}
	else{
		printf("\nList: [%d, ", list->data);
		while(list->next->next){
			printf("%d, ", list->next->data);
			list = list->next;
		}
		printf("%d]\n", list->next->data);
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
				if(index<=0)
					push(&list, dat);
				else if(index > 0 && index < l)
					insert(list, index, dat);
				else
					append(list, dat);
				break;
			
			case 2:
				printf("Enter index to delete: ");
				scanf("%d", &index);
				temp = delete(&list, index, &STATUS);
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
