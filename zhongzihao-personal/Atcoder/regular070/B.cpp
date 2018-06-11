#include<bits/stdc++.h>

int a, b, w;

int main(){
	scanf("%d%d%d", &w, &a, &b);
	if (a + w < b){
		return printf("%d\n", b - a - w), 0;
	}
	if (b + w < a){
		return printf("%d\n", a - b - w), 0;
	}
	return printf("0\n"), 0;
}
