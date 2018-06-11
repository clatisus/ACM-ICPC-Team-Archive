#include<bits/stdc++.h>

int main(){
	int a, b, c;
	scanf("%d%d%d", &a, &b, &c);
	if (a < b){
		std::swap(a, b);
	}
	if (b < c){
		std::swap(b, c);
	}
	if (a < b){
		std::swap(a, b);
	}
	return printf("%d\n", b + c), 0;
}
