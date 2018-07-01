#include<bits/stdc++.h>

typedef long long ll;

const int moder = 998244353;
const int root = 3;
const int invroot = 332748118;

int powermod(int a, int exp, int moder){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * a * ret % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

const int MAX = 1 << 18;

int w[2][MAX];

void NTT(int *a, int length, int type, int moder, int root){
    if (length == 1) return;
    int len = -1;
    for (int x = length; x; ++ len, x >>= 1);
    for (int i = 1, j = 0; i < length - 1; ++ i){
        for (int s = length; j ^= s >>= 1, ~j & s; )
            ;
        if (i < j){
            std::swap(a[i], a[j]);
        }
    }
    for (int i = 1; i <= len; ++ i){
        for (int j = 0, szk = 1 << i - 1, szw = MAX >> i; j < length; j += 1 << i){
            for (int k = j, noww = 0; k < j + szk; ++ k, noww += szw){
                int s = a[k], t = 1ll * w[type == 1 ? 1 : 0][noww] * a[k + szk] % moder;
                a[k] = s + t >= moder ? s + t - moder : s + t;
                a[k + szk] = s - t < 0 ? s - t + moder : s - t;
            }
        }
    }
    if (type == 1) return;
    int inv = powermod(length, moder - 2, moder);
    for (int i = 0; i < length; ++ i){
        a[i] = (ll) a[i] * inv % moder;
    }
}

int aux2[MAX], aux1[MAX], c[MAX];

void mult(int *a, int *b, int *c, int lena, int lenb, int &lenc){
    int n = lena + lenb;
    lenc = 1;
    for ( ; lenc <= n; lenc <<= 1)
        ;
    for (int i = lena + 1; i < lenc; ++ i){
        a[i] = 0;
    }
    for (int j = lenb + 1; j < lenc; ++ j){
        b[j] = 0;
    }
    NTT(a, lenc, 1, moder, root);
    NTT(b, lenc, 1, moder, root);
    for (int i = 0; i < lenc; ++ i){
        c[i] = 1ll * a[i] * b[i] % moder;
    }
    NTT(c, lenc, -1, moder, invroot);
    lenc = lena + lenb;
}

const int N = 100010;

std::vector <int> vec[N];
int a[N], b[N];
int fac[N], inv[N], sz[N];

int comb(int n, int m){
    return 1ll * fac[n] * inv[m] % moder * inv[n - m] % moder;
}

typedef std::pair <int, int> pii;

void solve(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
        scanf("%d%d", &a[i], &b[i]);
    }
    std::priority_queue <pii> pq;
    int sum = 0;
    for (int i = 0; i < n; ++ i){
        vec[i].resize(std::min(a[i], b[i]) + 1);
        for (int j = 0; j <= std::min(a[i], b[i]); ++ j){
            vec[i][j] = 1ll * comb(a[i], j) * comb(b[i], j) % moder * fac[j] % moder;
        }
        sz[i] = std::min(a[i], b[i]);
        pq.push({-sz[i], i});
        sum += a[i];
    }
    while (pq.size() >= 2){
        pii p1 = pq.top();
        pq.pop();
        pii p2 = pq.top();
        pq.pop();
        int sit1 = p1.second, sit2 = p2.second;
        for (int i = 0; i <= sz[sit1]; ++ i){
            aux1[i] = vec[sit1][i];
        }
        for (int i = 0; i <= sz[sit2]; ++ i){
            aux2[i] = vec[sit2][i];
        }
        int _sz;
        mult(aux1, aux2, c, sz[sit1], sz[sit2], _sz);
        vec[sit1].resize(_sz + 1);
        for (int i = 0; i <= _sz; ++ i){
            vec[sit1][i] = c[i];
        }
        sz[sit1] = _sz;
        pq.push({-sz[sit1], sit1});
    }
    int ans = 0;
    pii p = pq.top();
    int sit = p.second;
    for (int i = 0; i <= sz[sit]; ++ i){
        ans = (ans + (i & 1 ? -1ll : 1ll) * vec[sit][i] * fac[sum - i]) % moder;
        ans += ans < 0 ? moder : 0;
    }
    printf("%d\n", ans);
}

int main(){
    //freopen("input.txt", "r", stdin);
    w[1][0] = w[0][0] = 1, w[1][1] = powermod(root, (moder - 1) / MAX, moder);
    w[0][1] = powermod(invroot, (moder - 1) / MAX, moder);
    for (int i = 2; i < MAX; ++ i){
        for (int j = 0; j < 2; ++ j){
            w[j][i] = 1ll * w[j][i - 1] * w[j][1] % moder;
        }
    }
    fac[0] = 1;
    for (int i = 1; i < N; ++ i){
        fac[i] = 1ll * fac[i - 1] * i % moder;
    }
    inv[N - 1] = powermod(fac[N - 1], moder - 2, moder);
    for (int i = N - 1; i; -- i){
        inv[i - 1] = 1ll * inv[i] * i % moder;
    }
    int test;
    scanf("%d", &test);
    while (test --){
        solve();
    }
    return 0;
}
