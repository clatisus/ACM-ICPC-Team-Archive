#include<bits/stdc++.h>

const double PI = std::acos(-1);
const double eps = 1e-9;
inline int sig(double p){return (p > eps) - (p < -eps);}

struct P{
    double x, y;
    
    explicit P (double x = 0, double y = 0):x(x), y(y){}
    P operator + (const P &p)const{return P (x + p.x, y + p.y);}
    P operator - (const P &p)const{return P (x - p.x, y - p.y);}
    P operator * (const double &p)const{return P (x * p, y * p);}
    P operator / (const double &p)const{return P (x / p, y / p);}
    double operator % (const P &p)const{return x * p.x + y * p.y;}
    double operator ^ (const P &p)const{return x * p.y - y * p.x;}
    double abs2()const{return *this % *this;}
    double abs()const{return std::sqrt(abs2());}

    bool operator == (const P &p)const{
        return !sig(x - p.x) && !sig(y - p.y);
    }
};

double disSP(P p1, P p2, P q){
    if (p1 == p2) return (q - p1).abs();
    P v1 = p2 - p1, v2 = q - p1, v3 = q - p2;
    if (sig(v1 % v2) < 0) return v2.abs();
    if (sig(v1 % v3) > 0) return v3.abs();
    return std::abs(v1 ^ v2) / v1.abs();
}

int main(){
    int r, l, w, test;
    scanf("%d%d%d%d", &r, &l, &w, &test);
    while (test --){
        double min = std::min(2 * r, std::min(l, w));
        double a, b;
        scanf("%lf%lf", &a, &b);
        P A(l, w), C(l + l * std::cos(PI - a), w + l * std::sin(PI - a));
        P B(l, 0), D(l + l * std::cos(PI - b), 0 + l * std::sin(PI - b));
        P E(0, w);
        if (a >= PI / 2 && b >= PI / 2){
            min = std::min(min, w - D.y);
        }
        else if (a >= PI / 2){
            min = std::min(min, disSP(B, D, A));
        }
        else if (b >= PI / 2){
            min = std::min(min, w - D.y);
            min = std::min(min, disSP(A, C, E));
        }
        else{
            min = std::min(min, disSP(A, C, E));
            min = std::min(min, disSP(A, C, B));
            min = std::min(min, disSP(A, C, D));
            min = std::min(min, disSP(B, D, A));
            min = std::min(min, disSP(B, D, C));
        }
        printf("%.10f\n", min * 0.5);
    }
    return 0;
}

