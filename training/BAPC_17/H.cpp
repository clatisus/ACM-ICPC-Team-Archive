#include<bits/stdc++.h>

typedef long long ll;

inline int sig(ll x){return (x > 0) - (x < 0);}

struct P{
    ll x, y;
    P(ll x = 0, ll y = 0):x(x), y(y){}

    P operator + (const P &p)const{return P(x + p.x, y + p.y);}
    P operator - (const P &p)const{return P(x - p.x, y - p.y);}
    P operator * (const ll &p)const{return P(x * p, y * p);}
    ll operator ^ (const P &p)const{return p.x * y - p.y * x;}
    ll operator % (const P &p)const{return x * p.x + y * p.y;}

    bool operator < (const P &p)const{
        if (x != p.x) return x < p.x;
        return y < p.y;
    }

    bool operator == (const P &p)const{
        return x == p.x && y == p.y;
    }

    void read(){
        scanf("%lld%lld", &x, &y);
    }
};

bool crsSS(P p1, P p2, P q1, P q2){
    ll c1 = (p2 - p1) ^ (q1 - p1);
    ll c2 = (p2 - p1) ^ (q2 - p1);
    if (!c1 && !c2){
        if (p2 < p1) std::swap(p1, p2);
        if (q2 < q1) std::swap(q1, q2);
        P max = std::max(p1, q1);
        P min = std::min(p2, q2);
        return max < min || max == min;
    }
    ll c3 = (q2 - q1) ^ (p1 - q1);
    ll c4 = (q2 - q1) ^ (p2 - q1);
    return sig(c1) * sig(c2) <= 0 && sig(c3) * sig(c4) <= 0;
}

const int N = 1010;

P p1[N], p2[N];
int fa[N];

int find(int u){
    return fa[u] == u ? u : (fa[u] = find(fa[u]));
}

void unite(int u, int v){
    u = find(u), v = find(v);
    if (u == v) return;
    fa[u] = v;
}

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
        p1[i].read(), p2[i].read();
    }
    int point = 0;
    for (int i = 1; i < N; ++ i){
        fa[i] = i;
    }
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < i; ++ j){
            if (crsSS(p1[i], p2[i], p1[j], p2[j])){
                ++ point;
                unite(i, j);
            }
        }
    }
    int cnt = 0;
    for (int i = 0; i < n; ++ i){
        if (fa[i] == i){
            ++ cnt;
        }
    }
    printf("%d\n", cnt - n + point);
    return 0;
}

/*
6
0 0 1 0
1 0 2 0
2 0 2 1
2 1 1 1
1 1 0 1
0 1 0 0

2
0 0 4 0
2 0 6 0

8
-2 0 -1 0
-1 0 -1 1
-1 1 -2 1
-2 1 -2 0
0 0 1 0
1 0 1 1
1 1 0 1
0 1 0 0

3
0 0 1 0
2 0 3 0
0 0 3 0
*/

