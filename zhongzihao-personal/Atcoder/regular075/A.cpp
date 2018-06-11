#include<bits/stdc++.h>

int main(){
	int a, b;
	scanf("%d%d", &a, &b);
	if (a + b >= 10){
		return printf("error\n"), 0;
	}
	printf("%d\n", a + b);
	return 0;
}
