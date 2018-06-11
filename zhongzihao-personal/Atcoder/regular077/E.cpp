#include<bits/stdc++.h>

typedef long long ll;
const int N = 100010;
inline int lowbit(int n){return n & -n;}

int n, m;
ll c[N], ans[N], a[N];

void add(int sit, ll value){
	for ( ; sit < N; sit += lowbit(sit)){
		c[sit] += value;
	}
}

ll query(int sit){
	ll ret = 0;
	for ( ; sit; sit -= lowbit(sit)){
		ret += c[sit];
	}
	return ret;
}

int main(){
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
	}
	for (int i = 1; i < n; ++ i){
		if (a[i - 1] <= a[i]){
			int x = a[i] - a[i - 1];
			add(1, x);
			add(2, -x);
			add(a[i - 1] + 2, -1);
			add(a[i] + 1, x);
			add(a[i] + 2, -x + 1);
		}
		else{
			int x = a[i] + m - a[i - 1];
			add(1, a[i]);
			add(2, -a[i] - 1);
			add(a[i] + 1, x);
			add(a[i] + 2, 1 - x);
			add(a[i - 1] + 2, -1);
		}
		/*
		for (int i = 1; i <= m; ++ i){
			ans[i] = ans[i - 1] + query(i);
			printf("%d%c", ans[i], " \n"[i == m]);
		}*/
	}
	ll min = LLONG_MAX;
	for (int i = 1; i <= m; ++ i){
		ans[i] = ans[i - 1] + query(i);
		min = std::min(min, ans[i]);
	}
	return printf("%lld\n", min), 0;
}
