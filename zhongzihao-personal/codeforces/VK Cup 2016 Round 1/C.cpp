#include<bits/stdc++.h>

const int N = 200010;
typedef long long ll;

int t[N], prefive[5][N];
ll pre[N];
int n, k, b, c;

ll calc(int begin, int end, ll goal){
	ll ret = 0;
	for (int i = 0; i < 5; ++ i){
		ret += 1ll * c * (prefive[i][end] - prefive[i][begin]) * ((goal % 5 - i + 5) % 5);
	}
	ll sum = (end - begin) * goal - (pre[end] - pre[begin]);
	for (int i = 0; i < 5; ++ i){
		sum -= (prefive[i][end] - prefive[i][begin]) * ((goal % 5 - i + 5) % 5);
	}
	ret += std::min(5 * c, b) * sum / 5;
	return ret;
}

int main(){
	scanf("%d%d%d%d", &n, &k, &b, &c);
	for (int i = 1; i <= n; ++ i){
		scanf("%d", &t[i]);
	}
	std::sort(t + 1, t + n + 1);
	for (int i = 1; i <= n; ++ i){
		pre[i] = pre[i - 1] + t[i];
		for (int j = 0; j < 5; ++ j){
			prefive[j][i] = prefive[j][i - 1] + (j == t[i] % 5);
		}
	}
	ll ans = LLONG_MAX;
	for (int i = k; i <= n; ++ i){
		for (int j = 0; j < 5; ++ j){
			ans = std::min(ans, calc(i - k, i, t[i] + j));
		}
	}
	printf("%I64d\n", ans);
	return 0;
}
