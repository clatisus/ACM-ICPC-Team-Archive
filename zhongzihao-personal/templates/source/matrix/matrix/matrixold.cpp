// 旧版矩阵模板
// 使用方法参见矩阵模板

#include<bits/stdc++.h>
#define ll long long

class matrix{
private:
    static const int N = 200;
    constexpr static const double eps = 1e-12;
    
    double a[N][N];
    int n, m;

public:
    matrix():n(0), m(0){
    	int x = 100 > N ? 100 : N;
        memset(a, 0, sizeof(a));
    }
    
    matrix(int n, int m):n(n), m(m){
        memset(a, 0, sizeof(a));
    }
    
    void clear(){
        for (int i = 0; i < n; ++ i){
            memset(a[i], 0, sizeof(double) * m);
        }
        n = m = 0;
    }
    
    void assign(matrix &p){
        clear();
        for (int i = 0; i < p.n; ++ i){
            memcpy(a[i], p.a[i], sizeof(double) * p.m);
        }
        n = p.n, m = p.m;    
    }
    
    void setvalue(int x, int y, double value){
        if (x < 0 || x >= n || y < 0 || y >= m) assert(("Invalid matrix assignment!", 0));
        a[x][y] = value;
    }
    
    double getvalue(int x, int y){
        if (x < 0 || x >= n || y < 0 || y >= m) assert(("Invalid matrix query!", 0));
        return a[x][y];
    }
    
    void resize(int n, int m){
        clear();
        this -> n = n;
        this -> m = m;
    }
    
    int getline(){return n;}
    int getcolumn(){return m;} 
    
    bool equal(matrix &p){
        if (n != p.n || m != p.m) return false;
        for (int i = 0; i < n; ++ i){
            for (int j = 0; j < m; ++ j){
                if (a[i][j] != p.a[i][j]) return false;
            }
        }
        return true;
    }
    
    void write(){
        for (int i = 0; i < n; ++ i){
            for (int j = 0; j < m; ++ j){
                printf("%.10lf%c", a[i][j], " \n"[j == m - 1]);
            }
        }
    }
    
    void add(matrix &p){
        if (n != p.n || m != p.m) assert(("Invalid matrix addition!", 0));
        for (int i = 0; i < n; ++ i){
            for (int j = 0; j < m; ++ j){
                a[i][j] += p.a[i][j];
            }
        }
    }
    
    void minus(matrix &p){
        if (n != p.n || m != p.m) assert(("Invalid matrix subtraction!", 0));
        for (int i = 0; i < n; ++ i){
            for (int j = 0; j < m; ++ j){
                a[i][j] -= p.a[i][j];
            }
        }
    }
    
    void neg(){
        for (int i = 0; i < n; ++ i){
            for (int j = 0; j < m; ++ j){
                a[i][j] = -a[i][j];
            }
        }
    }
    
    void mult(matrix &p){
        static matrix aux;
        if (m != p.n) assert(("Invalid matrix multiplication!", 0));
        aux.clear();
        aux.n = n, aux.m = p.m;
        for (int k = 0; k < m; ++ k){
            for (int i = 0; i < n; ++ i){
                for (int j = 0; j < p.m; ++ j){
                    aux.a[i][j] += a[i][k] * p.a[k][j];
                }
            }
        }
        assign(aux);
    }
    
    void mult(double p){
        for (int i = 0; i < n; ++ i){
            for (int j = 0; j < m; ++ j){
                a[i][j] *= p;
            }
        }
    }
    
    void matrixI(int n){
        clear();
        this -> n = this -> m = n;
        for (int i = 0; i < n; ++ i){
            a[i][i] = 1;
        }
    }
    
    template <typename T>
    void power(T exp){
        static matrix aux;
        if (n != m) assert(("Invalid matrix power!", 0));
        aux.matrixI(n);
        for ( ; exp; exp >>= 1){
            if (exp & 1){
                aux.mult(*this);
            }
            mult(*this);
        }
        assign(aux);
    }
    
