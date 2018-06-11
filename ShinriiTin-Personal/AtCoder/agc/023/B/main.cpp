#include <bits/stdc++.h>

const int mod = 998244353;

const int base = 26;

const int max_N = 600 + 21;

char a[max_N][max_N];

int n, hash_x[max_N][max_N], hash_y[max_N][max_N];

int pw[max_N], _pw[max_N], inv[30];

int get_hash_x(int x, int l, int r){
	if(!l) return hash_x[x][r];
	int res = (hash_x[x][r] - hash_x[x][l-1] + mod)%mod;
	return 1ll*res*_pw[l]%mod;
}

int get_hash_y(int y, int l, int r){
	if(!l) return hash_y[r][y];
	int res = (hash_y[r][y] - hash_y[l-1][y] + mod)%mod;
	return 1ll*res*_pw[l]%mod;
}

bool check(int x, int y){
	for(int i=0;i<n;++i)
		if(get_hash_x(x+i, y+i, y+n-1) != get_hash_y(y+i, x+i, x+n-1))
			return false;
	return true;
}

int main(){
	scanf("%d", &n);
	inv[1] = 1;
	for(int i=2;i<=base;++i){
		inv[i] = 1ll*(mod/i)*inv[mod%i]%mod;
		if(inv[i]) inv[i] = mod - inv[i];	
	}
	pw[0] = _pw[0] = 1;
	for(int i=1;i<=2*n;++i){
		pw[i] = 1ll*pw[i-1]*base%mod;
		_pw[i] = 1ll*_pw[i-1]*inv[base]%mod;
	}
	for(int i=0;i<n;++i){
		scanf("%s", a[i]);
		for(int j=0;j<n;++j) a[i][j+n] = a[i][j];
		for(int j=0;j<2*n;++j) a[i+n][j] = a[i][j];
	}
	for(int i=0;i<2*n;++i)
		for(int j=0;j<2*n;++j){
			hash_x[i][j] = ((j ? hash_x[i][j-1] : 0) + 1ll*pw[j]*(a[i][j] - 'a'))%mod;
		}
	for(int j=0;j<2*n;++j)
		for(int i=0;i<2*n;++i){
			hash_y[i][j] = ((i ? hash_y[i-1][j] : 0) + 1ll*pw[i]*(a[i][j] - 'a'))%mod;
		}
	int ans = 0;
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j){
			ans += check(i, j);
		}
	printf("%d\n", ans);
	return 0;
}
