#include<stdio.h>

void output(int n){
	if (n == 0){
		printf("end\n");
		return;
	}
	printf("%d\n", n);
	output(n - 1);
}

int main(){
	int n;
	scanf("%d", &n);
	output(n);
	return 0;
}
