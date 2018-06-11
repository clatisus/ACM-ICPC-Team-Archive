#include <cstdio>
#include <set>
#include <cstring>
#include <algorithm>
using namespace std;
const int Q = 1e9 + 7;
char s0[10] = "CXIV" , s1[10] = "DXIV";

struct Matrix {
    int n , m , a[100][100];
    Matrix (int _n = 0 , int _m = 0) {
        n = _n , m = _m;
        memset(a , 0 , sizeof(a));
    }
    Matrix operator * (const Matrix &R) const {
        Matrix res(n , R.m);
        for (int i = 0 ; i < n ; ++ i) {
            for (int j = 0 ; j < m ; ++ j) {
                for (int k = 0 ; k < R.m ; ++ k) {
                    res.a[i][k] += (long long)a[i][j] * R.a[j][k] % Q;
                    res.a[i][k] %= Q;
                }
            }
        }
        return res;
    }
    int* operator [] (int x) {
        return a[x];
    }
};

Matrix P[30] , I;
int main() {

    P[0] = Matrix(100, 100);
    for (int i = 0 ; i < 100 ; ++ i) {
        for (int j = 0 ; j < 26 ; ++ j) {
            int x = i % 25 / 5 , y = i % 25 % 5 , mask = i / 25;

            if ('A' + j != s0[x]) {
                x = 0;
            }
            x += ('A' + j == s0[x]);
            if ('A' + j != s1[y]) {
                y = 0;
            }
            y += ('A' + j == s1[y]);

            if (y == 4 && (~mask & 1)) continue;
            if ((mask >> 0 & 1) && x == 4) continue;
            if ((mask >> 1 & 1) && y == 4) continue;
            mask |= (y == 4) << 1 | (x == 4);

            ++ P[0][i][mask * 25 + x * 5 + y];
        }
    }

    for (int k = 1 ; k < 30 ; ++ k) {
        P[k] = P[k - 1] * P[k - 1];
    }

    int T;
    scanf("%d" , &T);
    for (int i = 1 ; i <= T ; ++ i) {
        int n;
        scanf("%d" , &n);
        I = Matrix(1 , 100);
        I[0][0] = 1;
        for (int k = 0 ; k < 30 ; ++ k) {
            if (n >> k & 1) {
                I = I * P[k];
            }
        }
        int res = 0;
        for (int k = 0 ; k < 100 ; ++ k) {
            if (k / 25 == 3) {
                res += I[0][k];
                res %= Q;
            }
        }
        printf("Case #%d: %d\n" , i , res);
    }
}
