#include<bits/stdc++.h>

const int N = 200010;

int a[N], left[N], right[N];

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i){
		scanf("%d", &a[i]);
	}
	std::stack <int> s;
	for (int i = 0; i <= n + 1; ++ i){
		while (!s.empty() && a[s.top()] > a[i]){
			right[s.top()] = i;
			s.pop();
		}
		if (!s.empty()) left[i] = s.top();
		s.push(i);
	}
	long long ans = 0;
	for (int i = 1; i <= n; ++ i){
		ans += 1ll * a[i] * (right[i] - i) * (i - left[i]);
	}
	printf("%lld\n", ans);
	return 0;
}
