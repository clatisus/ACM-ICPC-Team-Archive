#include<bits/stdc++.h>

const double eps = 1e-9;
const double PI = std::acos(-1.0);
const double INF = 1e100;

inline int sig(double p){return (p > eps) - (p < -eps);}

inline double sqr(double p){return p * p;}

struct P{
    double x, y;
    P(double x = 0, double y = 0):x(x), y(y){}

    P operator + (const P &p)const{return P(x + p.x, y + p.y);}
    P operator - (const P &p)const{return P(x - p.x, y - p.y);}
    P operator * (const double &p)const{return P(x * p, y * p);}
    P operator / (const double &p)const{return P(x / p, y / p);}
    double operator ^ (const P &p)const{return x * p.y - y * p.x;}
    double operator % (const P &p)const{return x * p.x + y * p.y;}

    double abs2()const{return *this % *this;}
    double abs()const{return std::sqrt(abs2());}

    bool operator < (const P &p)const{
        if (sig(x - p.x)) return x < p.x;
        return y < p.y;
    }

    bool operator == (const P &p)const{
        return !sig(x - p.x) && !sig(y - p.y);
    }

    P rot90()const{
        return P(-y, x);
    }

    void read(){
        scanf("%lf%lf", &x, &y);
    }
};

struct L{
    P p, v;

    L (){}
    L (P a, P b):p(a), v(b - a){}

    P point(int t){
        return p + v * t;
    }
};

struct C{
    P o;
    double r;

    C (){}
    C (P o, double r):o(o), r(r){}
};

std::vector <double> isCL(C c1, L l){
    double a = l.v.x, b = l.p.x - c1.o.x, c = l.v.y, d = l.p.y - c1.o.y;
    double e = sqr(a) + sqr(c), f = 2 * (a * b + c * d);
    double g = sqr(b) + sqr(d) - sqr(c1.r);
    double delta = sqr(f) - 4 * e * g;
    if (sig(delta) < 0) return {};
    if (!sig(delta)){
        return {-f / (2 * e)};
    }
    std::vector <double> ret;
    ret.push_back((-f - std::sqrt(delta)) / (2 * e));
    ret.push_back((-f + std::sqrt(delta)) / (2 * e));
    return ret;
}

std::pair <int, std::vector <P>> isCC(C c1, C c2){
    double d = (c1.o - c2.o).abs2();
    if (!sig(d)){
        if (!sig(c1.r - c2.r)){
            return {-1, {}};
        }
        return {0, {}};
    }
    if (sig(c1.r + c2.r - std::sqrt(d)) < 0) return {4, {}};
    if (sig(std::abs(c1.r - c2.r) - std::sqrt(d)) > 0) return{0, {}};
    double x = ((sqr(c1.r) - sqr(c2.r)) / d + 1) / 2;
    double y = std::max(sqr(c1.r) / d - sqr(x), (double) 0.0);
    P q1 = c1.o + (c2.o - c1.o) * x;
    P q2 = ((c2.o - c1.o) * std::sqrt(y)).rot90();
    if (!sig(y)){
        return {!sig(c1.r + c2.r - std::sqrt(d)) ? 3 : 1, {q1}};
    }
    return {2, {q1 - q2, q1 + q2}};
}

const int N = 2010;
typedef std::pair <int, double> pid;
typedef std::pair <double, int> pdi;

P p[N];
C c[N];
std::vector <pid> e[N];
double dis[N];
bool vis[N];

void addedge(int u, int v, double w){
    e[u].push_back({v, w});
    e[v].push_back({u, w});
}

int main(){
    p[0].read(), p[1].read();
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
        P o;
        int r;
        o.read();
        scanf("%d", &r);
        c[i] = C(o, r);
    }
    int cnt = 2;
    for (int i = 0; i < n; ++ i){
        for (int j = i + 1; j < n; ++ j){
            std::pair <int, std::vector <P>> p = isCC(c[i], c[j]);
            for (auto u : p.second){
                ::p[cnt ++] = u;
            }
        }
    }
    for (int i = 0; i < cnt; ++ i){
        for (int j = i + 1; j < cnt; ++ j){
            if (p[i] == p[j]){
                addedge(i, j, 0.0);
                continue;
            }
            L l(p[i], p[j]);
            std::vector <pdi> vec;
            for (int k = 0; k < n; ++ k){
                std::vector <double> vvec = isCL(c[k], l);
                if (vvec.size() == 2){
                    vec.push_back({vvec[0], 1});
                    vec.push_back({vvec[1], -1});
                }
            }
            if (vec.empty()){
                continue;
            }
            vec.push_back({0, 0});
            vec.push_back({1, 0});
            std::sort(vec.begin(), vec.end());
            bool flag = true;
            for (int i = 0, j = 0, now = 0, sz = vec.size(); i < sz; i = j = j + 1){
                while (j < sz && !sig(vec[j].first - vec[i].first)){
                    now += vec[j].second;
                    ++ j;
                }
                -- j;
                if (now <= 0 && sig(vec[j].first - 0) >= 0 && sig(vec[j].first - 1) <= 0){
                    flag = false;
                    break;
                }
            }
            if (flag){
                addedge(i, j, (p[i] - p[j]).abs());
             }
        }
    }
    for (int i = 1; i < cnt; ++ i){
        dis[i] = INF;
    }
    std::set <pdi> set;
    for (int i = 0; i < cnt; ++ i){
        set.insert({dis[i], i});
    }
    for (int i = 0; i < cnt; ++ i){
        pdi p = *(set.begin());
        set.erase(set.begin());
        int u = p.second;
        vis[u] = true;
        for (auto v : e[u]){
            if (vis[v.first]) continue;
            set.erase({dis[v.first], v.first});
            dis[v.first] = std::min(dis[v.first], dis[u] + v.second);
            set.insert({dis[v.first], v.first});
        }
    }
    if (dis[1] > INF / 10){
        puts("impossible");
    }
    else{
        printf("%.10lf\n", dis[1]);
    }
    return 0;
}
