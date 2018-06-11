#include<bits/stdc++.h>

const int N = 60;
const int M = N * N * N;
typedef long long ll;

std::vector <int> e[N];
ll w[N], v[N], c[N];
ll dp[2][M];
ll first[N], second[N];
int m[N];

struct frac{
	ll x, y;
	ll num;
	
	frac (ll x = 0, ll y = 0, ll num = 0):x(x), y(y), num(num){}
	
	bool operator < (const frac &f)const{
		return x * f.y > y * f.x;
	}
};

frac f[N];

void dfs(int u){
	w[u] = m[u];
	v[u] = 1;
	for (auto v : e[u]){
		dfs(v);
		w[u] += w[v];
		::v[u] += ::v[v];
	}
}

int main(){
	int n, x, d;
	scanf("%d%d%d", &n, &x, &d);
	for (int i = 1, x; i <= n; ++ i){
		scanf("%d", &m[i]);
		if (i >= 2){
			scanf("%d", &x);
			e[x].push_back(i);
		}
	}
	dfs(1);
	for (int i = 1; i <= n; ++ i){
		c[i] = i == 1 ? x / w[i] : std::min((ll) d, x / w[i]);
		//c[i] = std::min((ll) d, x / w[i]);
		first[i] = std::min(c[i], 50ll);
		second[i] = c[i] - first[i];
	}
	memset(dp, -1, sizeof(dp));
	int now = 0;
	dp[now][0] = 0;
	for (int i = 1; i <= n; ++ i){
		for (int j = 0; j < v[i]; ++ j){
			std::deque <ll> queue;
			for (int k = j; k < M; k += v[i]){
				if (dp[now][k] != -1){
					ll pushvalue = dp[now][k] - (k / v[i]) * w[i];
					while (!queue.empty() && pushvalue < queue.back()){
						queue.pop_back();
					}
					queue.push_back(pushvalue);
				}
				if (!queue.empty()){
					dp[now ^ 1][k] = queue.front() + (k / v[i]) * w[i];
				}
				else{
					dp[now ^ 1][k] = -1;
				}
				int delsit = k - first[i] * v[i];
				if (delsit >= 0 && dp[now][delsit] != -1){
					ll delvalue = dp[now][delsit] - (k / v[i] - first[i]) * w[i];
					if (delvalue == queue.front()){
						queue.pop_front();
					}
				}
			}
		}
		now ^= 1;
	}
	for (int i = 1; i <= n; ++ i){
		f[i] = frac (v[i], w[i], second[i]);
	}
	std::sort(f + 1, f + n + 1);
	ll ans = 0;
	for (int i = 0; i < M; ++ i){
		if (dp[now][i] != -1 && dp[now][i] <= x){
			int y = x - dp[now][i], sum = 0;
			for (int j = 1; j <= n; ++ j){
				int num = std::min(f[j].num, y / f[j].y);
				y -= num * f[j].y;
				sum += num * f[j].x;
			}
			ans = std::max(ans, (ll) i + sum);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
