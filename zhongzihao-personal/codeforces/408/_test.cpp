#include<bits/stdc++.h>

const int N = 300010;
const int INF = 1e9;

struct edge{
	int next, to, exi;
};

int n, k, d, e_cnt = 1, min, sit;
int exi[N], first[N], min1[N], min2[N], sit1[N], sit2[N], fa[N];
edge e[N << 1];

void addedge(int u, int v){
	e[++ e_cnt] = {first[u], v, 1};
	first[u] = e_cnt;
	e[++ e_cnt] = {first[v], u, 1};
	first[v] = e_cnt;
}

void renew(int sit, int value, int newsit){
	if (value <= min1[sit]){
		min2[sit] = min1[sit];
		sit2[sit] = sit1[sit];
		min1[sit] = value;
		sit1[sit] = newsit;
	}
	else if (value < min2[sit]){
		min2[sit] = value;
		sit2[sit] = newsit;
	}
}

void dfs(int u, int pa){
	min1[u] = min2[u] = INF;
	if (exi[u]){
		renew(u, 0, u);
	}
	for (int i = first[u]; i; i = e[i].next){
		int v = e[i].to;
		if (v == pa || !e[i].exi){
			continue;
		}
		fa[v] = u;
		dfs(v, u);
		renew(u, min1[v], sit1[v]);
		renew(u, min2[v], sit2[v]);
	}
	int x = min1[u] + min2[u];
	if (min > x){
		min = x;
		sit = u;
	}
}

std::vector <int> vec1, vec2;

void solve(int s){
	min = INT_MAX;
	dfs(s, 0);
	if (min >= INF){
		return;
	}
	int u = sit1[sit], v = sit2[sit];
	vec1.clear();
	while (u != sit){
		vec1.push_back(u);
		u = fa[u];
	}
	vec1.push_back(sit);
	vec2.clear();
	while (v != sit){
		vec2.push_back(v);
		v = fa[v];
	}
	for (int i = (int) vec2.size() - 1; i >= 0; -- i){
		vec1.push_back(vec2[i]);
	}
	u = vec1[(int) vec1.size() >> 1], v = vec1[((int) vec1.size() >> 1) - 1];
	for (int i = first[u]; i; i = e[i].next){
		if (e[i].to == v){
			e[i].exi = false;
			e[i ^ 1].exi = false;
			solve(u);
			solve(v);
			break;
		}
	}
}

int main(){
	freopen("data.txt", "r", stdin);
	freopen("_D.txt", "w", stdout);
	scanf("%d%d%d", &n, &k, &d);
	for (int i = 0, x; i < k; ++ i){
		scanf("%d", &x);
		exi[x] = true;
	}
	int cnt = 0;
	for (int i = 1; i <= n; ++ i){
		if (exi[i]){
			++ cnt;
		}
	}
	for (int i = 1, u, v; i < n; ++ i){
		scanf("%d%d", &u, &v);
		addedge(u, v);
	}
	solve(1);
	printf("%d\n", cnt - 1);
	for (int i = 2; i < n << 1; i += 2){
		if (!e[i].exi){
			printf("%d ", i >> 1);
		}
	}
	return printf("\n"), 0;
}
