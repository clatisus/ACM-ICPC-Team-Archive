#include<bits/stdc++.h>

#define lowbit(x) ((x) & (-(x)))

const int N = 10000010;
const int moder = 1e9 + 7;

int c[N], n;

void add(int sit, int value){
	while (sit < N){
		c[sit] = (c[sit] + value) % moder;
		sit += lowbit(sit);
	}
}

int query(int sit){
	int ret = 0;
	while (sit){
		ret = (ret + c[sit]) % moder;
		sit -= lowbit(sit);
	}
	return ret;
}

int main(){
	scanf("%d", &n);
	add(1, moder - 1);
	int ans = 0;
	for (int i = 0; i < n; ++ i){
		int x = !i ? 1 : (query(i) + 1) % moder;
		add(i + 1, x);
		add(i + 2, (moder - x) % moder);
		if (i == n - 1){
			ans = (ans + 1ll * x * n) % moder;
			continue;
		}
		else{
			ans = (ans + 1ll * (n - 1) * (n - 1) % moder * x) % moder;
		}
		if (i + 3 >= n){
			ans = (ans + 1ll * x * (n - 1)) % moder;
			continue;
		}
		add(i + 3, x);
		add(n, (moder - x) % moder);
		ans = (ans + 1ll * (i + 2) * x) % moder;
	}
	return printf("%d\n", ans), 0;
}
