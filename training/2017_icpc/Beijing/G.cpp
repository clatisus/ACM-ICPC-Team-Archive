#include<bits/stdc++.h>

typedef long double ld;

const int N = 410;
const ld eps = 1e-9;
const ld INF = 1e100;

inline int sig(ld x){return (x > eps) - (x < -eps);}

char s[N][N];
std::vector <int> e[N];
int dis[N];
bool vis[N];
int n;

int encode(int x, int y){
    return x * n + y;
}

bool check(int x, int y){
    return x >= 0 && x < n && y >= 0 && y < n;
}

struct P{
    ld x, y;

    explicit P(ld x = 0, ld y = 0):x(x), y(y){}

    P operator + (const P &p)const{return P(x + p.x, y + p.y);}
    P operator - (const P &p)const{return P(x - p.x, y - p.y);}
    P operator * (const ld &p)const{return P(x * p, y * p);}
    P operator / (const ld &p)const{return P(x / p, y / p);}

    ld operator ^ (const P &p)const{return x * p.y - y * p.x;}
    ld operator % (const P &p)const{return x * p.x + y * p.y;}

    bool operator == (const P &p)const{
        return !sig(x - p.x) && !sig(y - p.y);
    }

    void read(){
        scanf("%Lf%Lf", &x, &y);
    }
};

struct L{
    P p, v;

    L (){}
    L (P a, P b):p(a), v(b - a){}

    P point(ld t){
        return p + v * t;
    }
};

bool para(L l1, L l2){
    return !sig(l1.v ^ l2.v);
}

ld isLL(L l1, L l2){
    P u = l2.p - l1.p;
    return (u ^ l2.v) / (l1.v ^ l2.v);
}

double isSS(P p1, P p2, P q1, P q2){
    L l1(p1, p2), l2(q1, q2);
    if (para(l1, l2)) return INF;
    ld t = isLL(l2, l1);
    if (sig(t) < 0 || sig(t - 1) > 0) return INF;
    t = isLL(l1, l2);
    if (sig(t) < 0 || sig(t - 1) > 0) return INF;
    return t;
}

bool onleft(P p, L l){
    return sig(l.v ^ (p - l.p)) > 0;
}

P tri[N];

bool intri(P p){
    return onleft(p, L (tri[0], tri[1])) && onleft(p, L (tri[1], tri[2])) && onleft(p, L(tri[2], tri[0]));
}

void addedge(int u, int v){
    e[u].push_back(v);
}

void solve(){
    for (int i = 0; i < N; ++ i){
        e[i].clear();
    }
    for (int i = 0; i < 3; ++ i){
        tri[i].read();
    }
    if (!onleft(tri[2], L (tri[0], tri[1]))){
        std::swap(tri[1], tri[2]);
    }
    for (int i = 0; i < n; ++ i){
        scanf("%s", s[i]);
    }
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < n; ++ j){
            if (s[n - 1 - j][i] == '#') continue;
            P p1(i, j);
            for (int u = -1; u <= 1; ++ u){
                for (int v = -1; v <= 1; ++ v){
                    if (!u && !v) continue;
                    if (!check(i + u, j + v)) continue;
                    if (s[n - 1 - (j + v)][i + u] == '#') continue;
                    P p2(i + u, j + v);
                    if (intri(p1) || intri(p2)) continue;
                    std::vector <double> vec;
                    for (int k = 0; k < 3; ++ k){
                        double p = isSS(p1, p2, tri[k], tri[(k + 1) % 3]);
                        if (p != INF){
                            vec.push_back(p);
                        }
                    }
                    vec.push_back(0);
                    vec.push_back(1);
                    std::sort(vec.begin(), vec.end());
                    bool flag = true;
                    for (int i = 0, sz = vec.size(); i < sz; ++ i){
                        for (int j = i + 1; j < sz; ++ j){
                            if (intri(L (p1, p2).point((vec[i] + vec[j]) * 0.5))){
                                flag = false;
                                break;
                            }
                        }
                    }
                    if (flag){
                        addedge(encode(i, j), encode(i + u, j + v));
                    }
                }
            }
        }
    }
    memset(dis, -1, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    std::queue <int> queue;
    queue.push(0);
    vis[0] = true;
    dis[0] = 0;
    while (!queue.empty()){
        int u = queue.front();
        queue.pop();
        for (auto v : e[u]){
            if (!vis[v]){
                dis[v] = dis[u] + 1;
                vis[v] = true;
                queue.push(v);
            }
        }
    }
    printf("%d\n", dis[encode(n - 1, n - 1)]);
}

int main(){
    while (scanf("%d", &n) != EOF){
        solve();
    }
    return 0;
}
