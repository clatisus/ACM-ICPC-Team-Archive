#include<bits/stdc++.h>

int main(){
	int n, a, b;
	scanf("%d%d%d", &n, &a, &b);
	puts(a + b & 1 ? "Borys" : "Alice");
	return 0;
}
