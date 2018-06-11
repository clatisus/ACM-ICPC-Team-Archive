#include<bits/stdc++.h>

int a, b;

int main(){
	scanf("%d%d", &a, &b);
	a = (a + 13) % 15;
	b = (b + 13) % 15;
	if (a == b){
		return printf("Draw\n"), 0;
	}
	return printf(a > b ? "Alice\n" : "Bob\n"), 0;
}
