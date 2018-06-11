#include<bits/stdc++.h>
#define ll long long

const int N = 1010;
const int M = 10;
const int K = 110;

ll n, m, kk;
char s[N][M], orz[K][N][M];

int main(){
	freopen("data.txt", "r", stdin);
	freopen("__orz.txt", "w", stdout);
	scanf("%I64d%I64d%I64d", &n, &m, &kk);
	for (int i = 0; i < n; ++ i){
		scanf("%s", s[i]);
	}
	for (int i = 0; i < kk; ++ i){
		memcpy(orz[i], s, N * M * sizeof(char));
	}
	for (int i = 0, a, b, c, d; i < kk; ++ i){
		scanf("%d%d%d%d", &a, &b, &c, &d);
		char ch = (getchar(), getchar());
		for (int j = a - 1; j < c; ++ j){
			for (int k = b - 1; k < d; ++ k){
				orz[i][j][k] = ch;
			}
		}
	}
	ll min = LLONG_MAX;
	for (int i = 0; i < kk; ++ i){
		ll ans = 0;
		for (int j = 0; j < kk; ++ j){
			for (int ii = 0; ii < n; ++ ii){
				for (int jj = 0; jj < m; ++ jj){
					ans += std::abs(orz[i][ii][jj] - orz[j][ii][jj]);
				}
			}
		}
		min = std::min(ans, min);
	}
	printf("%I64d\n", min);
	return 0;
}
