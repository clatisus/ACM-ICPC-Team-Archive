#include<bits/stdc++.h>

const int N = 100010;

int n, m;
int cnt[N];

int main(){
	scanf("%d%d", &n, &m);
	for (int i = 0, u, v; i < m; ++ i){
		scanf("%d%d", &u, &v);
		++ cnt[u];
		++ cnt[v];
	}
	for (int i = 1; i <= n; ++ i){
		if (cnt[i] & 1){
			return printf("NO\n"), 0;
		}
	}
	return printf("YES\n"), 0;
}
