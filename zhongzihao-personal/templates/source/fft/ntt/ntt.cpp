#include<bits/stdc++.h>

typedef long long ll;

int powermod(int a, int exp, int moder){
	int ret = 1;
	for ( ; exp; exp >>= 1){
		if (exp & 1){
			ret = 1ll * a * ret % moder;
		}
		a = 1ll * a * a % moder;
	}
	return ret;
}

void NTT(int *a, int length, int type, int moder, int root){
	if (length == 1) return;
	int len = -1;
	for (int x = length; x; ++ len, x >>= 1);
	for(int i = 1, j = 0; i < length - 1; ++ i){
		for(int s = length; j ^= s >>= 1, ~j & s; )
			;
		if(i < j){
			std::swap(a[i], a[j]);
		}
	}
	int *w = new int [length];
	w[0] = 1, w[1] = powermod(root, moder - 1 >> len, moder);
	for (int i = 2; i < length; ++ i){
		w[i] = 1ll * w[i - 1] * w[1] % moder;
	}
	for (int i = 1; i <= len; ++ i){
		for (int j = 0, szk = 1 << i - 1, szw = length >> i; j < length; j += 1 << i){
			for (int k = j, noww = 0; k < j + szk; ++ k, noww += szw){
				int s = a[k], t = 1ll * w[noww] * a[k + szk] % moder;
				a[k] = s + t >= moder ? s + t - moder : s + t;
				a[k + szk] = s - t < 0 ? s - t + moder : s - t;
			}
		}
	}
	delete [] w;
	if (type == 1) return;
	int inv = powermod(length, moder - 2, moder);
	for (int i = 0; i < length; ++ i){
		a[i] = (ll) a[i] * inv % moder;
	}
}
