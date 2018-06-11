#include<bits/stdc++.h>

const int N = 20010;
const int MAX = 1 << 15;
const int moder = 1e9 + 7;

int powermod(int a, int exp, int moder){
	int ret = 1;
	for ( ; exp > 0; exp >>= 1){
		if (exp & 1) ret = 1ll * ret * a % moder;
		a = 1ll * a * a % moder;
	}
	return ret;
}

struct matrix{
	static const int N = 32;
	
	int a[N][N];
	int n, m, moder;
	
	matrix():n(0), m(0), moder(0){memset(a, 0, sizeof(a));}
	matrix(int n, int m, int moder):n(n), m(m), moder(moder){memset(a, 0, sizeof(a));}
	
	int *operator [](int i){return a[i];}
	
	matrix merge(const matrix &mat)const{
		if (n == m){
			return *this;
		}
		if (mat.n == m){
			return mat;
		}
		matrix ret = *this, other = mat;
		if (ret.n < other.n) std::swap(ret, other);
		for (int i = 0; i < m; ++ i){
			if (!other.a[i][i]) continue;
			for (int j = i; j < m; ++ j){
				if (!other.a[i][j]) continue;
				if (!ret.a[j][j]){
					int inv = powermod(other.a[i][j], moder - 2, moder);
					for (int k = j; k < m; ++ k){
						ret.a[j][k] = other.a[i][k] * inv % moder;
					}
					++ ret.n;
					break;
				}
				int coe = other.a[i][j];
				for (int k = j; k < m; ++ k){
					other.a[i][k] = (other.a[i][k] - coe * ret.a[j][k]) % moder;
					other.a[i][k] += other.a[i][k] < 0 ? moder : 0;
				}
			}
		}
		return ret;
	}
};

matrix readmat(int d, int moder){
	matrix mat(0, d, moder);
	int sit = -1;
	for (int i = 0; i < d; ++ i){
		scanf("%d", &mat[0][i]);
	}
	for (int i = 0; i < d; ++ i){
		if (mat[0][i]){
			sit = i;
			break;
		}
	}
	if (sit == -1) return mat;
	for (int i = sit; i < d; ++ i){
		std::swap(mat[0][i], mat[sit][i]);
	}
	int inv = powermod(mat[sit][sit], moder - 2, moder);
	for (int i = sit; i < d; ++ i){
		mat[sit][i] = mat[sit][i] * inv % moder;
	}
	mat.n = 1;
	return mat;
}

matrix seg[N + MAX];

void pull(int sit){
	if ((sit << 1 | 1) >= N + MAX) return;
	seg[sit] = seg[sit << 1].merge(seg[sit << 1 | 1]);
}

void add(int sit, matrix value){
	seg[sit + MAX] = value;
	for (sit += MAX, sit >>= 1; sit; sit >>= 1){
		pull(sit);
	}
}

matrix query(int l, int r, int d, int p){
	matrix ret(0, d, p);
	for (l += MAX, r += MAX + 1; l < r; l >>= 1, r >>= 1){
		if (l & 1) ret = ret.merge(seg[l ++]);
		if (ret.n == ret.m) return ret;
		if (r & 1) ret = ret.merge(seg[-- r]);
		if (ret.n == ret.m) return ret;
	}
	return ret;
}

void solve(){
	int n, d, p, q;
	scanf("%d%d%d%d", &n, &d, &p, &q);
	for (int i = 0; i < MAX + N; ++ i){
		seg[i].m = d;
		seg[i].moder = p;
	}
	for (int i = 0; i < n; ++ i){
		seg[i + MAX] = readmat(d, p);
	}
	for (int i = MAX - 1; i; -- i){
		pull(i);
	}
	while (q --){
		int type;
		scanf("%d", &type);
		if (type == 1){
			int k;
			scanf("%d", &k);
			-- k;
			matrix mat = readmat(d, p);
			add(k, mat);
		}
		else{
			int l1, r1, l2, r2;
			scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
			-- l1, -- r1, -- l2, -- r2;
			matrix mat1 = query(l1, r1, d, p);
			matrix mat2 = query(l2, r2, d, p);
			int ans = (powermod(p, mat1.n, moder) + powermod(p, mat2.n, moder) - 2 * powermod(p, mat1.n + mat2.n - mat1.merge(mat2).n, moder)) % moder;
			ans += ans < 0 ? moder : 0;
			printf("%d\n", ans);
		}
	}
}

int main(){
	int test;
	scanf("%d", &test);
	while (test --){
		solve();
	}
	return 0;
}
