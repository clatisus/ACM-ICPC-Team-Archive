#include<bits/stdc++.h>

typedef long long ll;
const int N = 1010;
const int moder = 1e9 + 7;

struct matrix{
	int a[2][2];
	
	matrix (){memset(a, 0, sizeof(a));}
	
	int *operator [] (int n){return a[n];}
	
	matrix operator * (const matrix &m)const{
		matrix ret;
		for (int k = 0; k < 2; ++ k){
			for (int i = 0; i < 2; ++ i){
				for (int j = 0; j < 2; ++ j){
					ret.a[i][j] = (ret.a[i][j] + 1ll * a[i][k] * m.a[k][j]) % moder;
				}
			}
		}
		return ret;
	}
};

int powermod(int a, ll exp){
	int ret = 1;
	for ( ; exp > 0; exp >>= 1){
		if (exp & 1){
			ret = 1ll * ret * a % moder;
		}
		a = 1ll * a * a % moder;
	}
	return ret;
}

matrix powermod(matrix a, ll exp){
	matrix ret;
	ret[0][0] = ret[1][1] = 1;
	for ( ; exp > 0; exp >>= 1){
		if (exp & 1){
			ret = ret * a;
		}
		a = a * a;
	}
	return ret;
}

char s[N][N];

int main(){
	int h, w;
	scanf("%d%d", &h, &w);
	ll k;
	scanf("%lld", &k);
	for (int i = 0; i < h; ++ i){
		scanf("%s", &s[i]);
	}
	int black = 0;
	for (int i = 0; i < h; ++ i){
		for (int j = 0; j < w; ++ j){
			black += s[i][j] == '#';
		}
	}
	int row = 0;
	for (int i = 0; i < h; ++ i){
		row += s[i][0] == '#' && s[i][w - 1] == '#';
	}
	int column = 0;
	for (int i = 0; i < w; ++ i){
		column += s[0][i] == '#' && s[h - 1][i] == '#';
	}
	if (row && column || !k){
		puts("1");
		return 0;
	}
	if (!row && !column){
		printf("%d\n", powermod(black, k - 1));
		return 0;
	}
	matrix trans;
	trans[0][0] = black;
	if (row){
		for (int i = 0; i < h; ++ i){
			for (int j = 0; j < w - 1; ++ j){
				trans[0][1] += s[i][j] == '#' && s[i][j + 1] == '#';
			}
		}
	}
	else{
		for (int j = 0; j < w; ++ j){
			for (int i = 0; i < h - 1; ++ i){
				trans[0][1] += s[i][j] == '#' && s[i + 1][j] == '#';
			}
		}
	}
	trans[0][1] = (moder - trans[0][1]) % moder;
	trans[1][1] = row | column;
	trans = powermod(trans, k - 1);
	int ans = trans[0][0] + trans[0][1];
	ans -= ans >= moder ? moder : 0;
	printf("%d\n", ans);
	return 0;
}
