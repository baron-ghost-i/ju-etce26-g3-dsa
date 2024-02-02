#include <stdio.h>
#include <stdlib.h>

#define MAX(x,y) (((x)>(y))?(x):(y))
#define MENU "\n1. Append to function\n2. Add functions\n3. Display function\n4. Exit\nEnter your choice: "

typedef struct polynode{
	float coeff;
	int exp;
	struct polynode* link;
} polynode;

polynode* getnode(float coeff, int exp){
	polynode* h = (polynode*) malloc(sizeof(polynode));
	h->coeff = coeff;
	h->exp = exp;
	h->link = NULL;
	return h;
}

polynode* newfunc(float coeff){
	return getnode(coeff, 0);
}

int maxp(polynode* func){
	if(func == NULL) return -1;
	while(func->link){
		func = func->link;
	}
	//printf("\nMAXP: %d\n", func->exp);
	return func->exp;
}

//also implementing logic for changing coefficient
void append(polynode* func, float coeff, int exp){
	int i, mp = maxp(func);
	polynode *n = getnode(coeff, exp), *temp = NULL;
	n->coeff = coeff;
	n->exp = exp;
	if(exp>mp){
		while(func->link) func = func->link;
		i = func->exp;
		while(i<exp-1){		
			temp = getnode(0.0, i+1);
			func->link = temp;
			func = temp;
			i++;
		}
		func->link = n;
	}
	else{
		while(func->exp < exp) func = func->link;
		func->coeff = coeff;
	}
}

polynode* add(polynode* f, polynode* g){
	int i, mf = maxp(f), mg = maxp(g), max = MAX(mf, mg);
	polynode *h = getnode(0, 0);
	if(mf > mg) append(g, 0, max);
	else if(mg > mf) append(f, 0, max);
	for(i=0; i<=max; i++){
		append(h, (f->coeff)+(g->coeff), i);
		f = f->link;
		g = g->link;
	}
	return h;
}

void display(polynode* h){
	int mp = maxp(h);
	if(mp==-1) printf("0\n");
	else if(mp==0) printf("%.2f\n", h->coeff);
	else if(mp==1) printf("%.2f + %.2fx\n", h->coeff, h->link->coeff);
	else{
		printf("%.2f ", h->coeff);
		while(h->link->link){
			h = h->link;
			if(h->exp == 1) printf("+ %.2fx ", h->coeff, h->exp);
			else printf("+ %.2fx^%d ", h->coeff, h->exp);
		}
		printf("+ %.2fx^%d\n", h->link->coeff, h->link->exp);
	}
}

int main(){
	polynode *f = NULL, *g = NULL, *h = NULL;
	int i, ch, temp_exp = 0;
	char fch = 'e';
	float temp_coeff = 0;
	//taking f(x) from user
	printf("Enter maximum power of f(x): ");
	scanf("%d", &temp_exp);
	for(i = 0; i<=temp_exp; i++){
		printf("Enter coefficient of x^%d: ", i);
		scanf("%f", &temp_coeff);
		if(!i) f = getnode(temp_coeff, 0);
		else append(f, temp_coeff, i);
	}
	printf("f(x) = ");
	display(f);
	//taking g(x) from user
	printf("Enter maximum power of g(x): ");
	scanf("%d", &temp_exp);
	for(i = 0; i<=temp_exp; i++){  
		printf("Enter coefficient of x^%d: ", i);
		scanf("%f", &temp_coeff);
		if(!i) g = getnode(temp_coeff, 0);
		else append(g, temp_coeff, i);
	}
	printf("g(x) = ");
	display(g);
	for(;;){
		printf(MENU);
		scanf("%d", &ch);
		switch(ch){
			case 1:
				while(1){
					printf("Enter function: ");
					getchar(); //to get rid of any previous char input arising due to ENTER key
					fch = getchar();
					if(fch!='f' && fch != 'g') printf("Invalid choice of function, try again.\n");
					else{
						printf("Enter power of x: ");
						scanf("%d", &temp_exp);
						printf("Enter coefficient: ");
						scanf("%f", &temp_coeff);
						if(fch=='f') append(f, temp_coeff, temp_exp);
						else append(g, temp_exp, temp_coeff);
						fch = 'e';
						break;
					}
				}
				break;
			case 2:
				h = add(f, g);
				printf("h(x) = f(x) + g(x) = ");
				display(h);
				break;
			case 3:
				while(fch!='f' && fch!='g' && fch!='h'){
					printf("Enter function: ");
					getchar();
					fch = getchar();
					if(fch == 'f' || fch == 'g' || fch=='h') printf("%c(x) = ", fch);
					if(fch == 'f') display(f);
					else if(fch == 'g') display(g);
					else if(fch=='h') display(h);
					else{
						printf("Invalid function chosen, try again\n");
						continue;
					}
					fch = 'e';
					break;
				}
				break;
			default:
				printf("Quitting...");
				return 0;
		}
	}
}