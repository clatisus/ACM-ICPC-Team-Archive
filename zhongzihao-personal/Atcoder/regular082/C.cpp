#include<bits/stdc++.h>

const int N = 100010;

int n;
int cnt[N];

int main(){
	scanf("%d", &n);
	for (int i = 0, x; i < n; ++ i){
		scanf("%d", &x);
		++ cnt[x];
	}
	int ans = 0;
	for (int i = 1; i < N - 1; ++ i){
		ans = std::max(ans, cnt[i - 1] + cnt[i] + cnt[i + 1]);
	}
	return printf("%d\n", ans), 0;
}
