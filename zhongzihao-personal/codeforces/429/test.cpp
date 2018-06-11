#include<stdio.h>
#include<stdlib.h>

int main(){
	int *p = (int *)malloc(sizeof(int));
	printf("%d\n", *p);
	return 0; 
}
