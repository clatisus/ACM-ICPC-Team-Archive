#include<bits/stdc++.h>

const int N = 100010;

std::vector <int> e[N];
int dis[N << 1];
bool inque[N << 1];

void bfs(int s){
	
}

int main(){
	int n, m;
	scanf("%d", &n);
	for (int i = 1, c; i <= n; ++ i){
		scanf("%d", &c);
		for (int j = 0, x; j < c; ++ j){
			scanf("%d", &x);
			e[i].push_back(x);
		}
	}
	int s;
	scanf("%d", &s);
	spfa(s << 1);
}
