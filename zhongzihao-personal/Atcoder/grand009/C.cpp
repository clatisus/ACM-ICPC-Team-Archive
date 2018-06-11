#include<bits/stdc++.h>
#define ll long long

const int N = 100010;
const int moder = 1e9 + 7;

ll dp[2][N], pre[2][N], a[N], n, A, B;
std::map <ll, ll> Hash;

int main(){
	scanf("%lld%lld%lld", &n, &A, &B);
	for (int i = 1; i <= n; ++ i){
		scanf("%lld", &a[i]);
		Hash[- a[i]] = i;
	}
	dp[0][0] = dp[1][0] = pre[0][0] = pre[1][0] = 1;
	int now1 = 0, now2 = 0;
	for (int i = 2; i <= n; ++ i){
		auto u = Hash.lower_bound(B - a[i]);
		int sit = u == Hash.end() ? 0 : u -> second;
		if (sit == i - 1){
			-- sit;
		}
		dp[1][i - 1] = pre[0][sit];
		u = Hash.lower_bound(A - a[i]);
		sit = u == Hash.end() ? 0 : u -> second;
		if (sit == i - 1){
			-- sit;
		}
		dp[0][i - 1] = pre[1][sit];
		if (a[i] - a[i - 1] < A){
			for (int j = now1; j < i - 1; ++ j){
				dp[0][j] = pre[0][j] = 0;
			}
			now1 = i - 1;
		}
		if (a[i] - a[i - 1] < B){
			for (int j = now2; j < i - 1; ++ j){
				dp[1][j] = pre[1][j] = 0;
			}
			now2 = i - 1;
		}
		pre[1][i - 1] = (pre[1][i - 2] + dp[1][i - 1]) % moder;
		pre[0][i - 1] = (pre[0][i - 2] + dp[0][i - 1]) % moder;
	}
	ll ans = 0;
	for (int i = 0; i < n; ++ i){
		ans = (ans + dp[0][i] + dp[1][i]) % moder;
	}
	printf("%lld", ans);
	return 0;
}
