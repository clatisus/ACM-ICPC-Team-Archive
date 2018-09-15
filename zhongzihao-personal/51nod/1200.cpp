// FWT模板
// length必须为2的幂，不需要像FFT那样扩大两倍 

#include<bits/stdc++.h>

const int moder = 1e9 + 7;
const int inv2 = 5e8 + 4;
const int N = 1 << 16;

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

int a[N], b[N];

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 2; i <= m; ++ i){
        bool flag = true;
        for (int j = 2; j * j <= i; ++ j){
            if (i % j == 0){
                flag = false;
                break;
            }
        }
        if (flag){
            a[i] = 1;
        }
    }
    b[0] = 1;
    FWT_XOR(a, N, 1);
    FWT_XOR(b, N, 1);
    for ( ; n > 0; n >>= 1){
        if (n & 1){
            for (int i = 0; i < N; ++ i){
                b[i] = 1ll * b[i] * a[i] % moder;
            }
        }
        for (int i = 0; i < N; ++ i){
            a[i] = 1ll * a[i] * a[i] % moder;
        }
    }
    FWT_XOR(b, N, -1);
    printf("%d\n", b[0]);
	return 0;
}
