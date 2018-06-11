#include<bits/stdc++.h>

int a, b, c;

int main(){
	scanf("%d%d%d", &a, &b, &c);
	int x = 100 * a + 10 * b + c;
	return printf(x % 4 ? "NO\n" : "YES\n"), 0;
}
