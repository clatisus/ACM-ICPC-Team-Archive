#include<bits/stdc++.h>

const int N = 100010;

int n, c, k, a[N];

int main(){
	scanf("%d%d%d", &n, &c, &k);
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
	}
	std::sort(a, a + n);
	int cnt = 0, now = a[0] + k, ans = 0;
	for (int i = 0; i < n; ++ i){
		if (cnt == c || a[i] > now){
			now = a[i] + k;
			cnt = 0;
			++ ans;
		}
		++ cnt;
	}
	if (cnt){
		++ ans;
	}
	return printf("%d\n", ans), 0;
}
