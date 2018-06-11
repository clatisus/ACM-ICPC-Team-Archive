#include<stdio.h>

int main(){
	int i;
	char a[] = {0};
	scanf("%s", a);
	printf("a[1] is %c \n a[2] is %c\n", a[1], a[2]);
	for (i = 0; i < 3; ++ i){
		printf("%c", a[i]);
	}
	printf("a[1] is %c \n a[2] is %c\n", a[1], a[2]);
	return 0;
}
