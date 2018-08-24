#include<bits/stdc++.h>

const double eps = 1e-9;
const double PI = std::acos(-1.0);
const double INF = 1e100;

inline int sig(double p){return (p > eps) - (p < -eps);}
inline double sqr(double p){return p * p;}

struct P{
    double x, y;
    explicit P (double x = 0, double y = 0):x(x), y(y){}
    P operator + (const P &p)const{return P(x + p.x, y + p.y);}
    P operator - (const P &p)const{return P(x - p.x, y - p.y);}
    P operator * (const double &p)const{return P(x * p, y * p);}
    P operator / (const double &p)const{return P(x / p, y / p);}

    double operator ^(const P &p)const{return x * p.y - y * p.x;}
    double operator %(const P &p)const{return x * p.x + y * p.y;}

    bool operator < (const P &p)const{
        return sig(y - p.y) ? y < p.y : x < p.x;
    }

    void read(){
        scanf("%lf%lf", &x, &y);
    }

    double angle()const{
        return std::atan2(y, x);
    }
};

struct L{
    P p, v;

    L (){}
    L (P a, P b):p(a), v(b - a){}

    P point(double t){
        return p + v * t;
    }
};

double isLL(L l1, L l2){
    P u = l2.p - l1.p;
    return (u ^ l2.v) / (l1.v ^ l2.v);
}

bool para(L l1, L l2){
    return !sig(l1.v ^ l2.v);
}

P p[4];

double area(P p1, P p2, P p3){
    return std::abs((p2 - p1) ^ (p3 - p1)) / 2;
}

std::vector <P> isLS(L l){
    std::vector <double> ret;
    for (int i = 0; i < 4; ++ i){
        L tmp(p[i], p[(i + 1) % 4]);
        if (para(l, tmp)) continue;
        double x = isLL(tmp, l);
        if (sig(x - 0) >= 0 && sig(x - 1) <= 0){
            ret.push_back(isLL(l, tmp));
        }
    }
    std::sort(ret.begin(), ret.end());
    ret.erase(std::unique(ret.begin(), ret.end(), [](double x1, double x2){return !sig(x1 - x2);}), ret.end());
    std::vector <P> vec;
    for (auto u : ret){
        vec.push_back(l.point(u));
    }
    return vec;
}

double area(std::vector <P> ps){
    std::sort(ps.begin(), ps.end());
    std::sort(ps.begin() + 1, ps.end(), [&](P p1, P p2){return (p1 - ps[0]).angle() < (p2 - ps[0]).angle();});
    double ans = 0;
    for (int i = 1, sz = ps.size(); i < sz - 1; ++ i){
        ans += area(ps[0], ps[i], ps[i + 1]);
    }
    return ans;
}

int main(){
    for (int i = 0; i < 4; ++ i){
        p[i].read();
    }
    double ans = 500;
    std::vector <P> vec = isLS(L (P (0, -0.5),P (1, -0.5)));
    for (int i = 0; i < 4; ++ i){
        if (sig(p[i].y - (-0.5)) <= 0){
            vec.push_back(p[i]);
        }
    }
    ans += area(vec) * 5 * 1;
    vec = isLS(L (P (0.5, 0),P (0.5, 1)));
    for (int i = 0; i < 4; ++ i){
        if (sig(p[i].x - (0.5)) >= 0){
            vec.push_back(p[i]);
        }
    }
    ans += area(vec) * 5 * 3;
    vec = isLS(L (P (0, 0.5),P (1, 0.5)));
    for (int i = 0; i < 4; ++ i){
        if (sig(p[i].y - (0.5)) >= 0){
            vec.push_back(p[i]);
        }
    }
    ans += area(vec) * 5 * 6;
    vec = isLS(L (P (-0.5, 0),P (-0.5, 1)));
    for (int i = 0; i < 4; ++ i){
        if (sig(p[i].x - (-0.5)) <= 0){
            vec.push_back(p[i]);
        }
    }
    ans += area(vec) * 5 * 4;
    ans /= 124;
    printf("%.10f\n", ans);
    return 0;
}

