#include<bits/stdc++.h>

const int N = 100010;
typedef std::pair <int, int> pii;

int a[N];
pii p[N];

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
		p[i] = {a[i], i};
	}
	std::sort(p, p + n);
	int ans = 0;
	for (int i = 0; i < n; ++ i){
		ans += (p[i].second & 1) != (i & 1);
	}
	printf("%d\n", ans >> 1);
	return 0;
}
