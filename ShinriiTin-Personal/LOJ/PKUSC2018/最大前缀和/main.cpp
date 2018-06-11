#include <bits/stdc++.h>

const int max_N = 20 + 21;
const int max_S = (1 << 20);
const int mod = 998244353;

#define max_s (1 << n)
#define lbt(x) ((x)&-(x))

int n, a[max_N], f[max_S], g[max_S], ans;

long long s[max_S];

int main(){
	scanf("%d", &n);
	for(int i=0;i<n;++i){
		scanf("%d", a+i);
		s[1 << i] = a[i];
		f[1 << i] = 1;
	}
	for(int i=1;i<max_s;++i){
		s[i] = s[i ^ lbt(i)] + s[lbt(i)];
	}
	for(int i=1;i<max_s;++i)
		if(s[i] > 0){
			for(int j=i^(max_s-1);j;j^=lbt(j)){
				f[i | lbt(j)] = (f[i | lbt(j)] + f[i]) % mod;
			}
		}
	g[0] = 1;
	for(int i=1;i<max_s;++i)
		if(s[i] <= 0){
			for(int j=i;j;j^=lbt(j)){
				g[i] = (g[i] + g[i ^ lbt(j)]) % mod;
			}
		}
	for(int i=1;i<max_s;++i){
		ans = (ans + 1ll*f[i] * s[i] % mod * g[i^(max_s-1)]) % mod;	
	}
	printf("%d\n", (ans + mod) % mod);
	return 0;
}
