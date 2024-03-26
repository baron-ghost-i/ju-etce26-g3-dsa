#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef qnode queue;

int** newAdj(int n){
	int i;
	int** m = (int**) malloc(n*sizeof(int*));
	for(i=0; i<n; i++)
		m[i] = (int*) calloc(n, sizeof(int));
	return m;
}

void display_matrix(int** m, int n){
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

void create_edge(int** m, int a, int b){
	m[a][b] = 1;
	m[b][a] = 1;
}

void BFS(int** m, int size, int src){
	int i, o, *visited = (int*) calloc(size, sizeof(int));
	qnode *f = NULL, *r = NULL;
	insert(&f, &r, src);
	visited[src] = 1;
	while(!UNDERFLOW(&f)){
		display(f);
		o = pop(&f);
		printf("Visited node %d\n", o);
		for(i=0; i<size; i++){
			if(m[o][i] && !visited[i]){
				insert(&f, &r, i);
				visited[i] = 1;
			}
			else continue;
		}
	}
	printf("\n");
}

int main(){
	int size = 8;
	int** m = newAdj(size);
	create_edge(m, 0, 1);
	create_edge(m, 0, 3);
	create_edge(m, 1, 2);
	create_edge(m, 3, 4);
	create_edge(m, 3, 5);
	create_edge(m, 4, 6);
	create_edge(m, 5, 6);
	create_edge(m, 5, 7);
	create_edge(m, 6, 7);
	BFS(m, size, 0);
	display_matrix(m, size);
	return 0;
}