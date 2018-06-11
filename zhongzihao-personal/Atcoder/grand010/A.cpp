#include<bits/stdc++.h>

int n;

int main(){
	scanf("%d", &n);
	int cnt = 0;
	for (int i = 0, x; i < n; ++ i){
		scanf("%d", &x);
		if (x & 1){
			++ cnt;
		}
	}
	return printf((cnt & 1) ? "NO\n" : "YES\n"), 0;
}
