#include<bits/stdc++.h>

int x, a, b;

int main(){
	scanf("%d%d%d", &x, &a, &b);
	return printf(b - a <= 0 ? "delicious\n" : b - a <= x ? "safe\n" : "dangerous\n"), 0;
}
