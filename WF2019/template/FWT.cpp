// FWT模板
// length必须为2的幂，不需要像FFT那样扩大两倍 

#include<bits/stdc++.h>

const int moder = 1e9 + 7;
const int inv2 = 5e8 + 4;

void FWT_XOR(int *a, int length, int type){
	int len = -1;
	for (int x = length; x; ++ len, x >>= 1);
	for (int i = 1; i <= len; ++ i){
		for (int j = 0; j < length; j += 1 << i){
			for (int k = j, szk = 1 << i - 1; k < j + szk; ++ k){
				int s = a[k], t = a[k + szk];
				a[k] = s + t >= moder ? s + t - moder : s + t;
				a[k + szk] = s - t < 0 ? s - t + moder : s - t;
			}
		}
	}
	if (type == 1) return;
	int inv = powermod(length, moder - 2);
	for (int i = 0; i < length; ++ i){
		a[i] = 1ll * a[i] * inv % moder;
	}
}

void FWT_AND(int *a, int length, int type){
	int len = -1;
	for (int x = length; x; ++ len, x >>= 1);
	for (int i = 1; i <= len; ++ i){
		for (int j = 0; j < length; j += 1 << i){
			for (int k = j, szk = 1 << i - 1; k < j + szk; ++ k){
				a[k] = (a[k] + 1ll * type * a[k + szk] + moder) % moder;
			}
		}
	}
}

void FWT_OR(int *a, int length, int type){
	int len = -1;
	for (int x = length; x; ++ len, x >>= 1);
	for (int i = 1; i <= len; ++ i){
		for (int j = 0; j < length; j += 1 << i){
			for (int k = j, szk = 1 << i - 1; k < j + szk; ++ k){
				a[k + szk] = (a[k + szk] + 1ll * type * a[k] + moder) % moder;
			}
		}
	}
}

int main(){
	return 0;
}
