#include <stdio.h>
#include <stdlib.h>
#define MID(x) ((x)%2?(((x)+1)/2):((x)/2))
#define MENU_BASE ("\n1. Sort Array\n2. Search in Array\n3. Display Array\n4. New Array\n5. Quit\nEnter choice: ")
#define MENU_SORT ("\n1. Bubble Sort\n2. Insertion Sort\n3. Selection Sort\nEnter choice: ")
#define MENU_SEARCH ("\n1. Linear Search\n2. Binary Search\nEnter choice: ")

// all searches return indexes within list
// all sorting functions perform sort in-place

void bubble(int* arr, int len){
	int i, j, temp, count1=0, count2=0;
	for(i=0; i<len; i++){
		for(j=0; j<len-i-1; j++){
			count2++;
			if(arr[j]>arr[j+1]){
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
				count1++;
			}
		}
	}
	printf("\nBubble Sort: Performed %d swaps and %d comparisons.\n", count1, count2);
}

void insertion(int* arr, int len){
	int i, j, key, temp, count1=0, count2=0;
	for(i=0; i<len; i++){
		key = arr[i];
		j = i-1;
		while(j>=0 && arr[j]>arr[j+1]){
			temp = arr[j];
			arr[j] = arr[j+1];
			arr[j+1] = temp;
			count1++;
			count2++;
			j--;
		}
	}
	printf("\nInsertion Sort: Performed %d swaps and %d comparisons.\n", count1, count2);
}

void selection(int* arr, int len){
	int i, j, temp, minInd, count1=0, count2=0;
	for(i=0; i<len; i++){
		minInd=i;
		for(j=i+1; j<len; j++){
			if(arr[j]<arr[minInd]) minInd = j;
			count2++;
		}
		if(minInd==i) continue;
		temp = arr[minInd];
		arr[minInd] = arr[i];
		arr[i] = temp;
		count1++;
	}
	printf("\nSelection Sort: Performed %d swaps and %d comparisons.\n", count1, count2);
}

int linear(int* arr, int len, int item){
	int i, count=0, out=-1;
	for(i=0; i<len; i++){
		count++;
		if(arr[i]==item){
			out = i;
			break;
		}
	}
	if(out!=-1)	printf("\nLinear Search: Performed %d comparisons, found item at index %d\n", count, out);
	else printf("\nLinear Search: Performed %d comparisons, item not found.\n", count);
	return out;
}

int binary(int* arr, int len, int item){
	int mid, start=0, stop=len-1, out=-1, count=0;
	while(start<=stop){
		count++;
		mid = (start+stop)/2;
		if(arr[mid] == item){
			out = mid;
			break;
		}
		else if(item < arr[mid]) stop = mid-1;
		else start = mid+1;
	}
	if(out!=-1)	printf("\nBinary Search: Performed %d comparisons, found item at index %d\n", count, out);
	else printf("\nBinary Search: Performed %d comparisons, item not found.\n", count);
	return out;
}

void printArray(int* arr, int len){
	int i;
	printf("\nArray: ");
	for(i=0; i<len; ++i) printf("%d ", arr[i]);
	printf("\n");
}

int main(){
	int i, n, l, b, ch1, ch2, item;
	int* arr = NULL;
	printf("Enter length of array: ");
	scanf("%d", &n);
	arr = (int*) malloc(sizeof(int)*n);
	printf("Enter elements in array, separated by whitespace: ");
	for(i=0; i<n; i++) scanf("%d", arr+i);
	for(;;){
		printf(MENU_BASE);
		scanf("%d", &ch1);
		switch(ch1){
			case 1:
				printf(MENU_SORT);
				scanf("%d", &ch2);
				switch(ch2){
					case 1:
						bubble(arr, n);
						break;
					case 2:
						insertion(arr, n);
						break;
					case 3:
						selection(arr, n);
						break;
					default:
						printf("\nUnrecognized option, try again.\n");
				}
				break;
				
			case 2:
				printf(MENU_SEARCH);
				scanf("%d", &ch2);
				if(ch2!=1 && ch2!=2){
					printf("Unrecognized option, try again.\n");
					break;
				}
				printf("\nEnter value to search for: ");
				scanf("%d", &item);
				switch(ch2){
					case 1:
						linear(arr, n, item);
						break;
					case 2:
						binary(arr, n, item);
						break;
				}
				break;		
			
			case 3:
				printArray(arr, n);
				break;
				
			case 4:
				printf("\nEnter new array size: ");
				scanf("%d", &n);
				realloc(arr, n*sizeof(int));
				printf("Enter array items separated by whitespace: ");
				for(i=0;i<n;i++) scanf("%d", arr+i);
				break;				
			
			default:
				printf("\nQuitting...\n");
				return 0;
		}
	}
}