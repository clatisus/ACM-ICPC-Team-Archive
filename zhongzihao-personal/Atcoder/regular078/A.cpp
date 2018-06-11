#include<bits/stdc++.h>

int main(){
	int a, b;
	scanf("%d%d", &a, &b);
	return printf(a % 3 == b % 3 && a % 3 ? "Impossible\n" : "Possible\n"), 0;
}
