#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
//including dynamic queue using queue.h which also stores definition for btnode

#define MENU "\n1. Insert data\n2. Delete data\n3. Show tree in inorder\n4. Exit\nEnter choice: "

btnode* newNode(int data){
	btnode* n = (btnode*) malloc(sizeof(btnode));
	n->lchild = NULL;
	n->rchild = NULL;
	n->data = data;
	return n;
} //create new tree node

btnode* parent(btnode* root, btnode* child){
	btnode* p;
	if(!child) return NULL;
	if(!root) return NULL;
	else if(root->data == child->data) return NULL;
	else if(root->lchild==NULL && root->rchild==NULL) return NULL;
	else if((child == root->lchild) || (child == root->rchild)) return root;
	else{
		p = parent(root->lchild, child);
		if(!p) p = parent(root->rchild, child);
		return p;
	}
} //finds parent of a node

btnode* match(btnode* root, int key){
	btnode* out;
	if(!root){
		return NULL;
	}
	else if(root->data == key){
		return root;
	}
	else if(root->lchild == NULL && root->rchild==NULL){
		return NULL;
	}
	else{
		out = match(root->lchild, key);
		if(!out) out = match(root->rchild, key);
		return out;
	}
}

int DeleteDeepest(btnode** root){
	int out;
	btnode *temp, *p;
	qnode *f = NULL, *r = NULL;
	insert(&f, &r, *root);
	while(!UNDERFLOW(&f)){
		temp = pop(&f);
		if(temp->lchild) insert(&f, &r, temp->lchild);
		if(temp->rchild) insert(&f, &r, temp->rchild);
	}
	out = temp->data;
	p = parent(*root, temp);
	if(p->lchild->data==out) p->lchild=NULL;
	else p->rchild=NULL;
	free(temp);
	return out;
}
 
int TraverseInorder(btnode* root){
	if(root){
		TraverseInorder(root->lchild);
		printf("%d ", root->data);
		TraverseInorder(root->rchild);
	}
}

void inorder(btnode* root){
	if(root){
		printf("\nTraversed in inorder: ");
		TraverseInorder(root);
		printf("\n");
	}
	else printf("\nEmpty tree\n");
} //wrapper function for inorder traversal

void LevelOrderInsert(btnode** root, int data){
	btnode* temp;
	qnode *f = NULL, *r = NULL;
	if(!(*root)){
		*root = newNode(data);
		return;
	}
	insert(&f, &r, *root);
	while(!UNDERFLOW(&f)){
		temp = pop(&f);
		if(temp->lchild == NULL){
			temp->lchild = newNode(data);
			return;
		}
		else insert(&f, &r, temp->lchild);
		if(temp->rchild == NULL){
			temp->rchild = newNode(data);
			return;
		}
		else insert(&f, &r, temp->rchild);
	}
}

void del(btnode** root, int key){
	int temp;
	btnode* m = match(*root, key);
	btnode* p = parent(*root, m);
	if(!m){
		printf("\nData not found in tree\n");
		return;
	}
	if(m->lchild==NULL && m->rchild==NULL){
		if(!p){
			printf("\nDeleted tree\n");
			exit(0);
		}
		if(p->lchild == m) p->lchild=NULL;	
		else p->rchild=NULL;
		free(m);
	}
	else if(m->lchild==NULL && m->rchild!=NULL){
		p = parent(*root, m);
		if(!p){
			*root = (*root)->rchild;
			return;
		}
		if(p->lchild == m) p->lchild = m->rchild;
		else p->rchild = m->rchild;
		free(m);
	}
	else if(m->lchild!=NULL && m->rchild==NULL){
		if(!p){
			*root = (*root)->lchild;
			return;
		}
		p = parent(*root, m);
		if(p->lchild == m) p->lchild = m->lchild;
		else p->rchild = m->lchild;
		free(m);
	}
	else{
		temp = DeleteDeepest(root);
		m->data = temp;
	}
	printf("Deleted node successfully\n");
}

int main(){
	btnode* root = NULL;
	int ch, temp;
	for(;;){
		printf(MENU);
		scanf("%d", &ch);
		switch(ch){
			case 1:
				printf("Enter data: ");
				scanf("%d", &temp);
				LevelOrderInsert(&root, temp);
				break;
			case 2:
				printf("Enter data in node to be deleted: ");
				scanf("%d", &temp);
				del(&root, temp);
				break;
			case 3:
				inorder(root);
				break;	
			default:
				printf("Quitting...\n");
				return 0;
		}
	}
}