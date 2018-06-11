#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <algorithm>

const int max_N = (int)2e5 + 21;

int n, k, a[max_N], p[max_N], _p[max_N], cnt[max_N], ans[max_N];

void merge_sort(int l, int r){
	if(l == r) { p[l] = l; return; }
	int mid = (l+r)>>1;
	merge_sort(l, mid), merge_sort(mid+1, r);
	int *lp = p+l, *rp = p+mid+1;
	for(int i=l;i<=r;++i){
		if((rp-p)>r || ((lp-p)<=mid && a[*lp]<a[*rp])) _p[i] = *lp ++;
		else{
			cnt[*rp] += (p+mid+1) - lp;
			_p[i] = *rp ++;
		}
	}
	for(int i=l;i<=r;++i) p[i] = _p[i];
}

void testCase(){
	static int Case = 0;
	static int sum_n = 0;
	assert(scanf("%d%d", &n, &k) == 2);
	assert(1<=n&&n<=200000);
	assert(1<=k&&k<=n);
	assert((sum_n+=n)<=800000);
	for(int i=1;i<=n;++i){
		assert(scanf("%d", a+i) == 1);
		assert(1<=a[i]&&a[i]<=1000000000);
	}
	memset(cnt+1, 0, sizeof(int)*n);
	memset(ans+1, 0, sizeof(int)*n);
	merge_sort(1, n);
	for(int i=1;i<=n;++i) 
		if(cnt[i]>=k) ans[i-k] = i;
	for(int i=1, j=1;i<=n;++i) 
		if(cnt[p[i]]<k) {
			while(ans[j]) ++ j;
			ans[j] = p[i];
		}
	printf("Case #%d:\n", ++ Case);
	for(int i=1;i<=n;++i) printf("%d\n", a[ans[i]]);
}

int main(){
	int T; scanf("%d", &T); while(T --) testCase();
	return 0;
} 
