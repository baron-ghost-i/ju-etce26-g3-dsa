#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "queue.h"

typedef int** matrix;
typedef enum color{
	BLACK = 'B', //discovered
	GRAY = 'G', //in discovery
	WHITE = 'W' //undiscovered
} color;

matrix newMatrix(int n){
	int i;
	matrix M = (matrix) malloc(sizeof(int*)*n);
	for(i=0; i<n; i++){
		M[i] = (int*) calloc(n, sizeof(int));
	}
	return M;
}

void display_matrix(matrix m, int n){
	int i, j;
	printf("\n    ");
	for(i=0; i<n; i++) printf("%d ", i);
	printf("\n\n");
	for(i=0; i<n; i++){
		printf("%d   ", i);
		for(j=0; j<n; j++)
			printf("%d ", m[i][j]);
		printf("\n");
	}
}

void child(int n){
	int i;
	printf("\nNode:\t\t");
	for(i=0; i<n; i++) printf("%d\t", i);
}

void display_dist(int* l, int n){
	printf("\nDistance:\t");
	for(int i=0; i<n; i++){
		if(l[i]==INT_MAX) printf("inf\t");
		else printf("%d\t", l[i]);
	}
}

void display_color_list(color* l, int n){
	printf("\nColor:\t\t");
	for(int i=0; i<n; i++) printf("%c\t", l[i]);
	printf("\n");
}

void parent(int* l, int n){
	int i;
	printf("\nParent:\t\t");
	for(i=0; i<n; i++) printf("%d\t", l[i]);
}

void BFS(matrix m, int n, int src){
	int i, o;

	qnode *f = NULL, *r = NULL;
	color* col = (color*) malloc(sizeof(color)*n);
	int* d = (int*) calloc(sizeof(int), n);
	int* pi = (int*) calloc(sizeof(int), n);

	for(i=0; i<n; i++){
		col[i] = WHITE;
		d[i] = INT_MAX;
		pi[i] = -1;
	}
	
	col[src] = GRAY;
	d[src] = 0;
	pi[src] = -1;
	insert(&f, &r, src);
	while(!UNDERFLOW(&f)){
		printf("\n--------------------------------------------------\n");
		display(f);
		o = pop(&f);
		for(i=0; i<n; i++){
			if(m[o][i] && col[i] == WHITE){
				insert(&f, &r, i);
				col[i] = GRAY;
				pi[i] = o;
				d[i] = d[o]+1;
			}
		}
		printf("Visited node %d\n", o);
		col[o] = BLACK;
		child(n);
		parent(pi, n);
		display_dist(d, n);
		display_color_list(col, n);
	}
}

int main(){
	int i, n, src=0, temp1=0, temp2=0, *dist;
	matrix M;
	
	printf("Enter number of nodes: ");
	scanf("%d", &n);
	M = newMatrix(n);
	
	while(temp1!=-1 && temp2 != -1){
		printf("Enter two nodes to construct an edge between. To exit, enter \"-1\" twice: ");
		scanf("%d %d", &temp1, &temp2);
		if(temp1!=temp2 && temp1<n && temp2<n && temp1>=0 && temp2>=0){
			M[temp1][temp2] = 1;
			M[temp2][temp1] = 1;
			printf("Created edge between nodes %d and %d\n", temp1, temp2);
		}
	}
	printf("Enter source node: ");
	scanf("%d", &src);
	display_matrix(M, n);
	BFS(M, n, src);
	return 0;
}