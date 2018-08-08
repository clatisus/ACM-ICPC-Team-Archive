#include<bits/stdc++.h>

const double eps = 1e-9;

int w, h, x, xe, ye;
double mu;

inline int sig(double p){return (p > eps) - (p < -eps);}
inline double sqr(double p){return p * p;}

struct P{
    double x, y;

    P (double x = 0, double y = 0):x(x), y(y){}

    P operator + (const P &p)const{return P(x + p.x, y + p.y);}
    P operator - (const P &p)const{return P(x - p.x, y - p.y);}
    P operator * (const double &p)const{return P(x * p, y * p);}
    P operator / (const double &p)const{return P(x / p, y / p);}

    double operator ^(const P &p)const{return x * p.y - y * p.x;}
    double operator %(const P &p)const{return x * p.x + y * p.y;}
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

double solve(double mid){
    L l1(P(xe, ye), P(w, h)), l2(P(0, mid), P(w, mid));
    double t = isLL(l1, l2);
    P p = l1.point(t);
    double angle = std::sin(std::atan2(xe - w, ye - h)) / mu;
    L l3;
    l3.p = p, l3.v = P(-angle, -std::sqrt(1 - sqr(angle)));
    L l4(P(0, 0), P(w, 0));
    p = l3.point(isLL(l3, l4));
    return p.x;
}

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        scanf("%d%d%d%d%d%lf", &w, &h, &x, &xe, &ye, &mu);
        double left = 0, right = h;
        if (!sig(solve(left) - x)){
            printf("%.4f\n", left);
            continue;
        }
        if (!sig(solve(right) - x)){
            printf("%.4f\n", right);
            continue;
        }
        if (sig(solve(left)- x) == sig(solve(right) - x)){
            puts("Impossible");
            continue;
        }
        for (int i = 0; i < 50; ++ i){
            double mid = (left + right) / 2;
            if (solve(mid) < x){
                left = mid;
            }
            else{
                right = mid;
            }
        }
        printf("%.4f\n", left);
    }
    return 0;
}

