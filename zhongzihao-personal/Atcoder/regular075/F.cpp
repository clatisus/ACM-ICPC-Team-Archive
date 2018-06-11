#include<bits/stdc++.h>
#define ll long long

const int N = 20;

ll ans = 0;
int d;
int a[N];
ll power[N], coe[N], suf[N];

void dfs(int dep, int sz, ll now, bool flag){
	if (dep == sz){
		if (now == d){
			ll ret = 1;
			for (int i = 0; i < sz; ++ i){
				ret *= 10 - std::abs(a[i]) - !i;
			}
			if (flag){
				ret *= 10;
			}
			ans += ret;
		}
		return;
	}
	if (std::abs(now - d) > suf[dep]){
		return;
	}
	for (int i = -9; i <= 9; ++ i){
		a[dep] = i;
		dfs(dep + 1, sz, now + coe[dep] * i, flag);
	}
}

int main(){
	power[0] = 1;
	for (int i = 1; i <= 18; ++ i){
		power[i] = power[i - 1] * 10;
	}
	scanf("%d", &d);
	for (int i = 2; i <= 18; ++ i){
		for (int j = 0; j < i >> 1; ++ j){
			coe[j] = power[i - j - 1] - power[j];
		}
		for (int j = (i >> 1) - 1; ~j; -- j){
			suf[j] = suf[j + 1] + coe[j] * 9;	
		}
		dfs(0, i >> 1, 0, i & 1);
	}
	return printf("%lld\n", ans), 0;
}
