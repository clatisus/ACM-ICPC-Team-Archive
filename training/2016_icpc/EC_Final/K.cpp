#include<bits/stdc++.h>

typedef std::pair <double, int> pdi;
const double eps = 1e-9;
const double PI = std::acos(-1.0);
inline double sqr(double x){return x * x;}
inline int sig(double x){return (x > eps) - (x < -eps);}

struct P{
    double x, y, z;

    explicit P(double x = 0, double y = 0, double z = 0):x(x), y(y), z(z){}
    P operator +(const P &p)const{return P(x + p.x, y + p.y, z + p.z);}
    P operator -(const P &p)const{return P(x - p.x, y - p.y, z - p.z);}
    P operator *(const double &p)const{return P(x * p, y * p, z * p);}
    P operator /(const double &p)const{return P(x / p, y / p, z / p);}
    double operator %(const P &p)const{return x * p.x + y * p.y + z * p.z;}
    P operator ^(const P &p)const{return P(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);}
    double abs2()const{return *this % *this;}
    double abs()const{return std::sqrt(abs2());}

    void read(){
        scanf("%lf%lf%lf", &x, &y, &z);
    }
};

P rotate(P a, P b, double angle){
    P e1, e2, e3;
    b = b / b.abs(), e3 = b;
    double lens = a % e3;
    e1 = a - e3 * lens;
    if (sig(e1.abs()) == 0){
        return a;
    }
    e1 = e1 / e1.abs();
    e2 = e1 ^ e3;
    double x1 = a % e2, y1 = a % e1, x2, y2;
    x2 = x1 * std::cos(angle) - y1 * std::sin(angle);
    y2 = x1 * std::sin(angle) + y1 * std::cos(angle);
    return e3 * lens + e1 * y2 + e2 * x2;
}

void normalize(double &angle){
    while (angle < 0) angle += 2 * PI;
    while (angle >= 2 * PI) angle -= 2 * PI;
}

const int N = 1010;

P p[N];

int solve(){
    int n;
    double alpha;
    scanf("%d%lf", &n, &alpha);
    alpha = alpha * PI / 180;
    P o;
    o.read();
    for (int i = 0; i < n; ++ i){
        int x, y;
        scanf("%d%d", &x, &y);
        p[i] = P(x, y, 0) - o;
    }
    int ans = 0;
    for (int i = 0; i < n; ++ i){
        P axis = P(p[i].y, -p[i].x, 0);
        double rotang = std::acos(p[i].z / p[i].abs());
        std::vector <pdi> vec;
        int now = 0;
        for (int j = 0; j < n; ++ j){
            if (i == j) continue;
            double ang = std::acos((p[i] % p[j]) / p[i].abs() / p[j].abs());
            if (sig(ang - alpha * 2) > 0) continue;
            double angle;
            if (sig(ang - alpha * 2) == 0){
                angle = eps;
            }
            else{
                double y = std::sin(ang / 2), z = std::cos(ang / 2);
                double k = std::cos(alpha) * std::sqrt(1 / (sqr(z) - sqr(std::cos(alpha))));
                angle = std::acos(k / std::sqrt(sqr(k) + sqr(z / y) + 1)) + eps;
            }
            P newp = rotate(p[j], axis, rotang);
            double l = std::atan2(newp.y, newp.x);
            double r = l + angle;
            l -= angle;
            normalize(l), normalize(r);
            if (sig(l - r) > 0){
                ++ now;
            }
            vec.push_back({l, -1});
            vec.push_back({r, 1});
        }
        ans = std::max(ans, now);
        std::sort(vec.begin(), vec.end());
        for (auto u : vec){
            now -= u.second;
            ans = std::max(ans, now);
        }
    }
    return ans + 1;
}

int main(){
    int test;
    scanf("%d", &test);
    for (int i = 1; i <= test; ++ i){
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}
