#include<bits/stdc++.h>

const int N = 60;
typedef long long ll;
const int INF = 0x7f7f7f7f;

bool vis[N][N];
int a[N], b[N];
int dp[N][N];

int main(){
	memset(dp, 0x7f, sizeof(dp));
	for (int i = 0; i < N; ++ i){
		for (int j = 0; j < i; ++ j){
			for (int k = j + 1; k <= i; ++ k){
				if (dp[i % k][j] != INF){
					dp[i][j] = k;
					break;
				}
			}
		}
		dp[i][i] = 0;
	}
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
		vis[i][a[i]] = true;
	}
	for (int i = 0; i < n; ++ i){
		scanf("%d", &b[i]);
	}
	std::vector <int> vec;
	while (true){
		int max = 0;
		for (int i = 0; i < n; ++ i){
			if (!vec.empty()){
				int x = vec[vec.size() - 1];
				for (int j = a[i]; j >= x; -- j){
					if (vis[i][j]){
						vis[i][j % x] = true;
					}
				}
			}
			int min = INF;
			for (int j = 0; j <= a[i]; ++ j){
				if (vis[i][j]){
					min = std::min(min, dp[j][b[i]]);
				}
			}
			max = std::max(max, min);
		}
		if (max == INF){
			puts("-1");
			return 0;
		}
		if (!max){
			break;
		}
		vec.push_back(max);
	}
	ll ans = 0;
	for (auto u : vec){
		ans |= 1ll << u;
	}
	printf("%lld\n", ans);
	return 0;
}
