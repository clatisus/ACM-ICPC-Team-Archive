#include<bits/stdc++.h>

const int N = 100010;

bool vis[N];
int cnt[N];

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	vis[1] = true;
	for (int i = 1; i <= n; ++ i){
		cnt[i] = 1;
	}
	for (int i = 0, x, y; i < m; ++ i){
		scanf("%d%d", &x, &y);
		if (vis[x]){
			vis[x] = cnt[x] > 1;
			vis[y] = true;
		}
		-- cnt[x];
		++ cnt[y];
	}
	int ans = 0;
	for (int i = 1; i <= n; ++ i){
		ans += vis[i];
	}
	printf("%d\n", ans);
	return 0;
}
