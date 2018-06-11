#include <bits/stdc++.h>

#define inf (1ll<<60)
#define tri(x) ((x)*(x)*(x))

using ll = long long;

const int max_N = 55;

int n, m, d, v[max_N], p[max_N], q[max_N];

ll w[max_N], f[tri(max_N)], ans;

struct cmpFunctor{
	bool operator()(const int&a, const int&b){
		return v[a]*w[b] > v[b]*w[a];
	}
};

int main(){
	scanf("%d%d%d", &n, &m, &d);
	for(int i=1;i<=n;++i){
		scanf("%lld", w+i);
		if(i>1) scanf("%d", p+i);
		v[i] = 1, q[i] = i; 
	}
	for(int i=n;i>1;--i){
		w[p[i]] += w[i];
		v[p[i]] += v[i];
	}
	std::sort(q+1, q+1+n, cmpFunctor());
	for(int i=1;i<=tri(n);++i) f[i] = inf;
	f[0] = 0;
	for(int i=1;i<=n;++i){
		int siz_a = i==1 ? n: std::min(n, d);
		while(siz_a --){
			for(int j=tri(n);j>=v[i];--j)
				f[j] = std::min(f[j], f[j-v[i]] + w[i]);
		}
	}
	for(int i=0;i<=tri(n);++i){
		ll siz = m - f[i], sum = i;
		if(siz<0) break;
		for(int j=1;j<=n;++j){
			int siz_b = q[j]==1? m: std::max(d-n, 0);
			int tmp = std::min(siz_b, (int)(siz/w[q[j]]));
			sum += tmp*v[q[j]], siz -= tmp*w[q[j]];
		}
		ans = std::max(ans, sum);
	}
	printf("%lld\n", ans);
	return 0;
} 
