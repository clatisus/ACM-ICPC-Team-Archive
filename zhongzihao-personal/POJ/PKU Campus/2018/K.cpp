#include<bits/stdc++.h>

const int moder = 1e9 + 7;

inline void multadd(int &a, int b, int c){a = (a + 1ll * b * c) % moder;}
inline void add(int &a, int b){a += b; a -= a >= moder ? moder : 0;} 

int powermod(int a, int exp, int moder){
	int ret = 1;
	for ( ; exp > 0; exp >>= 1){
		if (exp & 1){
			ret = 1ll * ret * a % moder;
		}
		a = 1ll * a * a % moder;
	}
	return ret;
}

struct matrix{
	static const int N = 100;
	
	int a[N][N];
	int n, m;
	
	matrix ():n(0), m(0){memset(a, 0, sizeof(a));}
	matrix (int n, int m):n(n), m(m){memset(a, 0, sizeof(a));}
	
	int *operator [](int i){return a[i];}
	
	matrix operator + (const matrix &mat)const{
		matrix ret(n, m);
		for (int i = 0; i < n; ++ i){
			for (int j = 0; j < m; ++ j){
				ret.a[i][j] = a[i][j] + mat.a[i][j];
				ret.a[i][j] -= ret.a[i][j] >= moder ? moder : 0;
			}
		}
		return ret;
	}
	
	matrix operator * (const matrix &mat)const{
		matrix ret(n, mat.m);
		for (int i = 0; i < n; ++ i){
			for (int k = 0; k < m; ++ k){
				if (!a[i][k]) continue;
				for (int j = 0; j < mat.m; ++ j){
					multadd(ret.a[i][j], a[i][k], mat.a[k][j]);
				}
			}
		}
		return ret;
	}
	
	matrix operator * (const int &x)const{
		matrix ret(n, m);
		for (int i = 0; i < n; ++ i){
			for (int j = 0; j < m; ++ j){
				ret.a[i][j] = 1ll * x * a[i][j] % moder;
			}
		}
		return ret;
	}
	
	int det()const{
		matrix mat = *this;
		int ret = 1;
		for (int i = 0; i < n; ++ i){
			int sit = -1;
			for (int j = i; j < n; ++ j){
				if (mat.a[j][i]){
					sit = j;
					break;
				}
			}
			if (!~sit) return 0;
			if (sit != i){
				for (int j = i; j < n; ++ j){
					std::swap(mat.a[i][j], mat.a[sit][j]);
				}
				ret = ret ? moder - ret : 0;
			}
			for (int j = i + 1; j < n; ++ j){
				int coe = 1ll * mat.a[j][i] * powermod(mat.a[i][i], moder - 2, moder) % moder;
				if (!coe) continue;
				for (int k = i; k < n; ++ k){
					mat.a[j][k] = (mat.a[j][k] - 1ll * coe * mat.a[i][k]) % moder;
					mat.a[j][k] += mat.a[j][k] < 0 ? moder : 0;
				}
			}
			ret = 1ll * ret * mat.a[i][i] % moder;
		}
		return ret;
	}
};

typedef long long ll;
typedef std::pair <int, int> pii;

struct poly{
	static const int N = 1000;
	
	int a[N];
	int length, moder;
	
	poly():length(-1), moder(0){memset(a, 0, sizeof(a));}
	poly(int moder):length(-1), moder(moder){memset(a, 0, sizeof(a));}
	
	poly value(int x){
		int ret = 0;
		for (int i = 0, now = 1; i <= length; ++ i){
			ret = (ret + 1ll * a[i] * now) % moder;
			now = 1ll * now * x % moder;
		}
		return ret;
	}
	
	int &operator [](int sit){return a[sit];}
	
	poly operator + (const poly &p)const{
		poly ret(moder);
		ret.length = std::max(length, p.length);
		for (int i = 0; i <= ret.length; ++ i){
			ret.a[i] = a[i] + p.a[i];
			ret.a[i] -= ret.a[i] >= moder ? moder : 0;
		}
		for ( ; ~ret.length && !ret.a[ret.length]; -- ret.length)
			;
		return ret;
	}
	
	poly operator - ()const{
		poly ret(moder);
		ret.length = length;
		for (int i = 0; i <= ret.length; ++ i){
			ret.a[i] = a[i] ? moder - a[i] : 0;
		}
		return ret;
	}
	
	poly operator - (const poly &p)const{
		poly ret(moder);
		ret.length = std::max(length, p.length);
		for (int i = 0; i <= ret.length; ++ i){
			ret.a[i] = a[i] - p.a[i];
			ret.a[i] -= ret.a[i] < 0 ? moder : 0;
		}
		for ( ; ~ret.length && !ret.a[ret.length]; -- ret.length)
			;
		return ret;
	}
	
	poly operator * (const poly &p)const{
		poly ret(moder);
		if (!~length || !~p.length) return ret;
		ret.length = length + p.length;
		for (int i = 0; i <= length; ++ i){
			for (int j = 0; j <= p.length; ++ j){
				ret.a[i + j] = (ret.a[i + j] + 1ll * a[i] * p.a[j]) % moder;
			}
		}
		return ret;
	}
	
	poly operator * (const int &p)const{
		poly ret(moder);
		ret.length = length;
		for (int i = 0; i <= ret.length; ++ i){
			ret.a[i] = 1ll * a[i] * p % moder;
		}
		return ret;
	}
	
