#include <stdio.h>
#include <stdlib.h>

#define MENU ("\n1. Enter data\n2. Delete data\n3. Display BST in inorder\n4. Exit\nEnter your choice: ")

typedef struct binarytreenode{
	int data;
	struct binarytreenode* lchild;
	struct binarytreenode* rchild;
} bstnode;

void TraverseInInorder(bstnode* root){
	if(!root) return;
	TraverseInInorder(root->lchild);
	printf("%d ", root->data);
	TraverseInInorder(root->rchild);
} //inorder traversal

void inorder(bstnode* root){
	if(!root) printf("\nEmpty tree\n");
	else{
		printf("\n");
		TraverseInInorder(root);
		printf("\n");
	}
} //wrapper for inorder

bstnode* search(bstnode* root, int key){
	if(!root) return NULL;
	else if(root->data==key) return root;
	else{
		if(key<root->data) return search(root->lchild, key);
		else return search(root->rchild, key);
	}
} //search for node based on key

bstnode* parent(bstnode* root, bstnode* child){
	bstnode* p;
	if(!root || !child || root==child) return NULL;
	else if(root->lchild==child || root->rchild==child) return root;
	else{
		p = parent(root->lchild, child);
		if(!p) p = parent(root->rchild, child);
		return p;
	}
} //find paeent of node

bstnode* minVal(bstnode* root){
	if(root){
		while(root->lchild) root = root->lchild;
		return root;
	}
	else return NULL;
} //find minimum value node of a tree/subtree

bstnode* successor(bstnode* root, bstnode* pred){
	bstnode* s;
	if(!root || !pred) return NULL;
	if(pred->rchild) return minVal(pred->rchild);
	else return minVal(parent(root, pred)->rchild);
} //find inorder successor

void insert(bstnode** root, int n){
	bstnode* newNode = (bstnode*)malloc(sizeof(bstnode));
	newNode->lchild = NULL;
	newNode->rchild = NULL;
	newNode->data = n;
	if(!(*root)) *root = newNode;
	else if(n < (*root)->data){
		if((*root)->lchild == NULL) (*root)->lchild = newNode;
		else insert(&((*root)->lchild), n);
	}
	else{
		if((*root)->rchild == NULL) (*root)->rchild = newNode;
		else insert(&((*root)->rchild), n);
	}
} //insert to BST

void delete(bstnode** root, int key){
	int temp;
	bstnode *m, *p, *p2, *s;
	m = search(*root, key);
	if(m) p = parent(*root, m);
	else{
		printf("\nCould not find the node in tree.\n");
		return;
	}
	if(!p){
		free(*root);
		*root = NULL;
		return;
	}
	if(!m->lchild && !m->rchild){
		if(p->lchild==m) p->lchild=NULL;
		else p->rchild=NULL;
		free(m);
	}
	else if(!m->lchild && m->rchild){
		if(p->lchild==m) p->lchild = m->rchild;
		else p->rchild = m->rchild;
		free(m);
	}
	else if(m->lchild && !m->rchild){
		if(p->lchild==m) p->lchild = m->lchild;
		else p->rchild = m->lchild;
		free(m);
	}
	else{
		s = successor(*root, m);
		m->data = s->data;
		delete(root, temp);
	}
} //delete node from BST

int main(){
	int ch, temp;
	bstnode* root = NULL;
	while(1){
		printf(MENU);
		scanf("%d", &ch);
		switch(ch){
			case 1:
				printf("Enter data: ");
				scanf("%d", &temp);
				insert(&root, temp);
				break;
			case 2:
				printf("Enter data to be deleted: ");
				scanf("%d", &temp);
				delete(&root, temp);
				break;
			case 3:
				inorder(root);
				break;
			default:
				printf("Quitting...");
				return 0;
		}
	}
}