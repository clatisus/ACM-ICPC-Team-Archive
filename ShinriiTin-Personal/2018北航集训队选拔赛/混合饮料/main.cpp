#include <bits/stdc++.h>

const int max_N = (int)1e5 + 21;

int n, a[max_N], b[max_N], c[max_N], q[max_N], p[max_N], _p[max_N], bit[max_N], cnt[max_N];

long long ans1, ans2, ans3;

struct cmpFunctorA{
	bool operator ()(const int&x, const int&y){
		return a[x] < a[y];
	}
};

struct cmpFunctorB{
	bool operator ()(const int&x, const int&y){
		return b[x] < b[y];
	}
};

void bit_add(int pos, int delta){
	for(int x=pos;x&&x<=n;x+=x&-x) bit[x] += delta;
}

void bit_sum(int pos, int&res){
	for(int x=pos;x;x-=x&-x) res += bit[x];
}

void cdq(int l, int r){
	if(l==r) { p[l] = l; return; }
	
	int mid = (l + r) >> 1;
	cdq(l, mid), cdq(mid+1, r);
	
	int *lp = p+l, *rp = p+mid+1;
	for(int i=l;i<=r;++i){
		if((lp-p)>mid || ((rp-p)<=r && b[q[*rp]]<b[q[*lp]])) _p[i] = *rp ++;
		else _p[i] = *lp ++;
		
		if(_p[i] > mid) bit_sum(c[q[_p[i]]], cnt[q[_p[i]]]);
		else bit_add(c[q[_p[i]]], 1);
	}
	
	for(int i=l;i<=r;++i)
		if((p[i] = _p[i]) <= mid){
			bit_add(c[q[p[i]]], -1);
		}
}

void _2dDominator(int*a){
	memset(bit+1, 0, sizeof(int)*n);
	for(int i=1;i<=n;++i){
		int tmp = 0;
		bit_sum(a[q[i]], tmp);
		ans3 -= 1ll*tmp*(tmp-1)/2;
		bit_add(a[q[i]], 1);
	}
}

int main(){
	scanf("%d", &n);
	
	ans1 = n;
	ans2 = 1ll*n*(n-1)/2;
	ans3 = 1ll*n*(n-1)/2*(n-2)/3;
	
	for(int i=1;i<=n;++i) scanf("%d", a+i);
	for(int i=1;i<=n;++i) scanf("%d", b+i);
	for(int i=1;i<=n;++i) scanf("%d", c+i);

	for(int i=1;i<=n;++i) q[i] = i;
	std::sort(q+1, q+1+n, cmpFunctorA());
	cdq(1, n); // calculate cnt[x]: how many points can be dominated by x
	for(int i=1;i<=n;++i){
		ans2 -= cnt[i];
		ans3 += 1ll*cnt[i]*(cnt[i]-1);
	}
	
	_2dDominator(b); // count (x, y, z) which x dominates y and z in both a and b
	_2dDominator(c); // count (x, y, z) which x dominates y and z in both a and c
	std::sort(q+1, q+1+n, cmpFunctorB());
	_2dDominator(c); // count (x, y, z) which x dominates y and z in both b and c
	
	printf("Debug: %lld %lld %lld\n", ans1, ans2, ans3);
	
	printf("%lld\n", ans1+ans2+ans3);

	return 0;
}
