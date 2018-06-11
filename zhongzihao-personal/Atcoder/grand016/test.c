#include<stdio.h>

int main(){
	void func(int **p);
	int a[4][5];
	func(a);
	return 0;
}

void func(int **p){
	printf("FUCK!\n");
}
