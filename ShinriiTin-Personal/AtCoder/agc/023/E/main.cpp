#include <bits/stdc++.h>

int main(){
	const int mod = (int)1e9 + 7;
	
	int n; scanf("%d", &n);
	
	int a[n+1], cnt[n+1], S = 1;
	
	memset(cnt+1, 0, sizeof(int)*n);
	
	for(int i=1;i<=n;++i) scanf("%d", a+i), ++ cnt[a[i]];	
	
	for(int i=n;i;--i){
		cnt[i-1] += cnt[i];
		if((cnt[i] -= n-i) <= 0) return puts("0"), 0;
		S = 1ll*S*cnt[i]%mod;
	}
	
	auto inv = [&](int x){
		int res = 1, k = mod-2;
		for(;k;x=1ll*x*x%mod, k>>=1)
			if(k&1) res = 1ll*res*x%mod; 
		return res;
	};
	
	int d[n+1], x[n+1], pre[n+1];
	
	d[0] = 1, x[0] = 0;
	for(int i=1, last = 1;i<=n;++i){
		d[i] = cnt[i]>1? 1ll*d[i-1]*(cnt[i]-1)%mod*inv(cnt[i])%mod: d[i-1];
		x[i] = cnt[i]>1? x[i-1]: x[i-1]+1;
		if(cnt[i] == 1) last = i;
		pre[i] = last;
	}
	
	auto bit_sum = [&](int* bit, int x){
		int res = 0;
		for(;x;x-=x&-x) res = (res + bit[x])%mod;
		return res;
	};
	
	auto bit_add = [&](int* bit, int x, int y){
		for(;x&&x<=n;x+=x&-x) bit[x] = (bit[x] + y)%mod;	
	};

	int bit[n+1];
	
	memset(bit+1, 0, sizeof(int)*n);
	
	int ans = 0;
	
	for(int i=1;i<=n;++i){
		int tmp = bit_sum(bit, a[i]) - bit_sum(bit, pre[a[i]]-1);
		if(tmp < 0) tmp += mod;
		ans = (ans + 1ll*S*d[a[i]]%mod*tmp)%mod;
		bit_add(bit, a[i], inv(d[a[i]]));
	}

	ans = 1ll*ans*inv(2)%mod;

	int _bit[n+1], _ans = 0, _cnt = 0;
	
	memset(bit+1, 0, sizeof(int)*n);
	memset(_bit+1, 0, sizeof(int)*n);

	for(int i=n;i;--i){
		_cnt = (_cnt + bit_sum(_bit, a[i]-1))%mod;
		bit_add(_bit, a[i], 1);
		int tmp = bit_sum(bit, a[i]-1) - bit_sum(bit, pre[a[i]]-1);
		if(tmp < 0) tmp += mod;
		_ans = (_ans + 1ll*S*d[a[i]]%mod*tmp)%mod;
		bit_add(bit, a[i], inv(d[a[i]]));
	}
	
	_ans = 1ll*_ans*inv(2)%mod;
	
	_ans = (1ll*S*_cnt - _ans + mod)%mod;

	printf("%d\n", (ans + _ans)%mod);

	return 0;
}
 
