#include<bits/stdc++.h>

const int N = 100010;
const int moder = 1e9 + 7;

int n, cnt[N];

int power_mod(int a, int index){
	int ans = 1;
	while (index){
		if (index & 1){
			ans = 1ll * a * ans % moder;
		}
		a = 1ll * a * a % moder;
		index >>= 1;
	}
	return ans;
}

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 0, x; i < n; ++ i){
		scanf("%d", &x);
		++ cnt[x];
	}
	if (n & 1){
		if (cnt[0] != 1){
			return printf("0\n"), 0;
		}
		for (int i = 2; i < n; i += 2){
			if (cnt[i] != 2){
				return printf("0\n"), 0;
			}
		}
	}
	else{
		for (int i = 1; i < n; i += 2){
			if (cnt[i] != 2){
				return printf("0\n"), 0;
			}
		}
	}
	return printf("%d\n", power_mod(2, n >> 1)), 0;
}
