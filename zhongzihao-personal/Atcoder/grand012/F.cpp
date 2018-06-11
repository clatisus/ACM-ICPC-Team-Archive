#include<bits/stdc++.h>

const int N = 110;
const int moder = 1e9 + 7;

int dp[N][N][N], a[N];
int n;

int main(){
	scanf("%d", &n);
	for (int i = 1; i < n << 1; ++ i){
		scanf("%d", &a[i]);
	}
	std::sort(a + 1, a + (n << 1));
	dp[n][1][1] = 1;
	for (int i = n; i; -- i){
		bool flag1 = a[i - 1] == a[i], flag2 = a[2 * n - i + 1] == a[2 * n - i];
		for (int j = 0; j < N; ++ j){
			for (int k = 1; k <= j; ++ k){
				if (flag1 && flag2){
					int &x = dp[i - 1][j][k];
					x = (dp[i][j][k] + x) % moder;
					for (int kk = 1; kk < k; ++ kk){
						int &x = dp[i - 1][j - (k - kk - 1)][kk];
						x = (x + dp[i][j][k]) % moder;
					}
					for (int kk = k + 1; kk <= j; ++ kk){
						int &x = dp[i - 1][j - (kk - k - 1)][k + 1];
						x = (x + dp[i][j][k]) % moder;
					}
				}
				else if (flag1){
					int &x = dp[i - 1][j + 1][k];
					x = (dp[i][j][k] + x) % moder;
					for (int kk = 1; kk < k; ++ kk){
						int &x = dp[i - 1][j - (k - kk - 1) + 1][kk];
						x = (x + dp[i][j][k]) % moder;
					}
					for (int kk = k + 1; kk <= j + 1; ++ kk){
						int &x = dp[i - 1][j - (kk - k - 1) + 1][k + 1];
						x = (x + dp[i][j][k]) % moder;
					}
				}
				else if (flag2){
					int &x = dp[i - 1][j + 1][k + 1];
					x = (dp[i][j][k] + x) % moder;
					for (int kk = 0; kk < k; ++ kk){
						int &x = dp[i - 1][j - (k - kk - 1) + 1][kk + 1];
						x = (x + dp[i][j][k]) % moder;
					}
					for (int kk = k + 1; kk <= j; ++ kk){
						int &x = dp[i - 1][j - (kk - k - 1) + 1][k + 2];
						x = (x + dp[i][j][k]) % moder;
					}
				}
				else{
					int &x = dp[i - 1][j + 2][k + 1];
					x = (dp[i][j][k] + x) % moder;
					for (int kk = 0; kk < k; ++ kk){
						int &x = dp[i - 1][j - (k - kk - 1) + 2][kk + 1];
						x = (x + dp[i][j][k]) % moder;
					}
					for (int kk = k + 1; kk <= j + 1; ++ kk){
						int &x = dp[i - 1][j - (kk - k - 1) + 2][k + 2];
						x = (x + dp[i][j][k]) % moder;
					}
				}
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < N; ++ i){
		for (int j = 0; j < N; ++ j){
			ans = (ans + dp[1][i][j]) % moder;
		}
	}
	return printf("%d\n", ans), 0;
}
