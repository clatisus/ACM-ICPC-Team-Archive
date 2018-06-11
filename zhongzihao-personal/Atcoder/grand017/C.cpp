#include<bits/stdc++.h>

const int N = 200010;

int left[N], a[N];
int vis[N];
int n, m;

int main(){
	scanf("%d%d", &n, &m);
	for (int i = 0; i < N; ++ i){
		left[i] = i;
	}
	for (int i = 1; i <= n; ++ i){
		scanf("%d", &a[i]);
		-- left[a[i]];
	}
	for (int i = 0; i < N; ++ i){
		for (int j = std::max(left[i] + 1, 1); j <= i; ++ j){
			++ vis[j];
		}
	}
	int cnt = 0;
	for (int i = 1; i <= n; ++ i){
		cnt += vis[i] ? 1 : 0;
	}
	while (m --){
		int x, y;
		scanf("%d%d", &x, &y);
		++ left[a[x]];
		if (left[a[x]] > 0){
			cnt -= vis[left[a[x]]] ? 1 : 0;
			-- vis[left[a[x]]];
			cnt += vis[left[a[x]]] ? 1 : 0;
		}
		a[x] = y;
		-- left[y];
		if (left[y] >= 0){
			cnt -= vis[left[y] + 1] ? 1 : 0;
			++ vis[left[y] + 1];
			cnt += vis[left[y] + 1] ? 1 : 0;
		}
		printf("%d\n", n - cnt);
	}
	return 0;
}
