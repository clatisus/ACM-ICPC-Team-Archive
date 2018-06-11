#include<bits/stdc++.h>

typedef std::pair <int, int> pii;

struct state{
	int a[5];
	
	state(){memset(a, 0, sizeof(a));}
	
	state(int a0, int a1, int a2, int a3, int a4){
		a[0] = a0;
		a[1] = a1;
		a[2] = a2;
		a[3] = a3;
		a[4] = a4;
	}
	
	bool operator < (const state &s)const{
		for (int i = 0; i < 5; ++ i){
			if (a[i] != s.a[i]){
				return a[i] < s.a[i];
			}
		}
		return false;
	}
};

const int N = 510;

state s[N];
int cnt = 0;
int dis[N][N];
bool inque[N][N];
std::vector <pii> e[N][N], _e[N][N];

int main(){
	for (int i = 0; i <= 8; ++ i){
		for (int j = 0; j <= 8; ++ j){
			for (int k = 0; k <= 8; ++ k){
				for (int l = 0; l <= 8; ++ l){
					for (int m = 0; m <= 8; ++ m){
						if (i + j + k + l + m == 8){
							s[cnt ++] = state(i, j, k, l, m);
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < cnt; ++ i){
		for (int j = 0; j < cnt; ++ j){
			for (int ii = 1; ii <= 4; ++ ii){
				if (!s[i].a[ii]) continue;
				for (int jj = 1; jj <= 4; ++ jj){
					if (!s[j].a[jj]) continue;
					int x = (ii + jj) % 5;
					state newst = s[i];
					-- newst.a[ii];
					++ newst.a[x];
					int sit = std::lower_bound(s, s + cnt, newst) - s;
					e[j][sit].push_back({i, j});
					_e[i][j].push_back({j, sit});
				}
			}
		}
	}
	std::queue <pii> q;
	for (int i = 0; i < cnt; ++ i){
		int sit = std::lower_bound(s, s + cnt, state(8, 0, 0, 0, 0)) - s;
		if (i == sit) continue;
		dis[i][sit] = 1;
		q.push({i, sit});
		inque[i][sit] = true;
	}
	while (!q.empty()){
		pii u = q.front();
		inque[u.first][u.second] = false;
		q.pop();
		for (auto v : e[u.first][u.second]){
			int pre = dis[v.first][v.second];
			if (dis[u.first][u.second] == 1){
				dis[v.first][v.second] = 3;
			}
			else if (dis[u.first][u.second] == 2){
				dis[v.first][v.second] = std::max(2, dis[v.first][v.second]);
			}
			else{
				bool flag = true;
				for (auto w : _e[v.first][v.second]){
					if (dis[w.first][w.second] != 3){
						flag = false;
						break;
					}
				}
				if (flag){
					dis[v.first][v.second] = 1;
				}
			}
			if (!inque[v.first][v.second] && dis[v.first][v.second] != pre){
				q.push(v);
				inque[v.first][v.second] = true;
			}
		}
	}
	int test;
	scanf("%d", &test);
	while (test --){
		int f;
		scanf("%d", &f);
		int a[2];
		for (int i = 0; i < 2; ++ i){
			state st;
			for (int j = 0, x; j < 8; ++ j){
				scanf("%d", &x);
				++ st.a[x];
			}
			a[i] = std::lower_bound(s, s + cnt, st) - s;
		}
		if (f == 0){
			int ans = dis[a[0]][a[1]];
			puts(ans == 3 ? "Alice" : ans == 2 || ans == 0 ? "Deal" : "Bob");
		}
		else{
			int ans = dis[a[1]][a[0]];
			puts(ans == 3 ? "Bob" : ans == 2 || ans == 0 ? "Deal" : "Alice");
		}
	}
	return 0;
}
