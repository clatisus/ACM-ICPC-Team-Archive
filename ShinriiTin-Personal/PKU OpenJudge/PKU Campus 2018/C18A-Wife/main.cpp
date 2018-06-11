/*
一定存在一种最优方案，每个位置要么不选，要么选够7个 
*/
#include <bits/stdc++.h>

const int max_N = (int)1e4 + 21;

int T, n, a[max_N], f[max_N];

void testCase(){
	scanf("%d", &n);
	for(int i=1;i<=n;++i) scanf("%d", a+i);
	memset(f+1, 0,sizeof(int)*n);
	for(int i=1;i<=n;++i){
		f[i] = 0x3f3f3f3f;	
		for(int j=std::max(0,i-7);j<i;++j)
			f[i] = std::min(f[i], f[j]);
		f[i] += a[i];
	}
	int ans = 0x3f3f3f3f;
	for(int i=std::max(1, n-6);i<=n;++i){
		ans = std::min(ans, f[i]);
	}
	printf("%lld\n", 7ll*ans);
}

int main(){
	for(scanf("%d", &T); T --; testCase());
	return 0;
}
