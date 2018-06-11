#include<bits/stdc++.h>

const int N = 200010;

int p[N], inv[N];

int main(){
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= k; ++ i){
		scanf("%d", &p[i]);
		inv[p[i]] = i;
	}
	int min;
	for (int i = 1; ; ++ i){
		if (!inv[i]){
			min = i;
			break;
		}
	}
	int max = 0;
	for (int i = k; i; -- i){
		if (max > p[i] && min < p[i]){
			puts("-1");
			return 0;
		}
		max = std::max(max, p[i]);
		min = std::min(min, p[i]);
	}
	int pre = k + 1, now = pre;
	inv[n + 1] = n + 1;
	for (int i = 1; i <= n + 1; ++ i){
		if (!inv[i]){
			p[now ++] = i;
		}
		else{
			std::reverse(p + pre, p + now);
			pre = now;
		}
	}
	for (int i = 1; i <= n; ++ i){
		printf("%d%c", p[i], " \n"[i == n]);
	}
	return 0;
}
