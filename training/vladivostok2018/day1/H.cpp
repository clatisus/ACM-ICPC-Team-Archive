#include <bits/stdc++.h>

const int max_N = 21;
const int mod = 1234567891;

struct mat {
    int n, m, a[max_N][max_N];

    mat(int n = 0, int m = 0) : n(n), m(m) {
        memset(a, 0, sizeof(a));
    }

    friend mat operator * (const mat &a, const mat &b) {
        mat res(a.n, b.m);
        assert(a.m == b.n);
        for (int i = 0; i < res.n; ++i) {
            for (int j = 0; j < res.m; ++j) {
                int &tmp = res.a[i][j] = 0;
                for (int k = 0; k < a.m; ++k) {
                    tmp = (tmp + 1ll * a.a[i][k] * b.a[k][j]) % mod;
                }
            }
        }
        return res;
    }
};

int T, n, a[27], f[10][2], ans[10];

#define myHash(x, y) (((x) << 1) | (y))

void qpow(mat &x, mat &a, int k) {
    while (k) {
        if (k & 1) {
            a = x * a;
        }
        x = x * x;
        k >>= 1;
    }
}

void testCase() {
    scanf("%d", &n);
    for (int i = 0; i <= 26; ++i) {
        scanf("%d", a + i);
    }

    memset(f, 0, sizeof(f));
    
    for (int i = 0; i < 10; ++i) {
        if (i) {
            f[i][0] = (25ll * f[i - 1][0] + f[i - 1][1]) % mod;
        } else {
            f[i][0] = 1;
        }
        
        if (i) {
            for (int x = 1; x <= 26; ++x) {
                if (i >= a[x]) {
                    f[i][1] = (1ll * f[i][1] + f[i - a[x]][x == 'r' - 'a' + 1]) % mod;
                }
            }
        }
        if (i + 1 == a[0]) {
            f[i][1] = (f[i][1] + 1) % mod;
        }

        ans[i] = ((i ? ans[i - 1] : 0) + 25ll * f[i][0] + f[i][1]) % mod;
    }
    
    int res;
    if (n <= 10) {
        res = ans[n - 1];
    } else {
        mat F(21, 21);
        for (int x = 1; x <= 26; ++x) {
            ++F.a[myHash(9, 1)][myHash(10 - a[x], x == 'r' - 'a' + 1)];
            ++F.a[20][myHash(10 - a[x], x == 'r' - 'a' + 1)];
        }
        F.a[myHash(9, 0)][myHash(9, 0)] = 25;
        F.a[20][myHash(9, 0)] += 25 * 25;
        F.a[myHash(9, 0)][myHash(9, 1)] = 1;
        F.a[20][myHash(9, 1)] += 25;
        F.a[20][20] = 1;
        for (int i = 0; i < 9; ++i) {
            F.a[myHash(i, 0)][myHash(i + 1, 0)] = 1;
            F.a[myHash(i, 1)][myHash(i + 1, 1)] = 1;
        }
        mat A(21, 1);
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 2; ++j) {
                A.a[myHash(i, j)][0] = f[i][j];
            }
        }
        A.a[20][0] = ans[9];
        qpow(F, A, n - 10);
        res = A.a[20][0];
    }
    printf("%d\n", res);
}

int main() {
    scanf("%d", &T);
    while (T--) testCase();
    return 0;
}
