#include <bits/stdc++.h>

int main(){
	int n; scanf("%d", &n);
	
	int a[n], b[n], c[n];
	
	for(int i=0;i<n;++i) scanf("%d", a+i);
	for(int i=0;i<n;++i) scanf("%d", b+i);
	for(int i=0;i<n;++i) scanf("%d", c+i);
	
	int ans1 = n, ans2 = n*(n-1)/2, ans3 = n*(n-1)/2*(n-2)/3;
	
	auto check = [&](std::vector<int> vec){
		int maxa = 0, maxb = 0, maxc = 0;
		for(auto&x:vec){
			maxa = std::max(maxa, a[x]);
			maxb = std::max(maxb, b[x]);
			maxc = std::max(maxc, c[x]);
		}
		for(auto&x:vec)
			if(a[x]<maxa && b[x]<maxb && c[x]<maxc)
				return 1;
		return 0;
	};
	
	for(int i=0;i<n;++i)
		for(int j=i+1;j<n;++j){
			ans2 -= check({i, j});
		}
	
	for(int i=0;i<n;++i)
		for(int j=i+1;j<n;++j)
			for(int k=j+1;k<n;++k){
				ans3 -= check({i, j, k});
			}
	
	printf("Debug: %d %d %d\n", ans1, ans2, ans3);
	
	printf("%d\n", ans1+ans2+ans3);
	
	return 0;
}