	poly operator / (const poly &p)const{
		poly ret(moder);
		if (!~p.length) assert(("division by zero!", 0));
		if (length < p.length) return ret;
		ret.length = length - p.length;
		poly aux = *this;
		while (aux.length >= p.length){
			int x = 1ll * aux.a[aux.length] * powermod(p.a[p.length], moder - 2, moder) % moder;
			ret.a[aux.length - p.length] = x;
			for (int j = 0; j <= p.length; ++ j){
				int &u = aux.a[aux.length + j - p.length];
				u = (u - 1ll * x * p.a[j]) % moder;
				u += u < 0 ? moder : 0;
			}
			for ( ; ~aux.length && !aux.a[aux.length]; -- aux.length)
				;
		}
		return ret;
	}
	
	poly operator % (const poly &p)const{
		if (!~p.length) assert(("division by zero!", 0));
		poly ret = *this;
		while (ret.length >= p.length){
			int x = 1ll * ret.a[ret.length] * powermod(p.a[p.length], moder - 2, moder) % moder;
			for (int j = 0; j <= p.length; ++ j){
				int &u = ret.a[ret.length + j - p.length];
				u = (u - 1ll * x * p.a[j]) % moder;
				u += u < 0 ? moder : 0;
			}
			for ( ; ~ret.length && !ret.a[ret.length]; -- ret.length)
				;
		}
		return ret;
	}
	
	static poly interpolation(std::vector <pii> vec, int moder){
		int n = vec.size() - 1;
		poly aux(moder); aux.length = 0; aux.a[0] = 1;
		for (int i = 0; i <= n; ++ i){
			poly aux1(moder); aux1.length = 1;
			aux1.a[1] = 1; aux1.a[0] = moder - vec[i].first;
			aux1.a[0] -= aux1.a[0] >= moder ? moder : 0;
			aux = aux * aux1;
		}
		poly ret(moder);
		for (int i = 0; i <= n; ++ i){
			poly aux1(moder); aux1.length = 1;
			aux1.a[1] = 1; aux1.a[0] = moder - vec[i].first;
			aux1.a[0] -= aux1.a[0] >= moder ? moder : 0;
			poly aux2 = aux / aux1;
			int x = 1;
			for (int j = 0; j <= n; ++ j){
				if (i == j) continue;
				x = 1ll * x * (vec[i].first - vec[j].first) % moder;
				x += x < 0 ? moder : 0;
			}
			x = powermod(x, moder - 2, moder);
			ret = ret + (aux2 * x) * vec[i].second;
		}
		return ret;
	}
};

matrix power(matrix a, int exp){
	matrix ret(a.n, a.n);
	for (int i = 0; i < a.n; ++ i){
		ret.a[i][i] = 1;
	}
	for ( ; exp > 0; exp >>= 1){
		if (exp & 1) ret = ret * a;
		a = a * a;
	}
	return ret;
}

poly zzh[40];

matrix mat(91, 91), trans[100];
poly p;

void solve(){
	int n;
	scanf("%d", &n);
	poly pol(moder);
	pol[0] = 1;
	pol.length = 0;
	for (int i = 0; i <= 30; ++ i){
		if (n - 1 >> i & 1){
			pol = pol * zzh[i] % p;
		}
	}
	matrix mat(91, 91);
	int ret = 0;
	for (int i = 0; i <= 90; ++ i){
		ret = (ret + 1ll * trans[i][1][11] * pol[i]) % moder;
		ret = (ret + 1ll * trans[i][2][11] * pol[i]) % moder;
	}
	printf("%d\n", ret);
}

int main(){
	//freopen("data.txt", "r", stdin);
	//freopen("K.txt", "w", stdout);
	for (int i = 1; i <= 90; ++ i){
		add(mat[i][i], i * (90 - i));
		if (i <= 90 - 2){
			add(mat[i + 2][i], (90 - i) * (90 - i - 1) / 2);
		}
		if (i >= 3){
			add(mat[i - 2][i], i * (i - 1) / 2);
		}
		if (i <= 90 - 1){
			add(mat[i + 1][i], 90 - i);
		}
		if (i >= 2){
			add(mat[i - 1][i], i);
		}
	}
	std::vector <pii> vec;
	for (int i = 0; i <= 91; ++ i){
		matrix mat1 = mat;
		for (int j = 0; j <= 90; ++ j){
			for (int k = 0; k <= 90; ++ k){
				mat1[j][k] = (j == k ? i : 0) - mat1[j][k];
				mat1[j][k] += mat1[j][k] < 0 ? moder : 0;
			}
		}
		vec.push_back({i, mat1.det()});
	}
	p = poly::interpolation(vec, moder);
	trans[0] = matrix(90, 90);
	for (int i = 0; i <= 90; ++ i){
		trans[0][i][i] = 1;
	}
	for (int i = 1; i <= 90; ++ i){
		trans[i] = mat * trans[i - 1];
	}
	zzh[0].moder = moder;
	zzh[0].length = 1;
	zzh[0][1] = 1;
	for (int i = 1; i < 40; ++ i){
		zzh[i] = zzh[i - 1] * zzh[i - 1] % p;
	}
	int test;
	scanf("%d", &test);
	while (test --){
		solve();
	}
}
