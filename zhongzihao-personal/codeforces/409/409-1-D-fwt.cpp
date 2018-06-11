#include<bits/stdc++.h>
#define ll long long

const int N = 1000000;
const int M = 6;
const int K = 10;
const int moder = 1e9 + 7;
const int inv2 = 5e8 + 4;

int power[10], a[N], b[N], c[N], f[N];

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

int readin(){
	char ch;
	ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	int ret = 0;
	while (ch >= '0' && ch <= '9'){
		ret = ret * 10 + ch - '0';
		ch = getchar();
	}
	return ret;
}

void FWT(int *a, int length, int type){
	int len = -1;
	for (int x = length; x; ++ len, x /= 10);
	for (int i = 1; i <= len; ++ i){
		for (int j = 0; j < length; j += power[i]){
			for (int k = j, sizk = power[i - 1]; k < j + sizk; ++ k){
				for (int ii = K - 2; ii >= 0; -- ii){
					int &x = a[k + ii * power[i - 1]];
					x = (x + a[k + (ii + 1) * power[i - 1]]) % moder;
				}
			}
		}
	}
}

void UFWT(int *a, int length, int type){
	int len = -1;
	for (int x = length; x; ++ len, x /= 10);
	for (int i = 1; i <= len; ++ i){
		for (int j = 0; j < length; j += power[i]){
			for (int k = j, sizk = power[i - 1]; k < j + sizk; ++ k){
				for (int ii = 1; ii < K; ++ ii){
					int &x = a[k + (ii - 1)* power[i - 1]];
					x = (x - a[k + ii * power[i - 1]] + moder) % moder;
				}
			}
		}
	}
}

int n;

int main(){
	power[0] = 1;
	for (int i = 1; i < 8; ++ i){
		power[i] = power[i - 1] * 10;
	}
	n = readin();
	for (int i = 0, x; i < n; ++ i){
		x = readin();
		a[x] = (a[x] + 1) % moder;
		b[x] = (b[x] + x) % moder;
		c[x] = (c[x] + 1ll * x * x) % moder;
	}
	FWT(a, N, M);
	FWT(b, N, M);
	FWT(c, N, M);
	for (int i = 0; i < N; ++ i){
		if (!a[i]){
			continue;
		}
		if (a[i] == 1){
			f[i] = c[i];
			continue;
		}
		f[i] = (1ll * b[i] * b[i] + c[i]) % moder * power_mod(2, a[i] - 2) % moder;
	}
	UFWT(f, N, M);
	ll ans = 0;
	for (int i = 0; i < N; ++ i){
		ans ^= 1ll * f[i] * i;
	}
	return printf("%I64d\n", ans), 0;
}
