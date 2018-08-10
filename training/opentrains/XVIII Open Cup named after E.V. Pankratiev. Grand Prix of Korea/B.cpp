#include<bits/stdc++.h>

const int moder = 1e9 + 7;
const int N = 10010;
const int M = 110;

int grp[M][M];
int fac[N], inv[N];
int coe[M][M];
int a[N];

int powermod(int a, int exp){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * a * ret % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}


struct poly{
    int a[N];
    int len;

    poly():len(-1){memset(a, 0, sizeof(a));}
    poly(int len):len(len){memset(a, 0, sizeof(a));}

    int &operator [] (const int &n){return a[n];}

    poly operator + (const poly &p)const{
        poly ret(std::max(len, p.len));
        for (int i = 0; i <= ret.len; ++ i){
            ret.a[i] = a[i] + p.a[i];
            ret.a[i] -= ret.a[i] >= moder ? moder : 0;
        }
        return ret;
    }

    poly operator * (const poly &p)const{
        poly ret(len + p.len);
        for (int i = 0; i <= len; ++ i){
            for (int j = 0; j <= p.len; ++ j){
                ret.a[i + j] = (ret.a[i + j] + 1ll * a[i] * p.a[j]) % moder;
            }
        }
        return ret;
    }

    poly operator * (const int &p)const{
        poly ret(len);
        for (int i = 0; i <= len; ++ i){
            ret.a[i] = 1ll * a[i] * p % moder;
        }
        return ret;
    }

    poly operator / (const poly &p)const{
        poly ret(len - p.len), tmp = *this;
        for (int i = ret.len; i >= 0; -- i){
            ret.a[i] = 1ll * tmp.a[i + p.len] * powermod(p.a[p.len], moder - 2) % moder;
            for (int j = 0; j <= p.len; ++ j){
                tmp.a[i + j] = (tmp.a[i + j] - 1ll * ret.a[i] * p.a[j]) % moder;
                tmp.a[i + j] += tmp.a[i + j] < 0 ? moder : 0;
            }
        }
        return ret;
    }
};

int comb(int n, int m){
    return 1ll * fac[n] * inv[m] % moder * inv[n - m] % moder;
}

void init(){
    fac[0] = 1;
    for (int i = 1; i < N; ++ i){
        fac[i] = 1ll * fac[i - 1] * i % moder;
    }
    inv[N - 1] = powermod(fac[N - 1], moder - 2);
    for (int i = N - 1; i; -- i){
        inv[i - 1] = 1ll * inv[i] * i % moder;
    }
    grp[0][0] = 1;
    for (int i = 1; i < M; ++ i){
        for (int j = 1; j <= i; ++ j){
            for (int k = 0; k < i; ++ k){
                grp[i][j] = (grp[i][j] + 1ll * grp[k][j - 1] * (i - k)) % moder;
            }
        }
    }
    for (int i = 1; i < M; ++ i){
        for (int j = 1; j <= i; ++ j){
            for (int k = j; k <= i; ++ k){
                coe[j][i] = (coe[j][i] + (k - j & 1 ? -1ll : 1ll) * comb(k - 1, j - 1) * grp[i][k]) % moder;
            }
            coe[j][i] += coe[j][i] < 0 ? moder : 0;
            coe[j][i] = 1ll * coe[j][i] * inv[j] % moder;
        }
    }
}

int circ[M][M];

int solve(int n){
    poly dp(0);
    dp[0] = 1;
    for (int i = 1; i <= n; ++ i){
        poly p(a[i]);
        for (int j = 1; j <= a[i]; ++ j){
            p[j] = coe[j][a[i]];
        }
        dp = dp * p;
    }
    int ans = 0;
    for (int i = 1; i <= n; ++ i){
        poly p(a[i]);
        for (int j = 1; j <= a[i]; ++ j){
            p[j] = coe[j][a[i]];
        }
        poly tmp = dp / p;
        memset(circ, 0, sizeof(circ));
        circ[0][0] = 1;
        for (int j = 1; j <= a[i]; ++ j){
            for (int k = 1; k <= j; ++ k){
                circ[j][k] = coe[k][j];
            }
            for (int k = 0; k < j; ++ k){
                int sum = j - k << 1;
                for (int u = 1; u < j - k; ++ u){
                    sum = (sum + 1ll * u * (j - k - u)) % moder;
                }
                for (int u = 0; u <= k; ++ u){
                    circ[j][u] = (circ[j][u] - 1ll * sum * circ[k][u]) % moder;
                    circ[j][u] += circ[j][u] < 0 ? moder : 0;
                }
            }
        }
        p = poly(a[i]);
        for (int j = 0; j <= a[i]; ++ j){
            for (int k = 0; k <= j; ++ k){
                p[k] = (p[k] + 1ll * circ[j][k] * (a[i] - j) % moder * (a[i] - j)) % moder;
            }
        }
        p = tmp * p;
        for (int j = 0; j <= p.len; ++ j){
            ans = (ans + 1ll * fac[j] * p[j]) % moder;
        }
    }
    return ans;
}

int main(){
    init();
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i){
        scanf("%d", &a[i]);
    }
    if (n == 1){
        printf("%d\n", a[1]);
        return 0;
    }
    printf("%d\n", solve(n));
    return 0;
}
