#include<bits/stdc++.h>

const int N = 60;
typedef std::pair <int, int> pii;

std::vector <pii> e[N];
int n, m;
std::vector <pii> leaf;
int dis[N], a[N];
int sum;

void dfs(int u, int fa){
	sum += a[u];
	a[u] = 0;
	bool flag = false;
	for (auto v : e[u]){
		if (v.first == fa){
			continue;
		}
		flag = true;
		dis[v.first] = dis[u] + v.second;
		dfs(v.first, u);
	}
	if (!flag){
		leaf.push_back({dis[u], u});
	}
}

int main(){
	scanf("%d", &n);
	for (int i = 0, u, v, w; i < n - 1; ++ i){
		scanf("%d%d%d", &u, &v, &w);
		e[u].push_back({v, w});
		e[v].push_back({u, w});
	}
	int s;
	scanf("%d%d", &s, &m);
	int left = m;
	for (int i = 0, x; i < m; ++ i){
		scanf("%d", &x);
		++ a[x];
	}
	int ans = 0;
	while (left){
		memset(dis, 0, sizeof(dis));
		for (auto u : e[s]){
			leaf.clear();
			sum = 0;
			dis[u.first] = u.second;
			dfs(u.first, s);
			std::sort(leaf.begin(), leaf.end(), std::greater <pii>());
			int sz = leaf.size(), now = 0;
			while (sum){
				++ a[leaf[now].second];
				-- sum;
				now = (now + 1) % sz;
			}
		}
		int min = INT_MAX, sit;
		for (int i = 1; i <= n; ++ i){
			if (a[i]){
				if (min > dis[i]){
					min = dis[i];
					sit = i;
				}
			}
		}
		ans += dis[sit];
		s = sit;
		left -= a[sit];
		a[sit] = 0;
	}
	return printf("%d\n", ans), 0;
}
