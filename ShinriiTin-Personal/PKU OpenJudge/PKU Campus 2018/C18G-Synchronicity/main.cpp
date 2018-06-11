/*
用线段树维护区间在mod P意义下的极大线性无关组
对于修改，改一条链，复杂度$O(D^3\log{N})$
对于询问，先求出区间[l1, r1]的极大线性无关组v1，区间[l2, r2]的极大线性无关组v2
则其分别可以表示出$P^{|v1|}$和$P^{|v2|}$种向量
然后将v1和v2 merge得到v3(相当于联立方程组求解)，则v1和v2都能表示出的向量数量为$P^{|v1|+|v2|-|v3|}$ 
时间复杂度$O(D^3(N+Q)\log{N})$，空间复杂度$O(D^2N)$ 
*/ 
#include <bits/stdc++.h>

template <class T> inline void read(T&x){
    static char buf[233], *stop;
    scanf("%s", buf);
    x = strtod(buf, &stop);
}

using VI = std::vector<int>;
using DATA = std::vector<VI>;

#define SIZ(x) ((int)((x).size()))

const int max_N = 20000 + 21;
const int mod = (int)1e9 + 7;

#define ls(x) ((x)<<1)
#define rs(x) (ls(x)|1)
#define mid ((l+r)>>1)
#define lch ls(x),l,mid
#define rch rs(x),mid+1,r

int T, N, D, P, Q, inv[max_N], pos[max_N], pw[40 + 21];

VI a[max_N];

DATA seg[max_N*4];

inline bool gauss(VI x, VI&y){
    int i = 0; while(!x[i]) ++ i;
    if(!y[i]) return true;
    for(int j=i+1;j<D;++j){
        y[j] = (y[j] - x[j]*y[i]%P + P)%P;
    }
    y[i] = 0;
    for(auto&a:y)
        if(a) return true;
    return false;
}

inline void insert(DATA&a, VI v){
    bool flag = false;
    for(auto&x:v) if(x) flag = true;
    if(!flag) return;

    for(auto&x:a)
        if(!gauss(x, v)){
            return;
        }

    int i = 0; while(!v[i]) ++ i;
    for(int j=i+1;j<D;++j){
        v[j] = inv[v[i]] * v[j] % P;
    }
    v[i] = 1;

    for(auto&x:a) gauss(v, x);

    a.push_back(v);
}

inline DATA merge(const DATA&a, const DATA&b){
    DATA res;
    if(SIZ(a) < SIZ(b)){
        res = b;
        for(auto&v:a){
            if(SIZ(res) == D) break;
            insert(res, v);
        }
    }
    else{
        res = a;
        for(auto&v:b){
            if(SIZ(res) == D) break;
            insert(res, v);
        }
    }
    return res;
}

inline void update(int x){
    seg[x] = merge(seg[ls(x)], seg[rs(x)]);
}

void data_init(int x, const VI&v){
    DATA().swap(seg[x]);
    insert(seg[x], v);
}

void build(int x, int l, int r){
    if(l == r){
        pos[l] = x;
        data_init(x, a[l]);
    }
    else{
        build(lch), build(rch);
        update(x);
    }
}

inline void modify(int k, const VI&v){
    data_init(k = pos[k], v);
    while(k >>= 1) update(k);
}

inline void modify(){
    int k; VI v;
    read(k);
    for(int i=0,x;i<D;++i){
        read(x);
        v.push_back(x);
    }
    modify(k, v);
}

int Ql, Qr;

DATA Qv;

void query(int x, int l, int r){
    if(Ql<=l && r<=Qr){
        Qv = merge(Qv, seg[x]);
    }
    else{
        if(Ql<=mid) query(lch);
        if(Qr> mid) query(rch);
    }
}

inline void query(){
    int a, b, c, l1, r1, l2, r2;
    DATA v1, v2, v3;

    read(l1), read(r1), read(l2), read(r2);

    Ql = l1, Qr = r1, DATA().swap(Qv), query(1, 1, N), v1 = Qv;
    Ql = l2, Qr = r2, DATA().swap(Qv), query(1, 1, N), v2 = Qv;
    v3 = merge(v1, v2);

    int n =SIZ(v1), m =SIZ(v2);

    a = pw[n], b = pw[m], c = 2*pw[n+m-SIZ(v3)]%mod;

    printf("%d\n", ((a+b)%mod-c+mod)%mod);
}

void testCase(){
    read(N), read(D), read(P), read(Q);
    pw[0] = 1;
    for(int i=1;i<=D;++i){
        pw[i] = 1ll * pw[i-1] * P % mod;
    }
    for(int i=1;i<=N;++i){
        VI().swap(a[i]);
        for(int j=0,x;j<D;++j){
            read(x);
            a[i].push_back(x);
        }
    }
    inv[1] = 1;
    for(int i=2;i<P;++i){
        inv[i] = (P/i) * inv[P%i] % P;
        if(inv[i]) inv[i] = P - inv[i];
    }
    build(1, 1, N);
    while(Q --){
        int opt; read(opt);
        if(opt == 1) modify();
        else query();
    }
}

//#define local

int main(){
#ifdef local
    freopen("data.in", "r", stdin);
#endif

    read(T);
    while(T --) testCase();
    return 0;
}
