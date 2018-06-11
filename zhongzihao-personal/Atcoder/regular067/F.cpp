#include<bits/stdc++.h>
#define ll long long

const int MAX = 14;
const int N = 5010;
const int M = 210;

std::pair <int, int> seg[1 << MAX + 1];
int mat[N][M], n, m;
ll max[N][N], dis[N];

void build(int j){
	memset(seg, 0, sizeof(seg));
	for (int i = 1 << MAX; i < (1 << MAX) + n; ++ i){
		seg[i] = {mat[i + 1 - (1 << MAX)][j], i + 1 - (1 << MAX)};
	}
	for (int i = (1 << MAX) - 1; i; -- i){
		seg[i] = std::max(seg[i << 1], seg[(i << 1) + 1]);
	}
}

std::pair <int, int> query(int left, int right){
	std::pair <int, int> ret = {0, 0};
	for (int l = (1 << MAX) + left - 1, r = (1 << MAX) + right; l < r; l >>= 1, r >>= 1){
		if (l & 1){
			ret = std::max(ret, seg[l ++]);
		}
		if (r & 1){
			ret = std::max(ret, seg[-- r]);
		}
	}
	return ret;
}

void solve(int left, int right){
	if (left > right){
		return;
	}
	std::pair <int, int> p = query(left, right);
	int x = p.first, sit = p.second;
	max[left][sit] += x;
	max[left][right + 1] -= x;
	max[sit + 1][sit] -= x;
	max[sit + 1][right + 1] += x;
	solve(left, sit - 1);
	solve(sit + 1, right);
}
	
int main(){
	scanf("%d%d", &n, &m);
	for (int i = 2; i <= n; ++ i){
		scanf("%lld", &dis[i]);
		dis[i] += dis[i - 1];
	}
	for (int i = 1; i <= n; ++ i){
		for (int j = 1; j <= m; ++ j){
			scanf("%d", &mat[i][j]);
		}	
	}
	for (int j = 1; j <= m; ++ j){
		build(j);
		solve(1, n);
	}
	for (int i = 1; i <= n; ++ i){
		for (int j = 1; j <= n; ++ j){
			max[i][j] += max[i][j - 1];
		}
	}
	for (int j = 1; j <= n; ++ j){
		for (int i = 1; i <= n; ++ i){
			max[i][j] += max[i - 1][j];
		}
	}
	ll ans = 0;
	for (int i = 1; i <= n; ++ i){
		for (int j = i; j <= n; ++ j){
			ans = std::max(ans, max[i][j] - (dis[j] - dis[i]));
		}
	}
	printf("%lld\n", ans);
	return 0;
}
