#include<bits/stdc++.h>

const int N = 200010;
typedef long long ll;

char s[N];
int cnt[N];

int main(){
	scanf("%s", s);
	int n = strlen(s);
	for (int i = 0; i < n; ++ i){
		++ cnt[s[i]];
	}
	ll ans = 1ll * n * (n + 1) / 2 + 1;
	for (int i = 0; i < N; ++ i){
		ans -= 1ll * cnt[i] * (cnt[i] + 1) >> 1;
	}
	printf("%lld\n", ans);
	return 0;
}
