#include<bits/stdc++.h>

const int N = 100010;

double f[N], g[N], v[N], r[N], a[N], b[N];

void solve(){
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i){
		scanf("%lf", &v[i]);
	}
	for (int i = 0; i <= n; ++ i){
		f[i] = 0;
	}
	for (int i = 1; i <= n - 1; ++ i){
		scanf("%lf", &r[i]);
	}
	f[0] = 1;
	g[1] = 1.0 / n;
	for (int i = 1; i <= n; ++ i){
		for (int j = 1; j < i; ++ j){
			f[i] += g[j] * (1 - r[i - j]) / v[j] / (n - j);
		}
		f[i] *= v[i];
		if (i < n){
			g[i + 1] = g[i] + f[i] / (n - i);
		}
	}
	printf("%.10lf\n", f[n] + g[n] - 1);
}

int main(){
	freopen("data.txt", "r", stdin);
	int test;
	scanf("%d", &test);
	while (test --){
		solve();
	}
	return 0;
}
