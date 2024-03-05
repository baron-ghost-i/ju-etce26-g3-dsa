#include "queue.h"

int main(){
	qnode *f = NULL, *r = NULL;
	insert(&f, &r, 10);
	insert(&f, &r, 20);
	insert(&f, &r, 30);
	insert(&f, &r, 40);
	display(f);
	return 0;
}