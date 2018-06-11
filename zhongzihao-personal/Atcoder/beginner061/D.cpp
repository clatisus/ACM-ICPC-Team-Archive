#include<bits/stdc++.h>
#define ll long long

const int N = 10010;

int n, m;
std::vector <std::pair <int, ll>> e[N];
ll dis[N] = {};
int cnt[N] = {};
bool inque[N] = {};

void spfa(int s){
	std::queue <int> q;
	for(int i = 1; i <= n; ++ i) dis[i] = LLONG_MAX;
	dis[s] = 0;
	q.push(s);
	inque[s] = true;
	cnt[s] = 1;
	while (!q.empty()){
		int u = q.front();
		q.pop();
		inque[u] = false;
		for (auto v : e[u]){
			if (dis[v.first] > dis[u] + v.second){
				dis[v.first] = dis[u] + v.second;
				if (!inque[v.first]){
					++ cnt[v.first];
					if (cnt[v.first] > 2 * n){
						return;
					}
					q.push(v.first);
					inque[v.first] = true;
				}
			}
		}
	}
}

int main(){
	scanf("%d%d", &n, &m);
	for (int i = 0, u, v; i < m; ++ i){
		ll c;
		scanf("%d%d%lld", &u, &v, &c);
		e[u].push_back({v, -c});
	}
	spfa(1);
	if (dis[n] == LLONG_MAX){
		assert(0 == 1);
	}
	if (cnt[n] > n){
		return printf("inf\n"), 0;
	}
	return printf("%lld\n", -dis[n]), 0;
}
