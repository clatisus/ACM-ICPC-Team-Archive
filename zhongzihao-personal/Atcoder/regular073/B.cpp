#include<bits/stdc++.h>

int a, b, c;

int main(){
	scanf("%d%d%d", &a, &b, &c);
	return printf(c % std::__gcd(a, b) ? "NO\n" : "YES\n"), 0;
}
