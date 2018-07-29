#include<bits/stdc++.h>

const int N = 10;

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

    P rot90()const{
        return P (-y, x);
    }

    void read(){
        scanf("%lf%lf", &x, &y);
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

typedef std::pair <int, std::vector <P>> piv;

piv isCC(C c1, C c2){
    double d = (c1.o - c2.o).abs2();
    if (!sig(d)){
        if (!sig(c1.r - c2.r)){
            return {-1, {}};
        }
        return {0, {}};
    }
    if (sig(c1.r + c2.r - std::sqrt(d)) < 0) return {4, {}};
    if (sig(std::abs(c1.r - c2.r) - std::sqrt(d)) > 0) return {0, {}};
    double x = ((sqr(c1.r) - sqr(c2.r)) / d + 1) / 2;
    double y = std::max(sqr(c1.r) / d - sqr(x), (double) 0.0);
    P q1 = c1.o + (c2.o - c1.o) * x;
    P q2 = ((c2.o - c1.o) * std::sqrt(y)).rot90();
    if (!sig(y)){
        return {!sig(c1.r + c2.r - std::sqrt(d)) ? 3 : 1, {q1}};
    }
    return {2, {q1 - q2, q1 + q2}};
}

double areaarc(P p, P p1, P p2, double r){
    double area = std::abs((p1 - p) ^ (p2 - p));
    double area1 = std::asin(area / r / r) * r * r / 2;
    return area1 - area / 2;
}

double areaCC(C c1, C c2){
    double d = (c1.o - c2.o).abs();
    if (sig(c1.r + c2.r - d) <= 0){
        return 0;
    }
    if (sig(d - std::abs(c1.r - c2.r)) <= 0){
        return sqr(std::min(c1.r, c2.r)) * PI;
    }
    double x = (sqr(d) + sqr(c1.r) - sqr(c2.r)) / (2 * d);
    double t1 = std::acos(x / c1.r);
    double t2 = std::acos((d - x) / c2.r);
    return sqr(c1.r) * t1 + sqr(c2.r) * t2 - d * c1.r * sin(t1);
}


bool onSeg(P p1, P p2, P q){
    double len = (q - p1).abs();
    if (!sig(len)) return true;
    p1 = p1 - q, p2 = p2 - q;
    return !sig((p1 ^ p2) / len) && sig(p1 % p2) <= 0;
}

std::pair <bool, P> isCSeg(C c, P p1, P p2){
    std::vector <double> vec = isCL(c, L(p1, p2));
    if (vec.empty()){
        return {false, P(0, 0)};
    }
    for (auto u : vec){
        P p = L(p1, p2).point(u);
        if (onSeg(p1, p2, p)){
            return {true, p};
        }
    }
    return {false, P(0, 0)};
}

int n;

int main(){
    int w, h, a, b, ab;
    scanf("%d%d%d%d%d", &w, &h, &a, &b, &ab);
    bool flag = a > b;
    if (flag){
        std::swap(a, b);
    }
    double r1 = std::sqrt(a / PI);
    double r2 = std::sqrt(b / PI);
    double Left = 0, Right = r1 + r2;
    for (int i = 0; i < 100; ++ i){
        double mid = (Left + Right) / 2;
        C c1(P(0, 0), r1), c2(P(mid, 0), r2);
        std::vector <C> vec;
        vec.push_back(c1);
        vec.push_back(c2);
        double area = areaCC(c1, c2); 
        if (area > ab){
            Left = mid;
        }
        else{
            Right = mid;
        }
    }
    if (sig(2 * r2 - std::min(w, h)) > 0){
        puts("impossible");
        return 0;
    }
    C c2(P(w - r2, h - r2), r2);
    C c3(P(w - r2, h - r2), Left);
    double left = r1, right = w - r1, down = r1, up = h - r1;
    P ld(left, down), lu(left, up), rd(right, down), ru(right, up);
    std::pair <bool, P> p = isCSeg(c3, ld, lu);
    C c1(P(0, 0), -1);
    if (p.first){
        c1 = C(p.second, r1);
    }
    p = isCSeg(c3, lu, ru);
    if (p.first){
        c1 = C(p.second, r1);
    }
    p = isCSeg(c3, ru, rd);
    if (p.first){
        c1 = C(p.second, r1);
    }
    p = isCSeg(c3, ld, rd);
    if (p.first){
        c1 = C(p.second, r1);
    }
    if (sig(c1.r) < 0){
        if (sig((c3.o - lu).abs() - c3.r) < 0){
            puts("impossible");
            return 0;
        }
        c1 = C(c3.point(0), r1);
    }
    if (flag){
        std::swap(c1, c2);
    }
    printf("%.10f %.10f %.10f %.10f %.10f %.10f\n", c1.o.x, c1.o.y, c1.r, c2.o.x, c2.o.y, c2.r);
    return 0;
}

/*
20 10 75 75 0
*/

