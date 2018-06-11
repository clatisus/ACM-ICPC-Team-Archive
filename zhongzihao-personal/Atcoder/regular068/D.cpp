#include<bits/stdc++.h>

const int N = 100010;

int n;
bool flag[N];

int main(){
	scanf("%d", &n);
	for (int i = 0, x; i < n; ++ i){
		scanf("%d", &x);
		flag[x] = true;
	}
	int ans = 0;
	for (int i = 0; i < N; ++ i){
		ans += flag[i];
	}
	if (!(ans & 1)){
		-- ans;
	}
	return printf("%d", ans), 0;
}
