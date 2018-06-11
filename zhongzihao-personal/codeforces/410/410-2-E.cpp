#include<bits/stdc++.h>

const int N = 500010;

int a[N], ans[N];
int n;
int inv[N];

int main(){
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
	}
	int x = n;
	for (int i = 0; i < n; ++ i){
		if (!~a[i]){
			ans[i] = x --;
		}
	}
	for (int i = 0; i < n; ++ i){
		if (!ans[i]){
			inv[a[i]] = 1;
		}
	}
	x = 1;
	for (int i = 1; i <= n; ++ i){
		if (inv[i]){
			inv[i] = x ++;
		}
	}
	for (int i = 0; i < n; ++ i){
		printf("%d ", ans[i] ? ans[i] : inv[a[i]]);
	}
	return printf("\n"), 0;
}
