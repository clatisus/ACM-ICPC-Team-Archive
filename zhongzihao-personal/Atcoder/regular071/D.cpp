#include<bits/stdc++.h>

const int moder = 1e9 + 7;
const int N = 100010;

int x[N], y[N], prex[N], prey[N];
int n, m;


int main(){
	scanf("%d%d", &n, &m);
	int sum1 = 0;
	for (int i = 1; i <= n; ++ i){
		scanf("%d", &x[i]);
		prex[i] = (prex[i - 1] + x[i]) % moder;
		sum1 = (sum1 + 1ll * x[i] * i - prex[i]) % moder;
	}
	int sum2 = 0;
	for (int i = 1; i <= m; ++ i){
		scanf("%d", &y[i]);
		prey[i] = (prey[i - 1] + y[i]) % moder;
		sum2 = (sum2 + 1ll * y[i] * i - prey[i]) % moder;
	}
	return printf("%lld\n", (1ll * sum1 * sum2 % moder + moder) % moder), 0;
}
