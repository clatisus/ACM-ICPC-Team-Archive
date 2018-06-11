#include<bits/stdc++.h>

const int N = 100010;
typedef long long ll;

int a[N];
ll pre1[N], pre2[N];

int main(){
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++ i){
		scanf("%d", &a[i]);
		pre1[i] = pre1[i - 1] + a[i];
		pre2[i] = pre2[i - 1] + std::max(a[i], 0);
	}
	ll ans = 0;
	for (int i = 1; i <= n - k + 1; ++ i){
		ans = std::max(ans, pre1[i + k - 1] - pre1[i - 1] + pre2[i - 1] + pre2[n] - pre2[i + k - 1]);
		ans = std::max(ans, pre2[i - 1] + pre2[n] - pre2[i + k - 1]);
	}
	printf("%lld\n", ans);
	return 0;
}
