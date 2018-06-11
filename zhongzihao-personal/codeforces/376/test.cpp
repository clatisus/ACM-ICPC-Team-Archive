
 #include <bits/stdc++.h>
#define ll long long

#define debug(x) cout << #x << " = " << x << endl

using namespace std;

const int MAX = 3e5 + 5;
const int INF = 1 << 30;
ll arr[3][MAX];
int prv[3][MAX], dp[MAX];
int n;
map<std::pair <int, int>, int> memo;

int roll(int x, int y) {
	if(x == -1 || y == -1) {
		return -INF;
	}
	else if(x == y) {
		return dp[x];
	}
	else if(memo.count({x, y})) {
		return memo[{x, y}];
	}
	int &ans = memo[{x, y}];
	ans = dp[min(x, y)];
	if(x > y) {
		ans = max(ans, roll(prv[0][x], y) + 1);
	}
	else {
		ans = max(ans, roll(x, prv[1][y]) + 1);
	}
	return ans;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < 2; ++ i){
		for (int j = 1; j <= n; ++ j){
			scanf("%I64d", &arr[i][j]);
		}
	}
	for (int i = 1; i <= n; ++ i){
		arr[2][i] = arr[0][i] + arr[1][i];
	}

	memset(prv, -1, sizeof prv);
	map<ll, int> idx;
	for (int i = 0; i < 3; ++ i){
		idx[0] = 0;
		ll sum = 0;
		for (int j = 1; j <= n; ++ j){
			sum += arr[i][j];
			if(idx.count(sum)) {
				prv[i][j] = idx[sum];
			}
			idx[sum] = j;
		}
		for (int j = 1; j <= n; ++ j){
			prv[i][j] = max(prv[i][j], prv[i][j - 1]);
		}
		idx.clear();
	}

	for (int i = 1; i <= n; ++ i){
		dp[i] = dp[i - 1];
		if(prv[2][i] != -1) {
			dp[i] = max(dp[i], dp[prv[2][i]] + 1);
		}
		dp[i] = max(dp[i], roll(prv[0][i], i) + 1);
		dp[i] = max(dp[i], roll(i, prv[1][i]) + 1);
	}

	printf("%d\n", dp[n]);

	return 0;
}
