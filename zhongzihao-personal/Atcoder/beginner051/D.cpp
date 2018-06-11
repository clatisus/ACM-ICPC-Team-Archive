#include<bits/stdc++.h>

const int N = 110;

struct edge{
	int next, to, w;
};

edge e[N * N];
bool mat[N][N];
int e_cnt = 1, n, m, first[N];

void addedge(int u, int v, int w){
	e[++ e_cnt] = {first[u], v, w};
	first[u] = e_cnt;
	e[++ e_cnt] = {first[v], u, w};
	first[v] = e_cnt;
}

std::vector <int> pre[N];
std::queue <int> q;
bool inque[N];
int dis[N];

void spfa(int s){
	for (int i = 0; i < n; ++ i){
		pre[i].clear();
	}
	memset(dis, 0xf, sizeof(dis));
	q.push(s);
	inque[s] = true;
	dis[s] = 0;
	while (!q.empty()){
		int i = q.front();
		q.pop();
		inque[i] = false;
		for (int j = first[i]; j; j = e[j].next){
			int x = e[j].to;
			if (dis[x] > dis[i] + e[j].w){
				pre[x] = {i};
				dis[x] = dis[i] + e[j].w;
				q.push(x);
				inque[x] = true;
			}
			else if (dis[x] == dis[i] + e[j].w){
				pre[x].push_back(i);
			}
		}
	}
}

int main(){
	scanf("%d%d", &n, &m);
	for (int i = 0, u, v, w; i < m; ++ i){
		scanf("%d%d%d", &u, &v, &w);
		addedge(u - 1, v - 1, w);
		mat[u - 1][v - 1] = mat[v - 1][u - 1] = 1;
	}
	for (int i = 0; i < n; ++ i){
		spfa(i);
		for (int j = 0; j < n; ++ j){
			if (j == i){
				continue;
			}
			for (int k = 0; k < pre[j].size(); ++ k){
				int x = pre[j][k];
				mat[x][j] = mat[j][x] = 0;
			}
		}
	}
	int cnt = 0;
	for (int i = 0; i < n; ++ i){
		for (int j = 0; j < n; ++ j){
			cnt += mat[i][j];
		}
	}
	return printf("%d\n", cnt >> 1), 0;
}
