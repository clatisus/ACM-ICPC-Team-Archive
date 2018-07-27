// 矩阵模板
// 尽量不要开太多临时变量，有爆空间的可能（虽然可能性基本趋于0吧orz） 
// 注释中记矩阵 *this 为 A 

#include<bits/stdc++.h>

class matrix{
private:
	static const int MAXN = 100000;
	constexpr static const double eps = 1e-12;
	static double **ptrpool, *dbpool;
	static int ptrsize, dbsize;
	
	double **a;
	int n, m;
	
	double **newptrs(int size){
		if (ptrsize < size){
			ptrpool = new double *[ptrsize = std::max((int) MAXN, size)];
		}
		return ptrpool + (ptrsize -= size);
	}
	double *newdbs(int size){
		if (dbsize < size){
			dbpool = new double[dbsize = std::max((int) MAXN, size)]();
		}
		return dbpool + (dbsize -= size);
	}
	
	void apply(int n, int m){
		if (!n || !m) return;
		a = newptrs(n);
		for (int i = 0; i < n; ++ i){
			a[i] = newdbs(m);
		}
		this -> n = n, this -> m = m;
	}
	
	void InitMatrix(const matrix &p){
		apply(p.n, p.m);
		for (int i = 0; i < n; ++ i){
			memcpy(a[i], p.a[i], sizeof(double) * m);
		}
	}
	
	void InitMatrix(matrix &&p){
		a = p.a, n = p.n, m = p.m;
	}

public:
	matrix():n(0), m(0){a = nullptr;}
	matrix(int n, int m){apply(n, m);}
	matrix(const matrix &p){InitMatrix(p);}
	matrix(matrix && p){InitMatrix(std::move(p));}
	double *operator [](int n){return a[n];}
	int getline(){return n;}
	int getcolumn(){return m;}
	void clear(){a = nullptr; n = m = 0;}
	
	void resize(int n, int m){
		if (this -> n == n && this -> m == m) return;
		apply(n, m);
	}
	
	matrix &operator = (const matrix &p){
		if (&p != this) InitMatrix(p);
		return *this;
	}
	
	matrix &operator = (matrix &&p){
		InitMatrix(std::move(p));
		return *this;
	}
	
	bool operator == (const matrix &p)const{
		if (n != p.n || m != p.m) return false;
		for (int i = 0; i < n; ++ i){
			for (int j = 0; j < m; ++ j){
				if (a[i][j] != p.a[i][j]) return false;
			}
		}
		return true;
	}
	
	matrix operator + (const matrix &p)const{
		if (n != p.n || m != p.m) assert(("Invalid matrix addition!", 0));
		matrix ret(n, m);
		for (int i = 0; i < n; ++ i){
			for (int j = 0; j < m; ++ j){
				ret.a[i][j] = a[i][j] + p.a[i][j];
			}
		}
		return ret;
	}
	
	matrix operator - (const matrix &p)const{
		if (n != p.n || m != p.m) assert(("Invalid matrix subtraction!", 0));
		matrix ret(n, m);
		for (int i = 0; i < n; ++ i){
			for (int j = 0; j < m; ++ j){
				ret.a[i][j] = a[i][j] - p.a[i][j];
			}
		}
		return ret;
	}
	
	matrix operator - ()const{
		matrix ret(n, m);
		for (int i = 0; i < n; ++ i){
			for (int j = 0; j < m; ++ j){
				ret.a[i][j] = -a[i][j];
			}
		}
		return ret;
	}
	
	matrix operator * (const matrix &p)const{
		if (m != p.n) assert(("Invalid matrix multiplication!", 0));
		matrix ret(n, p.m);
		for (int k = 0; k < m; ++ k){
			for (int i = 0; i < n; ++ i){
				for (int j = 0; j < p.m; ++ j){
					ret.a[i][j] += a[i][k] * p.a[k][j];
				}
			}
		}
		return ret;
	}
	
	matrix operator * (const double &p)const{
		matrix ret(n, m);
		for (int i = 0; i < n; ++ i){
			for (int j = 0; j < m; ++ j){
				ret.a[i][j] = p * a[i][j];
			}
		}
		return ret;
	}
	
	friend matrix operator * (const double &p, const matrix &mat){return mat * p;}
	matrix &operator += (const matrix &p){*this = *this + p; return *this;}
	matrix &operator -= (const matrix &p){*this = *this - p; return *this;}
	matrix &operator *= (const double &p){*this = *this * p; return *this;}
	
	// 返回 A 的 exp 次幂 
	template <typename T>
	matrix power(T exp)const{
		if (n != m) assert(("Invalid matrix power!", 0));
		matrix ret(matrixI(n)), aux(*this);
		for ( ; exp; exp >>= 1){
			if (exp & 1){
				ret = ret * aux;
			}
			aux = aux * aux;
		}
		return ret;
	}
	
	// 返回 I + A + A^2 + ... + A^exp 的结果 
	template <typename T>
	matrix powersum(T exp)const{
		if (n != m) assert(("Invalid matrix powersum!", 0));
		matrix ret(matrixI(n)), aux(*this), unit(ret);
		T exp1 = 1;
		for (++ exp; exp > 1; exp1 = exp1 << 1 | exp & 1, exp >>= 1)
			;
	    for ( ; exp1 > 1; exp1 >>= 1){
	    	ret = ret * (aux + unit);
	    	aux = aux * aux;
	    	if (exp1 & 1){
	    		ret += aux;
	    		aux = aux * *this;
	    	}
	    }
	    return ret;
	}
	
