#include<bits/stdc++.h>

const int N = 210;
const int moder = 998244353;

int x[N], y[N];
int n;

int powermod(int a, int exp){
	int ret = 1;
	for ( ; exp; exp >>= 1){
		if (exp & 1){
			ret = 1ll * ret * a % moder;
		}
		a = 1ll * a * a % moder;
	}
	return ret;
}

int det(int x1, int y1, int x2, int y2){
	return x1 * y2 - y1 * x2;
}

bool onSeg(int x1, int y1, int x2, int y2, int x3, int y3){
	return !det(x2 - x1, y2 - y1, x3 - x1, y3 - y1);
}

int main(){
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i){
		scanf("%d%d", &x[i], &y[i]);
	}
	int ans = 0;
	for (int i = 0; i < n; ++ i){
		for (int j = i + 1; j < n; ++ j){
			int cnt = 0;
			for (int k = 0; k < n; ++ k){
				cnt += onSeg(x[i], y[i], x[j], y[j], x[k], y[k]);
			}
			ans = (ans + 1ll * (powermod(2, cnt) - (cnt + 1) + moder) * powermod(cnt * (cnt - 1) >> 1, moder - 2)) % moder;
		}
	}
	ans = (ans + n + 1) % moder;
	return printf("%d\n", (powermod(2, n) - ans + moder) % moder), 0;
}
