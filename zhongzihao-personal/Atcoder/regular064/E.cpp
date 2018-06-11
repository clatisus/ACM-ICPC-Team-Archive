#include<bits/stdc++.h>
#define ll long long
const int N = 1010;

struct edge{
	int next, to;
	double w;
};

edge e[2 * N * N];
int first[N], x[N], y[N], r[N], n, cnt = 0;
double dist[N];
bool vis[N];

ll sqr(int _x){
	return 1ll * _x * _x;
}

double dis(int x1, int y1, int x2, int y2){
	return sqrt(sqr(x1 - x2) + sqr(y1 - y2));
}

void addedge(int u, int v, double w){
	e[++ cnt] = {first[u], v, w};
	first[u] = cnt;
	e[++ cnt] = {first[v], u, w};
	first[v] = cnt;
}

std::priority_queue<std::pair <int, int>> pq;

void dijkstra(int s){
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < N; ++ i)
		dist[i] = 1e100;
	dist[s] = 0;
	pq.push({-dist[s], s});
	while (!pq.empty()){
		int i = pq.top().second;
		pq.pop();
		if (vis[i])
			continue;
		vis[i] = 1;
		for (int j = first[i]; j; j = e[j].next){
			int x = e[j].to;
			if (!vis[x] && dist[x] > dist[i] + e[j].w){
				dist[x] = dist[i] + e[j].w;
				pq.push({-dist[x], x});
			}
		}
	}
}

int main(){
	int x_s, y_s, x_t, y_t;
	scanf("%d%d%d%d", &x_s, &y_s, &x_t, &y_t);
	scanf("%d", &n);
	int s = n, t = n + 1;
	for (int i = 0; i < n; ++ i){
		scanf("%d%d%d", &x[i], &y[i], &r[i]);
	}
	addedge(s, t, dis(x_s, y_s, x_t, y_t));
	for (int i = 0; i < n; ++ i){
		addedge(s, i, std::max(0.0, dis(x_s, y_s, x[i], y[i]) - r[i]));
		addedge(t, i, std::max(0.0, dis(x_t, y_t, x[i], y[i]) - r[i]));
		for (int j = 0; j < n; ++ j){
			if (j == i)
				continue;
			addedge(i, j, std::max(0.0, dis(x[j], y[j], x[i], y[i]) - r[i] - r[j]));
		}
	}
	dijkstra(s);
	printf("%.10lf", dist[t]);
	return 0;
}
