#include<bits/stdc++.h>

const int N = 1000010;
const int M = 20;
const int moder = 1e9 + 7;

int pre[N][M];
int n;

int main(){
	for (int i = 0; i < M; ++ i){
		pre[0][i] = 1;
	}
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i){
		for (int now = 1, j = 0; j < M; now <<= 1, ++ j){
			pre[i][j] = ((now <= i ? pre[i - now][j] : 0) + (j ? pre[i][j - 1] : 0)) % moder;
		}
	}
	return printf("%d\n", pre[n][M - 1]), 0;
}
