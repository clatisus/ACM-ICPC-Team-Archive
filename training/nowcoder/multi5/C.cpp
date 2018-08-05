#include<bits/stdc++.h>
 
const int moder = 998244353;
 
int powermod(int a, int exp){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * ret * a % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}
 
struct poly{
    static const int N = 20;
 
    int a[N];
 
    poly(){memset(a, 0, sizeof(a));}
 
    int &operator [](const int &n){
        return a[n];
    }
 
    poly operator +(const poly &p)const{
        poly ret = *this;
        for (int i = 0; i < N; ++ i){
            ret.a[i] += p.a[i];
            ret.a[i] -= ret.a[i] >= moder ? moder : 0;
        }
        return ret;
    }
 
    poly operator -(const poly &p)const{
        poly ret = *this;
        for (int i = 0; i < N; ++ i){
            ret.a[i] -= p.a[i];
            ret.a[i] += ret.a[i] < 0 ? moder : 0;
        }
        return ret;
    }
 
    poly operator *(const poly &p)const{
        poly ret;
        for (int i = 0; i < N; ++ i){
            if (!a[i]) continue;
            for (int j = 0; i + j < N; ++ j){
                ret.a[i + j] = (ret.a[i + j] + 1ll * a[i] * p.a[j]) % moder;
            }
        }
        return ret;
    }
};
 
const int N = 19;
const int M = 100;
 
poly f[1 << N], g[1 << N];
int bitcnt[1 << N], cnt[1 << N];
int fac[M], inv[M], ans[M], s[M][M];
 
void FMT(poly *f, int len, int type){
    for (int j = 0; j < len; ++ j){
        for (int i = 0; i < 1 << len; ++ i){
            if (i >> j & 1){
                if (type == 0){
                    f[i] = f[i] + f[i ^ 1 << j];
                }
                else{
                    f[i] = f[i] - f[i ^ 1 << j];
                }
            }
        }
    }
}
 
int main(){
    int time = clock();
    for (int i = 1; i < 1 << N; ++ i){
        bitcnt[i] = bitcnt[i >> 1] + (i & 1);
    }
    fac[0] = 1;
    for (int i = 1; i < M; ++ i){
        fac[i] = 1ll * fac[i - 1] * i % moder;
    }
    inv[M - 1] = powermod(fac[M - 1], moder - 2);
    for (int i = M - 1; i; -- i){
        inv[i - 1] = 1ll * inv[i] * i % moder;
    }
    s[0][0] = 1;
    for (int i = 1; i < M; ++ i){
        for (int j = 1; j <= i; ++ j){
            s[i][j] = (s[i - 1][j - 1] + 1ll * j * s[i - 1][j]) % moder;
        }
    }
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0, u, v; i < m; ++ i){
        scanf("%d%d", &u, &v);
        -- u, -- v;
        ++ cnt[1 << u | 1 << v];
    }
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < 1 << n; ++ j){
            if (j >> i & 1){
                cnt[j] += cnt[j ^ 1 << i];
            }
        }
    }
    for (int i = 0; i < 1 << n; ++ i){
        f[i][bitcnt[i]] = powermod(2, cnt[i]);
    }
    f[0][0] = 0;
    FMT(f, n, 0);
    g[0][0] = 1;
    FMT(g, n, 0);
    for (int j = 0; j < 1 << n; ++ j){
        for (int i = 1; i <= n; ++ i){
            g[j] = f[j] * g[j];
            ans[i] += (n - bitcnt[j] & 1 ? -1 : 1) * g[j][n];
            ans[i] -= ans[i] >= moder ? moder : 0;
            ans[i] += ans[i] < 0 ? moder : 0;
        }
    }
    int ret = 0;
    for (int i = n; i >= 1; -- i){
        ans[i] = 1ll * ans[i] * inv[i] % moder;
        for (int j = i + 1; j <= n; ++ j){
            ans[i] = (ans[i] - 1ll * ans[j] * s[j][i]) % moder;
        }
        ans[i] += ans[i] < 0 ? moder : 0;
        ret = (ret + 1ll * ans[i] * powermod(i, i - 1)) % moder;
    }
    printf("%d\n", ret);
    return 0;
}
