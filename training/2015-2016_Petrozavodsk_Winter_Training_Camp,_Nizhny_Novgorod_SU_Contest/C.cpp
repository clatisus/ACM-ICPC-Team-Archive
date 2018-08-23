#include<bits/stdc++.h>

typedef long long ll;
const int MAX = 20;
const int moder = 998244353;
const int root = 3;
const int invroot = (moder + 1) / root;

int w[2][1 << MAX];

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

void init(){
    w[0][0] = w[1][0] = 1;
    w[0][1] = powermod(root, (moder - 1) >> MAX);
    for (int i = 2; i < (1 << MAX); ++ i){
        w[0][i] = 1ll * w[0][i - 1] * w[0][1] % moder;
    }
    for (int i = 1; i < (1 << MAX); ++ i){
        w[1][(1 << MAX) - i] = w[0][i];
    }
}

void NTT(std::vector <int> &a, int len, int type){
    for (int i = 1, j = 0; i < len - 1; ++ i){
        for (int s = len; j ^= (s >>= 1), ~j & s; )
            ;
        if (i < j){
            std::swap(a[i], a[j]);
        }
    }
    for (int i = 2, d = 1; i <= len; i <<= 1, ++ d){
        for (int j = 0; j < len; j += i){
            auto u = a.begin() + j;
            for (int k = 0; k < i / 2; ++ k){
                int t = 1ll * w[type][k << (MAX - d)] * u[k + i / 2] % moder;
                u[k + i / 2] = u[k] - t + (u[k] - t < 0 ? moder : 0);
                u[k] += t; u[k] -= u[k] >= moder ? moder : 0;
            }
        }
    }
    if (type == 0) return;
    int inv = powermod(len, moder - 2);
    for (int i = 0; i < len; ++ i){
        a[i] = 1ll * a[i] * inv % moder;
    }
}

struct poly{
    std::vector <int> a;
    int len;

    poly():len(-1){}
    poly(int len):len(len){a.resize(len + 1);}
    poly(const poly &p, int len):len(len){
        a.resize(len + 1);
        for (int i = 0; i <= len; ++ i){
            a[i] = i > p.len ? 0 : p.a[i];
        }
    }

    int &operator [](int n){return a[n];}

    poly operator *(const poly &p)const{
        if (!~len || !~p.len) return poly(-1);
        int n = len + p.len;
        int lenret = 1;
        for ( ; lenret <= n; lenret <<= 1)
            ;
        poly ret(*this, lenret);
        std::vector <int> aux(lenret);
        std::copy(p.a.begin(), p.a.begin() + p.len + 1, aux.begin());
        NTT(ret.a, lenret, 0);
        NTT(aux, lenret, 0);
        for (int i = 0; i < lenret; ++ i){
            ret.a[i] = 1ll * ret.a[i] * aux[i] % moder;
        }
        NTT(ret.a, lenret, 1);
        ret.len = n;
        return ret;
    }
};

const int N = 200010;
const int M = 5;

char s[N], t[N];
int p[N];
int ans[M][M][N];

int main(){
    init();
    scanf("%s%s", s, t);
    int n = strlen(s);
    std::reverse(t, t + n);
    for (int i = 0; i < M; ++ i){
        for (int j = 0; j < M; ++ j){
            poly p1(n - 1), p2(n - 1);
            for (int k = 0; k < n; ++ k){
                p1[k] = s[k] == 'A' + i;
            }/*
            for (int k = 0; k <= n - 1; ++ k){
                printf("%d%c", p1[k], " \n"[k == n - 1]);
            }*/
            for (int k = 0; k < n; ++ k){
                p2[k] = t[k] == 'a' + j;
            }/*
            for (int k = 0; k <= n - 1; ++ k){
                printf("%d%c", p2[k], " \n"[k == n - 1]);
            }*/
            p1 = p1 * p2;/*
            for (int k = 0; k <= 2 * n - 2; ++ k){
                printf("%d%c", p1[k], " \n"[k == 2 * n - 2]);
            }*/
            for (int k = 0; k <= 2 * n - 2; ++ k){
                ans[i][j][k % n] += p1[k];
            }
        }
    }
    for (int i = 0; i < M; ++ i){
        p[i] = i;
    }
    int max = 0;
    do{
        //p[0] = 1, p[1] = 2, p[2] = 4, p[3] = 0, p[4] = 3;
        for (int j = 0; j < n; ++ j){
            int tot = 0;
            for (int i = 0; i < M; ++ i){
                tot += ans[i][p[i]][j];
            }
            max = std::max(max, tot);
        }
        //break;
    }
    while (std::next_permutation(p, p + M));
    printf("%d\n", n - max);
    return 0;
}

