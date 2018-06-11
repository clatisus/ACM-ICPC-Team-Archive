#include<bits/stdc++.h>

int a, b, c;

int main(){
	scanf("%d%d%d", &a, &b, &c);
	return printf(b - a == c - b ? "YES\n" : "NO\n"), 0;
}
