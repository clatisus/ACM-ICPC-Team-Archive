#include<bits/stdc++.h>
#define ll long long
#define lowbit(x) ((x) & (-x))

const int N = 1000000;
const int M = 6;
const int K = 10;
const int moder = 1e9 + 7;

int cnt[N], f[N];
std::pair <int, int> orz[1 << M];
ll g[N];
int c[3][K + 1][K + 1][K + 1][K + 1][K + 1];

void add(int _x1, int _x2, int _x3, int _x4, int _x5, int value, int times){
	int x1 = 10 - _x1;
	while (x1 <= K){
		int x2 = 10 - _x2;
		while (x2 <= K){
			int x3 = 10 - _x3;
			while (x3 <= K){
				int x4 = 10 - _x4;
				while (x4 <= K){
					int x5 = 10 - _x5;
					while (x5 <= K){
						c[0][x1][x2][x3][x4][x5] = (c[0][x1][x2][x3][x4][x5] + times) % moder;
						c[1][x1][x2][x3][x4][x5] = (c[1][x1][x2][x3][x4][x5] + 1ll * times * value) % moder;
						c[2][x1][x2][x3][x4][x5] = (c[2][x1][x2][x3][x4][x5] + 1ll * times * value % moder * value) % moder;
						x5 += lowbit(x5);
					}
					x4 += lowbit(x4);
				}
				x3 += lowbit(x3);
			}
			x2 += lowbit(x2);
		}
		x1 += lowbit(x1);
	}
}

int query(int _x1, int _x2, int _x3, int _x4, int _x5, int type){
	int x1 = 10 - _x1, ret = 0;
	while (x1){
		int x2 = 10 - _x2;
		while (x2){
			int x3 = 10 - _x3;
			while (x3){
				int x4 = 10 - _x4;
				while (x4){
					int x5 = 10 - _x5;
					while (x5){
						ret = (ret + c[type][x1][x2][x3][x4][x5]) % moder;
						x5 -= lowbit(x5);
					}
					x4 -= lowbit(x4);
				}
				x3 -= lowbit(x3);
			}
			x2 -= lowbit(x2);
		}
		x1 -= lowbit(x1);
	}
	return ret;
}

int power_mod(int a, int exp){
	int ret = 1;
	for ( ; exp; exp >>= 1){
		if (exp & 1){
			ret = 1ll * ret * a % moder;
		}
		a = 1ll * a * a % moder;
	}
	return ret;
}

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 0, x; i < n; ++ i){
		scanf("%d", &x);
		++ cnt[x];
	}
	for (int i = N - 1; i >= 0; -- i){
		int x[M], y = i;
		for (int i = 0; i < M - 1; ++ i){
			x[i] = y % 10;
			y /= 10;
		}
		if (cnt[i]){
			add(x[4], x[3], x[2], x[1], x[0], i, cnt[i]);
		}
		int sum0 = query(x[4], x[3], x[2], x[1], x[0], 0);
		int sum1 = query(x[4], x[3], x[2], x[1], x[0], 1);
		int sum2 = query(x[4], x[3], x[2], x[1], x[0], 2);
		if (!sum0){
			continue;
		}
		if (sum0 == 1){
			f[i] = sum2;
			continue;
		}
		f[i] = (1ll * sum1 * sum1 + sum2) % moder * power_mod(2, sum0 - 2) % moder;
	}
	for (int i = 0; i < 1 << M; ++ i){
		orz[i].second = 1;
		for (int j = 0; j < M; ++ j){
			orz[i].first *= 10;
			++ orz[i].first;
			if (i >> j & 1){
				-- orz[i].first;
				orz[i].second *= -1;
			}
		}
	}
	for (int i = 0; i < N; ++ i){
		int a[M], x = i;
		for (int j = 0; j < M; ++ j){
			a[j] = x % 10;
			x /= 10;
		}
		x = 0;
		for (int j = 0; j < M; ++ j){
			x <<= 1;
			if (a[j]){
				++ x;
			}
		}
		for (int j = 0; j < 1 << M; ++ j){
			if ((j | x) != 63){
				continue;
			}
			ll &u = g[i - orz[j].first];
			u = ((u + f[i] * orz[j].second) % moder + moder) % moder;
		}
	}
	ll ret = 0;
	for (int i = 0; i < N; ++ i){
		ret ^= i * g[i];
	}
	return printf("%I64d\n", ret), 0;
}
