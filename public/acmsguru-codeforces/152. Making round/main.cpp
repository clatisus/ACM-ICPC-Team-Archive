#include <bits/stdc++.h>

#define rep(i,a,b) for(int i=(a);i<=(b);++i) 

const int max_N = 10000 + 21;

int n, a[max_N], sum_a;

int min[max_N], max[max_N];

int min_sum, max_sum, delta;

int main(){
	scanf("%d", &n);
	rep(i,1,n){
		scanf("%d", a+i);
		sum_a += a[i];
	}
	rep(i,1,n){
		min_sum += (min[i] = std::floor(100. * a[i] / sum_a));
		max_sum += (max[i] = std::ceil(100. * a[i] / sum_a));
	}
	if(min_sum<=100 && max_sum>=100){
		delta = 100 - min_sum;
		for(int i=1;i<=n;++i){
			int tmp = min[i];
			if(delta && min[i]<max[i]){
				-- delta;
				++ tmp;
			}
			printf("%d%c", tmp, " \n"[i==n]);
		}
	}
	else puts("Yahaha");
	return 0;
}
