#include<bits/stdc++.h>

int main(){
	int a, b;
	scanf("%d%d", &a, &b);
	if (a <= 0 && 0 <= b){
		puts("Zero");
		return 0;
	}
	if (a > 0){
		puts("Positive");
		return 0;
	}
	puts(b - a & 1 ? "Positive" : "Negative");
	return 0;
}
