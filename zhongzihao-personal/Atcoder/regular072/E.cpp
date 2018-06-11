#include<bits/stdc++.h>
#define ll long long

const int N = 500010;

int a[N], dis[N];
int n, d;
ll b[N];

int main(){
	scanf("%d%d", &n, &d);
	int _d = d;
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
		d = dis[i] = std::min(std::abs(d - a[i]), d);
	}
	b[n - 1] = 1;
	for (int i = n - 1; i; -- i){
		if (b[i] <= a[i] / 2){
			b[i - 1] = b[i];
		}
		else{
			b[i - 1] = b[i] + a[i];
		}
	}
	int q;
	scanf("%d", &q);
	while (q --){
		int x;
		scanf("%d", &x);
		-- x;
		int _dis = x ? dis[x - 1] : _d;
		printf(b[x] <= _dis ? "YES\n" : "NO\n");
	}
	return 0;
}
