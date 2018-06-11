#include<bits/stdc++.h>

const int N = 24;
inline int lowbit(int n){return n & -n;}
typedef std::pair <int, int> pii;

struct P{
	int x, y;
	
	P (int x = 0, int y = 0) : x(x), y(y){}
	
	P operator - (const P &p)const{return P (x - p.x, y - p.y);}
	int operator % (const P &p)const{return x * p.x + y * p.y;}
	int abs2()const{return *this % *this;}
	
	void read(){
		scanf("%d%d", &x, &y);
	}
};

P p[N];
int dp[1 << N];
pii pre[1 << N];
int dis[N + 10][N + 10];

int main(){
	int n;
	P ori;
	ori.read();
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i){
		p[i].read();
	}
	for (int i = 0; i < n; ++ i){
		for (int j = 0; j < n; ++ j){
			dis[i][j] = dis[j][i] = (p[i] - p[j]).abs2();
		}
		dis[n][i] = dis[i][n] = (ori - p[i]).abs2();
	}
	memset(dp, 0x7f, sizeof(dp));
	dp[0] = 0;
	for (int i = 1; i < 1 << n; ++ i){
		for (int j = 0; j < n; ++ j){
			if (!(i >> j & 1)) continue;
			for (int k = j; k < n; ++ k){
				if (!(i >> k & 1)) continue;
				int ddis = dp[i ^ 1 << j ^ 1 << k] + dis[n][j] + dis[j][k] + dis[k][n];
				if (ddis < dp[i]){
					dp[i] = ddis;
					pre[i] = {j, k};
				}
			}
		}
	}
	int nowstate = (1 << n) - 1;
	printf("%d\n", dp[nowstate]);
	while (nowstate > 0){
		pii p = pre[nowstate];
		printf("%d %d ", 0, p.first + 1);
		nowstate ^= 1 << p.first;
		if (p.second != INT_MAX){
			printf("%d ", p.second + 1);
			nowstate ^= 1 << p.second;
		}
	}
	printf("0\n");
	return 0;
}
