#include<bits/stdc++.h>

const double eps = 1e-9;
const double PI = acos(-1.0);
const double INF = 1e100;

inline int sig(double p){
    return (p > eps) - (p < -eps);
}

inline double sqr(double p){return p * p;}

class P{
public:
    double x, y;
    explicit P (double x = 0, double y = 0): x(x), y(y){}
    P operator + (const P &p)const{return P (x + p.x, y + p.y);}
    P operator - (const P &p)const{return P (x - p.x, y - p.y);}
    P operator * (const double &p)const{return P (x * p, y * p);}
    friend P operator * (const double &d, const P &p){return P (d * p.x, d * p.y);}
    P operator / (const double &p)const{return P (x / p, y / p);}
    double operator ^ (const P &p)const{return x * p.y - y * p.x;}
    double operator % (const P &p)const{return x * p.x + y * p.y;}
    double abs2()const{return *this % *this;}
    double abs()const{return std::sqrt(abs2());}
    double angle()const{return std::atan2(y, x);}
    
    // 逆时针旋转 rad 弧度 
    P rot(const double &rad)const{
        double sin = std::sin(rad), cos = std::cos(rad);
        return P (x * cos - y * sin, x * sin + y * cos);
    }
    
    P rot90()const{
        return P (-y, x);
    }
    
    bool operator < (const P &p)const{
        if (sig(x - p.x)) return x < p.x;
        return y < p.y;
    }
    
    bool operator == (const P &p)const{
        return !sig(x - p.x) && !sig(y - p.y);
    }
    
    void read(){
        scanf("%lf%lf", &x, &y);
    }
};

class L{
public:
    P p, v;
    double angle;
    
    L (){}
    L (P a, P b):p(a), v(b - a){angle = std::atan2(v.y, v.x);}
    
    bool operator < (const L &l)const{
        return angle < l.angle;
    }
    
    P point(double t){
        return p + v * t;
    }
};

class C{
public:
    P o;
    double r;
    
    C (){}
    C (P o, double r):o(o), r(r){}
    
    P point(double angle){
        return P (o + P (std::cos(angle), std::sin(angle)) * r);
    }
};

double rad(P p1, P p2){
    return std::acos((p1 % p2) / (p1.abs() * p2.abs()));
}

std::vector <P> tanCP(C c, P p){ // p在圆上时返回 p 点本身 
    double d = (p - c.o).abs2();
    double x = d - sqr(c.r);
    if (sig(x) < 0) return {};
    if (!sig(x)) return {p};
    P q1 = (p - c.o) * sqr(c.r) / d;
    P q2 = ((p - c.o) * -c.r * std::sqrt(x) / d).rot90();
    return {c.o + q1 - q2, c.o + q1 + q2};
}

std::vector <double> isCL(C c1, L l){ // 以离 l.p 近为序 
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

const int N = 100010;
const int DEG = 180000;
const int MAX = 1 << 17;
typedef std::pair <int, int> pii;

std::set <int> set;
int ans[MAX];
std::vector <int> vec[MAX << 1];

void insert(int &max, int sit){
    if (!set.empty()){
        for (int i = sit; i <= sit + DEG * 2; i += DEG * 2){
            auto u = set.upper_bound(i + DEG);
            if (u != set.begin()){
                int x = std::abs(i - *(-- u));
                if (x <= DEG){
                    max = std::max(max, x);
                }
            }
            u = set.lower_bound(i - DEG);
            if (u != set.end()){
                int x = std::abs(i - *u);
                if (x <= DEG){
                    max = std::max(max, x);
                }
            }
        }
    }
    set.insert(sit);
    set.insert(sit + DEG * 2);
}

void add(int sit, int l, int r, int ql, int qr, int value){
    if (ql <= l && qr >= r){
        vec[sit].push_back(value);
        return;
    }
    int mid = l + r >> 1;
    if (ql <= mid){
        add(sit << 1, l, mid, ql, qr, value);
    }
    if (qr > mid){
        add(sit << 1 | 1, mid + 1, r, ql, qr, value);
    }
}

void add(int ql, int qr, int value){
    add(1, 0, MAX - 1, ql, qr, value);
}

void solve(int sit, int l, int r, int max){
    for (auto u : vec[sit]){
        insert(max, u);
    }
    if (l == r){
        ans[l] = max;
    }
    if (l != r){
        int mid = l + r >> 1;
        solve(sit << 1, l, mid, max);
        solve(sit << 1 | 1, mid + 1, r, max);
    }
    for (auto u : vec[sit]){
        set.erase(u);
        set.erase(u + DEG * 2);
    }
}

int main(){
    int R, r;
    scanf("%d%d", &R, &r);
    int n;
    scanf("%d", &n);
    std::set <pii> set;
    for (int i = 0, x; i < n; ++ i){
        scanf("%d", &x);
        set.insert({x, 0});
    }
    int q;
    scanf("%d", &q);
    for (int i = 1; i <= q; ++ i){
        int type, x;
        scanf("%d%d", &type, &x);
        if (type == 1){
            set.insert(std::make_pair(x, i));
        }
        else{
            auto u = set.lower_bound(std::make_pair(x, INT_MIN));
            add(u -> second, i - 1, x);
            set.erase(u);
        }
    }
    for (auto u : set){
        add(u.second, q, u.first);
    }
    solve(1, 0, MAX - 1, 0);
    for (int i = 0; i <= q; ++ i){
        //printf("max = %d\n", ans[i]);
        P p1(0, R);
        double angle = ans[i] * PI / DEG;
        P p2(std::sin(angle) * R, std::cos(angle) * R);
        C c(P(0, 0), r);
        if (isCL(c, L(p1, p2)).size() <= 1){
            printf("%.10f\n", (p1 - p2).abs());
        }
        else{
            std::vector <P> vec1 = tanCP(c, p1);
            std::vector <P> vec2 = tanCP(c, p2);
            double min = INF;
            for (auto u : vec1){
                for (auto v : vec2){
                    double angle = rad(u, v);
                    min = std::min(min, angle * r + (p1 - u).abs() + (p2 - v).abs());
                }
            }
            printf("%.10f\n", min);
        }
    }
    return 0;
}
