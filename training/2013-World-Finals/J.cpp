#include <bits/stdc++.h>

const int N = 110;
const double eps = 1e-9;

inline double sqr(double x){return x * x;}
inline int sig(double x){return (x > eps) - (x < -eps);}

struct P{
    double x, y;

    P(double x = 0, double y = 0):x(x), y(y){}

    P operator +(const P &p)const{return {x + p.x, y + p.y};}
    P operator -(const P &p)const{return {x - p.x, y - p.y};}
    P operator *(const double &p)const{return {x * p, y * p};}
    P operator /(const double &p)const{return {x / p, y / p};}
    double operator %(const P &p)const{return x * p.x + y * p.y;}
    double operator ^(const P &p)const{return x * p.y - y * p.x;}

    double abs2()const {
        return x * x + y * y;
    }

    double abs()const{
        return std::sqrt(abs2());
    }

    void read(){
        scanf("%lf%lf", &x, &y);
    }
};

struct L{
    P p, v;

    L(P p1, P p2):p(p1), v(p2 - p1){}

    P point(double t){return p + v * t;}
};

struct C{
    P o;
    double r;

    C(P o, double r):o(o), r(r){}
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

int main(){
    int n, r;
    scanf("%d%d", &n, &r);
    std::vector <P> ps(n);
    for (int i = 0; i < n; ++ i){
        ps[i].read();
    }
    std::vector <P> vec;
    for (int i = 0; i < n; ++ i){
        vec.push_back(ps[i]);
        if (sig(ps[i].abs() - r) <= 0 && sig(ps[(i + 1) % n].abs() - r) <= 0){
            continue;
        }
        C c(P(0, 0), r);
        L l(ps[i], ps[(i + 1) % n]);
        std::vector <double> vvec = isCL(c, l);
        if (vvec.size() < 2) continue;
        for (auto u : vvec){
            if (sig(u) < 0 || sig(u - 1) > 0){
                continue;
            }
            P p = l.point(u);
            vec.push_back(p);
        }
    }
    n = vec.size();
    double ans = 0;
    for (int i = 0; i < n; ++ i){
        P p1 = vec[i], p2 = vec[(i + 1) % n];
        double area;
        if (sig(p1.abs() - r) <= 0 && sig(p2.abs() - r) <= 0){
            area = std::abs(p1 ^ p2) * 0.5;
        }
        else{
            double angle = (p1 % p2) / p1.abs() / p2.abs();
            angle = std::acos(angle);
            area = r * r * angle * 0.5;
        }
        ans += area * (sig(p1 ^ p2) > 0 ? 1 : -1);
    }
    printf("%.15f\n", ans);
}
