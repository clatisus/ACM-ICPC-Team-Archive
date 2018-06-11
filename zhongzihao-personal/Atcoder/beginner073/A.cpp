#include<bits/stdc++.h>

int main(){
	int n;
	scanf("%d", &n);
	return printf(n % 10 == 9 || n / 10 == 9 ? "Yes\n" : "No\n"), 0;
}
