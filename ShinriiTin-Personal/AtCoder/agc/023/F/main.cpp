#include <bits/stdc++.h>

int main(){
	int n; scanf("%d", &n);
	
	int f[n+1], p[n+1], c0[n+1], c1[n+1];
	
	for(int i=2;i<=n;++i) scanf("%d", p+i);
	
	for(int i=1,v;i<=n;++i){
		scanf("%d", &v);
		c0[i] = !v, c1[i] = v;
		f[i] = i;
	}
	
	auto find = [&](int x){
		int re = x; 
		while(re != f[re]) re = f[re];
		for(int i=x,k;i!=re;i=k) k = f[i], f[i] = re;
		return re;
	};
	
	using pair = std::pair<double, int>;
	
	std::priority_queue<pair> pq;
	
	#define eps (1e-12)
	
	for(int i=2;i<=n;++i) pq.push({c0[i]/(c1[i]+eps), i});
	
	long long ans = 0;
	
	while(!pq.empty()){
		int x = pq.top().second; pq.pop();
		if(x != find(x)) continue;
		int pa = find(p[x]);
		ans += 1ll*c1[pa]*c0[x];
		f[x] = pa;
		c0[pa] += c0[x], c1[pa] += c1[x];
		if(pa == 1) continue;
		pq.push({c0[pa]/(c1[pa]+eps), pa});
	}
	
	printf("%lld\n", ans);

	return 0;
} 
