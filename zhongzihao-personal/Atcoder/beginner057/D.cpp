#include<bits/stdc++.h>

#define ll long long

const int N = 100;

int n, a, b;
ll v[N], com[N][N];

ll comb(int n, int m){
	if (m < 0 || m > n){
		return 0;
	}
	if (m == 0 && n == 0){
		return com[0][0] = 1;
	}
	if (~com[n][m]){
		return com[n][m];
	}
	return com[n][m] = comb(n - 1, m) + comb(n - 1, m - 1);
}

int main(){
	memset(com, -1, sizeof(com));
	scanf("%d%d%d", &n, &a, &b);
	for (int i = 0; i < n; ++ i){
		scanf("%lld", &v[i]);
	}
	std::sort(v, v + n, std::greater <ll>());
	if (v[a - 1] == v[0]){
		int cnt = 0;
		for (int i = 0; i < n; ++ i){
			if (v[i] == v[0]){
				++ cnt;
			}
		}
		ll ans = 0;
		for (int i = a; i <= std::min(cnt, b); ++ i){
			ans += comb(cnt, i);
		}
		return printf("%.10lf\n%lld\n", (double) v[0], ans), 0;
	}
	int cnt1 = 0, cnt2 = 0;
	ll sum = 0;
	for (int i = 0; i < n; ++ i){
		if (v[i] > v[a - 1]){
			++ cnt1;
			sum += v[i];
		}
		else if (v[i] == v[a - 1]){
			++ cnt2;
		}
	}
	return printf("%.10lf\n%lld\n", (double) (sum + (a - cnt1) * v[a - 1]) / a, comb(cnt2, a - cnt1)), 0;
}
