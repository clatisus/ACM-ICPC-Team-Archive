#include<bits/stdc++.h>

typedef long long ll;
const int moder = 1e9 + 7;
const int N = 10010;
const int M = 62;

int fac[N], inv[N], invf[N];

void init(){
    fac[0] = invf[0] = 1;
    for (int i = 1; i < N; ++ i){
        inv[i] = i == 1 ? 1 : moder - 1ll * (moder / i) * inv[moder % i] % moder;
        fac[i] = 1ll * fac[i - 1] * i % moder;
        invf[i] = 1ll * invf[i - 1] * inv[i] % moder;
    }
}

struct matrix{
    int n;
    int a[M][M];

    matrix():n(0){memset(a, 0, sizeof(a));}
    matrix(int n):n(n){memset(a, 0, sizeof(a));}

    int *operator [](const int &sit){return a[sit];}

    matrix operator *(const matrix &m)const{
        matrix ret(n);
        for (int k = 0; k < n; ++ k){
            for (int i = 0; i < n; ++ i){
                for (int j = 0; j < n; ++ j){
                    ret.a[i][j] = (ret.a[i][j] + 1ll * a[i][k] * m.a[k][j]) % moder;
                }
            }
        }
        return ret;
    }
    
    matrix power(ll exp)const{
        matrix ret(n), tmp = *this;
        for (int i = 0; i < n; ++ i){
            ret.a[i][i] = 1;
        }
        for ( ; exp > 0; exp >>= 1){
            if (exp & 1){
                ret = ret * tmp;
            }
            tmp = tmp * tmp;
        }
        return ret;
    }
};

int interpolation(std::vector <int> &vec, int x){
    int n = vec.size() - 1;
    if (x >= 0 && x <= n) return vec[x];
    std::vector <int> pre(n + 1), suf(n + 1);
    pre[0] = suf[n] = 1;
    for (int i = 1; i <= n; ++ i){
        pre[i] = 1ll * pre[i - 1] * (x - i + 1) % moder;
        pre[i] += pre[i] < 0 ? moder : 0;
    }
    for (int i = n - 1; i >= 0; -- i){
        suf[i] = 1ll * suf[i + 1] * (x - i - 1) % moder;
        suf[i] += suf[i] < 0 ? moder : 0;
    }
    int ans = 0;
    for (int i = 0; i <= n; ++ i){
        ans = (ans + ((n - i) & 1 ? -1ll : 1ll) * vec[i] * pre[i] % moder * suf[i] % moder * invf[i] % moder * invf[n - i]) % moder;
    }
    ans += ans < 0 ? moder : 0;
    return ans;
}

std::vector <int> vec[N];

void solve(ll n){
    for (int i = 1; i <= M; ++ i){
        vec[i].clear();
        int now = (n & ((1ll << i) - 1)) >> (i - 1);
        int tot = 0;
        for (int j = 0; j <= i; ++ j){
            tot += interpolation(vec[i - 1], now);
            tot -= tot >= moder ? moder : 0;
            vec[i].push_back(tot);
            now += 2;
        }
    }
}

int main(){
    init();
    vec[0].push_back(1);
    ll n, m;
    scanf("%lld%lld", &n, &m);
    matrix mat(M);
    for (int i = 0; i < M - 1; ++ i){
        mat[i][i + 1] = 1;
    }
    solve(n << 1);
    for (int i = 1; i <= M; ++ i){
        mat[M - 1][M - i] = interpolation(vec[i], (n << 1 >> i) % moder);
    }
    solve(n);
    for (int i = 1; i <= M; ++ i){
        mat[M - 1][M - i] -= interpolation(vec[i], (n >> i) % moder);
        mat[M - 1][M - i] += mat[M - 1][M - i] < 0 ? moder : 0;
    }
    for (int i = 0; i < M - 1; ++ i){
        mat[M - 1][i] -= mat[M - 1][i + 1];
        mat[M - 1][i] += mat[M - 1][i] < 0 ? moder : 0;
    }
    mat = mat.power(m);
    printf("%d\n", mat[M - 1][M - 1]);
    return 0;
}
