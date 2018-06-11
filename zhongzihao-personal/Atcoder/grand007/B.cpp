#include<bits/stdc++.h>

const int N = 20010;

int a[N], b[N];

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 1, x; i <= n; ++ i){
		scanf("%d", &x);
		a[x] = i;
		b[i] = 2 * n * (n + 1 - i);
	}
	for (int i = 1; i <= n; ++ i){
		a[i] -= b[i];
	}
	for (int i = n; i >= 1; -- i){
		a[i] -= a[1] - 1;
	}
	for (int i = 1; i <= n; ++ i){
		printf("%d%c", a[i], " \n"[i == n]);
	}
	for (int i = 1; i <= n; ++ i){
		printf("%d%c", b[i], " \n"[i == n]);
	}
	return 0;
}