	// 返回 A 的行列式 
	double det()const{
		if (n != m) assert(("Invalid matrix det!", 0));
		matrix aux(*this);
		double ret = 1;
		for (int i = 0; i < aux.n; ++ i){
			double max = 0;
			int sit, sit1;
			for (int j = i; j < aux.n; ++ j){
				for (int k = i; k < aux.n; ++ k){
					double x = std::abs(aux.a[j][k]);
					if (x > max){
						sit = j, sit1 = k;
						max = x;
					}
				}
			}
			if (std::abs(max) < eps){
				ret = 0;
				break;
			}
			if (sit != i){
				for (int j = i; j < aux.n; ++ j){
					std::swap(aux.a[i][j], aux.a[sit][j]);
				}
				ret = -ret;
			}
			if (sit1 != i){
				for (int j = i; j < aux.n; ++ j){
					std::swap(aux.a[j][i], aux.a[j][sit1]);
				}
				ret = -ret;
			}
			for (int j = i + 1; j < aux.n; ++ j){
				double coe = aux.a[j][i] / aux.a[i][i];
				for (int k = i; k < aux.n; ++ k){
					aux.a[j][k] -= coe * aux.a[i][k];
				}
			}
		}
		for (int i = 0; i < aux.n; ++ i){
			ret *= aux.a[i][i];
		}
		return ret;
	}
	
	// 返回 AX = p 的通解，如无解返回行列为 0 的空矩阵，否则前 p.m 列为一个特解，后面若干个 p.m 列矩阵为通解的组成部分，即这些矩阵的任意线性组合加上特解仍为该方程的解 
	matrix gauss(const matrix &p)const{
		matrix aux1(*this), aux2(p);
		if (aux1.n != aux2.n) assert(("Invalid matrix equation!", 0));
		int cnt = 0;
		std::vector <int> aux;
		for (int i = 0; i < aux1.m; ++ i){
			int sit = -1;
			double max = 0;
			for (int j = cnt; j < aux1.n; ++ j){
				double x = std::abs(aux1.a[j][i]);
				if (x > max + eps){
					max = x;
					sit = j;
				}
			}
			if (!~sit){
				aux.push_back(i);
				continue;
			}
			double inv = 1 / aux1.a[sit][i];
			for (int j = i; j < aux1.m; ++ j){
				std::swap(aux1.a[cnt][j], aux1.a[sit][j]);
				aux1.a[cnt][j] *= inv;
			}
			for (int j = 0; j < aux2.m; ++ j){
				std::swap(aux2.a[cnt][j], aux2.a[sit][j]);
				aux2.a[cnt][j] *= inv;
			}
			for (int j = 0; j < aux1.n; ++ j){
				if (j == cnt) continue;
				double x = aux1.a[j][i];
				for (int k = i; k < aux1.m; ++ k){
					aux1.a[j][k] -= x * aux1.a[cnt][k];
				}
				for (int k = 0; k < aux2.m; ++ k){
					aux2.a[j][k] -= x * aux2.a[cnt][k];
				}
			}
			++ cnt;
		}
		for (int i = cnt; i < aux2.n; ++ i){
			for (int j = 0; j < aux2.m; ++ j){
				if (std::abs(aux2.a[i][j]) > eps) return matrix ();
			}
		}
		int sz = aux.size();
		matrix ret(aux1.m, sz + aux2.m);
		for (int i = 0; i < aux2.n; ++ i){
			for (int j = 0; j < aux2.m; ++ j){
				ret.a[i][j] = aux2.a[i][j];
			}
		}
		for (int i = 0; i < sz; ++ i){
			for (int j = 0; j < aux2.n; ++ j){
				if (j == aux[i]){
					ret.a[j][i + aux2.m] = 1.0;
				}
				else{
					ret.a[j][i + aux2.m] = -aux1.a[j][aux[i]];
				}
			}
		}
		return ret;
	}
	
	// 返回 A 的逆，如逆不存在返回行列为 0 的空矩阵 
	matrix inv()const{
		if (n != m) assert(("Invalid matrix inv!", 0));
		matrix aux(matrixI(n));
		aux = gauss(aux);
		if (!aux.n || aux.n != aux.m) return matrix ();
		return aux;
	}
	
	// 返回一个 n 阶单位阵 
	static matrix matrixI(int n){
		matrix ret(n, n);
		for (int i = 0; i < n; ++ i){
			ret[i][i] = 1;
		}
		return ret;
	}
	
	void write(){
		for (int i = 0; i < n; ++ i){
			for (int j = 0; j < m; ++ j){
				printf("%.10lf%c", a[i][j], " \n"[j == m - 1]);
			}
		}
	}
};

double **matrix::ptrpool = nullptr;
double *matrix::dbpool = nullptr;
int matrix::ptrsize = 0;
int matrix::dbsize = 0;

int main(){
	return 0;
}
