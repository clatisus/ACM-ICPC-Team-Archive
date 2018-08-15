#include<bits/stdc++.h>

const double eps = 1e-9;
const double PI = std::acos(-1.0);
const double INF = 1e100;

inline int sig(double p){
    return (p > eps) - (p < -eps);
}

inline double sqr(double p){return p * p;}

struct P{
    double x, y;
    explicit P (double x = 0, double y = 0):x(x), y(y){}
    P operator + (const P &p)const{return P(x + p.x, y + p.y);}
    P operator - (const P &p)const{return P(x - p.x, y - p.y);}
    P operator * (const double &p)const{return P(x * p, y * p);}
    P operator / (const double &p)const{return P(x / p, y / p);}
    double operator ^ (const P &p)const{return x * p.y - y * p.x;}
    double operator % (const P &p)const{return x * p.x + y * p.y;}
    double abs2()const{return *this % *this;}
    double abs()const{return std::sqrt(abs2());}

    P rot90()const{
        return P(y, -x);
    }

    void read(){
        scanf("%lf%lf", &x, &y);
    }
};

struct L{
    P p, v;

    L (P a, P b):p(a), v(b - a){}

    P point(double t){
        return p + v * t;
    }
};

struct C{
    P o;
    double r;

    C (){}
    C (P o, double r):o(o), r(r){}
};

double isLL(L l1, L l2){
    P u = l2.p - l1.p;
    return (u ^ l2.v) / (l1.v ^ l2.v);
}

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

bool onSeg(P p1, P p2, P q){
    double len = (q - p1).abs();
    if (!sig(len)) return true;
    p1 = p1 - q, p2 = p2 - q;
    return !sig((p1 ^ p2) / len) && sig(p1 % p2) <= 0;
}

int inPolygon(std::vector <P> &ps, P q){
    int n = ps.size();
    for (int i = 0; i < n; ++ i){
        if (onSeg(ps[i], ps[(i + 1) % n], q)){
            return 0;
        }
    }
    int ret = -1;
    for (int i = 0; i < n; ++ i){
        P a = ps[i], b = ps[(i + 1) % n];
        if (a.y > b.y) std::swap(a, b);
        if (sig((a - q) ^ (b - q)) < 0 && sig(a.y - q.y < 0) && sig(b.y - q.y) >= 0){
            ret = -ret;
        }
    }
    return ret;
}

bool inPol(C c, std::vector <P> ps){
    int n = ps.size();
    for (int i = 0; i < n; ++ i){
        L l(ps[i], ps[(i + 1) % n]);
        std::vector <double> vec = isCL(c, l);
        if (vec.size() == 2){
            if (sig(vec[0] - 0) > 0 && sig(vec[0] - 1) < 0 || sig(vec[1] - 0) > 0 && sig(vec[1] - 1) < 0){
                return false;
            }
        }
    }
    return inPolygon(ps, c.o) == 1;
}

int main(){
    int n;
    scanf("%d", &n);
    std::vector <P> ps;
    for (int i = 0; i < n; ++ i){
        P p;
        p.read();
        ps.push_back(p);
    }
    std::vector <P> qs;
    for (int i = 0; i < n; ++ i){
        P p1 = ps[i], p2 = ps[(i + 1) % n], p3 = p2, p4 = ps[(i + 2) % n];
        P dir1 = p2 - p1;
        dir1 = dir1 / dir1.abs() * 4000.5;
        dir1 = dir1.rot90();
        p1 = p1 + dir1, p2 = p2 + dir1;
        P dir2 = p4 - p3;
        dir2 = dir2 / dir2.abs() * 4000.5;
        dir2 = dir2.rot90();
        p3 = p3 + dir2, p4 = p4 + dir2;
        L l1(p1, p2), l2(p3, p4);
        P q = l1.point(isLL(l1, l2));
        if (inPol(C (q, 4000), ps)){
            qs.push_back(q);
        }
    }
    int sz = qs.size();
    for (int i = 0; i < sz; ++ i){
        for (int j = i + 1; j < sz; ++ j){
            if (sig((qs[j] - qs[i]).abs2() - sqr(8000)) >= 0){
                printf("%.10lf %.10lf\n%.10lf %.10lf\n", qs[i].x, qs[i].y, qs[j].x, qs[j].y);
                return 0;
            }
        }
    }
    puts("impossible");
    return 0;
}
/*
3
0 0
30000 1
60000 0
*/