    template <typename T>
    void powersum(T exp){
        static matrix aux, aux1;
        if (n != m) assert(("Invalid matrix powersum!", 0));
        aux.matrixI(n);
        aux1.assign(*this);
        T exp1 = 1;
        for (++ exp; exp > 1; exp1 = exp1 << 1 | exp & 1, exp >>= 1)
            ;
        for ( ; exp1 > 1; exp1 >>= 1){
            for (int i = 0; i < n; ++ i){
                aux1.a[i][i] += 1;
            }
            aux.mult(aux1);
            for (int i = 0; i < n; ++ i){
                aux1.a[i][i] -= 1;
            }
            aux1.mult(aux1);
            if (exp1 & 1){
                aux.add(aux1);
                aux1.mult(*this);
            }
        }
        assign(aux);
    }
    
    double det(){
        static matrix aux;
        if (n != m) assert(("Invalid matrix det!", 0));
        aux.assign(*this);
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
            ret = ret * aux.a[i][i];
        }
        return ret;
    }
    
    void gauss(matrix &p, matrix &ans){
        static int aux[N];
        static matrix aux1, aux2;
        aux1.assign(*this), aux2.assign(p);
        if (aux1.n != aux2.n) assert(("Invalid matrix equation!", 0));
        ans.clear();
        for (int i = 0; i < aux1.n; ++ i){
            aux[i] = i;
        }
        int zero = aux1.n;
        for (int i = 0; i < aux1.n; ++ i){
            double max = 0;
            int sit, sit1;
            for (int j = i; j < aux1.n; ++ j){
                for (int k = i; k < aux1.m; ++ k){
                    double x = std::abs(aux1.a[j][k]);
                    if (x > max){
                        sit = j, sit1 = k;
                        max = x;
                    }
                }
            }
            if (std::abs(max) < eps){
                zero = i;
                break;
            }
            if (sit1 != i){
                std::swap(aux[i], aux[sit1]);
                for (int j = 0; j < aux1.n; ++ j){
                    std::swap(aux1.a[j][i], aux1.a[j][sit1]);
                }
            }
            double div = aux1.a[sit][i];
            for (int j = i; j < aux1.m; ++ j){
                std::swap(aux1.a[i][j], aux1.a[sit][j]);
                aux1.a[i][j] /= div;
            }
            for (int j = 0; j < aux2.m; ++ j){
                std::swap(aux2.a[i][j], aux2.a[sit][j]);
                aux2.a[i][j] /= div;
            }
            for (int j = 0; j < aux1.n; ++ j){
                if (j == i) continue;
                double coe = aux1.a[j][i];
                for (int k = i; k < aux1.m; ++ k){
                    aux1.a[j][k] -= coe * aux1.a[i][k];
                }
                for (int k = 0; k < aux2.m; ++ k){
                    aux2.a[j][k] -= coe * aux2.a[i][k];
                }
            }
        }
        for (int i = zero; i < aux1.n; ++ i){
            for (int j = 0; j < aux2.m; ++ j){
                if (std::abs(aux2.a[i][j]) > eps) return;
            }
        }
        ans.resize(aux1.m, (n - zero + 1) * aux2.m);
        for (int i = 0; i < zero; ++ i){
            memcpy(ans.a[aux[i]], aux2.a[i], sizeof(double) * aux2.m);
            for (int j = zero; j < aux1.m; ++ j){
                for (int k = 0; k < aux2.m; ++ k){
                    ans.a[aux[i]][(j - zero + 1) * aux2.m + k] = -aux1.a[i][j];
                }
            }
        }
        for (int i = zero; i < aux1.n; ++ i){
            for (int j = 0; j < aux2.m; ++ j){
                ans.a[aux[i]][(i - zero + 1) + j] = 1;
            }
        }
    }
    
    void inv(){
        static matrix aux;
        if (n != m) assert(("Invalid matrix inv!", 0));
        aux.matrixI(n);
        gauss(aux, *this);
    }
};

int main(){
	return 0;
}
