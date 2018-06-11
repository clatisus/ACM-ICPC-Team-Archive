#include<bits/stdc++.h>

const int N = 1010;
const int INF = 0x7f7f7f7f;

char s[N][N];
int dis[N][N];
int h, w, k;
std::queue <std::pair <int, int>> q;

bool check(int x, int y){
	return x >= 0 && x < h && y >= 0 && y < w && s[x][y] != '#';
}

void bfs(std::pair <int, int> p){
	dis[p.first][p.second] = 0;
	q.push(p);
	while (!q.empty()){
		std::pair <int, int> pair = q.front();
		q.pop();
		int x = dis[pair.first][pair.second];
		if (x == k){
			return;
		}
		if (check(pair.first + 1, pair.second) && dis[pair.first + 1][pair.second] == INF){
			dis[pair.first + 1][pair.second] = x + 1;
			q.push({pair.first + 1, pair.second});
		}
		if (check(pair.first - 1, pair.second) && dis[pair.first - 1][pair.second] == INF){
			dis[pair.first - 1][pair.second] = x + 1;
			q.push({pair.first - 1, pair.second});
		}
		if (check(pair.first, pair.second + 1) && dis[pair.first][pair.second + 1] == INF){
			dis[pair.first][pair.second + 1] = x + 1;
			q.push({pair.first, pair.second + 1});
		}
		if (check(pair.first, pair.second - 1) && dis[pair.first][pair.second - 1] == INF){
			dis[pair.first][pair.second - 1] = x + 1;
			q.push({pair.first, pair.second - 1});
		}
	}
}

int main(){
	scanf("%d%d%d", &h, &w, &k);
	for (int i = 0; i < h; ++ i){
		scanf("%s", s[i]);
	}
	std::pair <int, int> now;
	for (int i = 0; i < h; ++ i){
		for (int j = 0; j < w; ++ j){
			if (s[i][j] == 'S'){
				now = {i, j};
			}
		}
	}
	memset(dis, 0x7f, sizeof(dis));
	bfs(now);
	int ans = INF;
	for (int i = 0; i < h; ++ i){
		for (int j = 0; j < w; ++ j){
			if (dis[i][j] != INF){
				ans = std::min(ans, 1 + (std::min(std::min(i, j), std::min(h - i - 1, w - j - 1)) + k - 1) / k);
			}
		}
	}
	return printf("%d\n", ans), 0;
}
