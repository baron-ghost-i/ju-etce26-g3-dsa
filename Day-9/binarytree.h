#include <stdio.h>
#include <stdlib.h>
#include "treequeue.h"
//including dynamic queue using treequeue.h which also stores definition for btnode

btnode* newNode(int data){
	btnode* n = (btnode*) malloc(sizeof(btnode));
	n->lchild = NULL;
	n->rchild = NULL;
	n->data = data;
	return n;
} //create new tree node
 
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
	tqnode *f = NULL, *r = NULL;
	if(!(*root)){
		*root = newNode(data);
		return;
	}
	tinsert(&f, &r, *root);
	while(!UNDERFLOW(&f)){
		temp = tpop(&f);
		if(temp->lchild == NULL){
			temp->lchild = newNode(data);
			return;
		}
		else tinsert(&f, &r, temp->lchild);
		if(temp->rchild == NULL){
			temp->rchild = newNode(data);
			return;
		}
		else tinsert(&f, &r, temp->rchild);
	}
}