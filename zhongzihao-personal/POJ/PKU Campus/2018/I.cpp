#include<bits/stdc++.h>

const int N = 30;
const int M = 1 << 20;
const int K = 510;

int comb[N][N];
int bitcnt[M];
int ans[K][K];
int column[K];

void solve(){
	int n;
	scanf("%d", &n);
	for (int i = 0; ; ++ i){
		if (comb[i][i >> 1] >= n){
			int cnt = 0;
			for (int j = 0; cnt < n; ++ j){
				if (bitcnt[j] == i >> 1){
					column[cnt ++] = j;
				}
			}
			for (int j = 0; j < n; ++ j){
				for (int k = 0; k < n; ++ k){
					if (j == k){
						ans[j][k] = 0;
					}
					else{
						int tmp = column[k] & ~column[j];
						for (int u = 0; ; ++ u){
							if (tmp >> u & 1){
								ans[j][k] = u + 1;
								break;
							}
						}
					}
					printf("%d%c", ans[j][k], " \n"[k ==  n - 1]);
				}
			}
			return;
		}
	}
}

int main(){
	for (int i = 0; i < N; ++ i){
		comb[i][0] = 1;
		for (int j = 1; j <= i; ++ j){
			comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
		}
	}
	for (int i = 1; i < M; ++ i){
		bitcnt[i] = bitcnt[i >> 1] + (i & 1);
	}
	int test;
	scanf("%d", &test);
	while (test --){
		solve();
	}
	return 0;
}
