#include<bits/stdc++.h>
#define ll long long

const int N = 200010;

inline int lowbit(int n){return n & (-n);}

std::vector <ll> vec;
int n, k;
int a[N];
ll pre[N];
int c[N];

int getsit(ll n){
	return std::lower_bound(vec.begin(), vec.end(), n) - vec.begin() + 1;
}

int add(int sit, int value){
	for ( ; sit < N; sit += lowbit(sit)){
		c[sit] += value;
	}
}

int query(int sit){
	int ret = 0;
	for ( ; sit; sit -= lowbit(sit)){
		ret += c[sit];
	}
	return ret;
}

int main(){
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++ i){
		scanf("%d", &a[i]);
		a[i] -= k;
	}
	for (int i = 1; i <= n; ++ i){
		pre[i] = pre[i - 1] + a[i];
	}
	for (int i = 0; i <= n; ++ i){
		vec.push_back(pre[i]);
	}
	std::sort(vec.begin(), vec.end());
	vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
	long long ans = 0;
	add(getsit(0), 1);
	for (int i = 1;i <= n; ++ i){
		int sit = getsit(pre[i]);
		ans += query(sit);
		add(sit, 1);
	}
	return printf("%lld\n", ans), 0;
}
