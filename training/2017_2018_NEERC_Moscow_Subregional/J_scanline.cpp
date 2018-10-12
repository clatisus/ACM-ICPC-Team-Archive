#include<bits/stdc++.h>

const double eps = 1e-6;
const double PI = acos(-1.0);
const double INF = 1e100;
typedef long long ll;
typedef std::pair <double, int> pdi;

inline int sig(double p){return (p > eps) - (p < -eps);}

struct func{
    double a, b;

    func():a(0.0), b(0.0){}
    func(double a, double b):a(a), b(b){}
    func(double x1, double y1, double x2, double y2){
        a = (y2 - y1) / (x2 - x1);
        b = y1 - a * x1;
    }

    func operator + (const func &f)const{
        return func(a + f.a, b + f.b);
    }

    func operator - (const func &f)const{
        return func(a - f.a, b - f.b);
    }

    double value(double x){
        return a * x + b;
    }
};

struct P{
    int x, y;
    explicit P (int x = 0, int y = 0):x(x), y(y){}

    bool operator < (const P &p)const{
        return x == p.x ? y < p.y : x < p.x;
    }

    void read(){
        scanf("%d%d", &x, &y);
    }
};

struct T{
    P p[3];

    P &operator [](int n){return p[n];}

    void read(){
        for (int i = 0; i < 3; ++ i){
            p[i].read();
        }
        std::sort(p, p + 3);
    }

    std::vector <double> isTL(double x){
        std::vector <double> vec;
        for (int i = 0; i < 3; ++ i){
            P p1 = p[i], p2 = p[(i + 1) % 3];
            if (p1.x == p2.x) continue;
            if (p1.y == p2.y){
                if (p1.x > p2.x) std::swap(p1, p2);
                if (p1.x <= x && x <= p2.x){
                    vec.push_back(p1.y);
                }
                continue;
            }
            if (p1.y > p2.y) std::swap(p1, p2);
            func f(p1.x, p1.y, p2.x, p2.y);
            double y = f.value(x);
            if (sig(y - p1.y) >= 0 && sig(y - p2.y) <= 0){
                vec.push_back(y);
            }
        }
        std::sort(vec.begin(), vec.end());
        return vec;
    }
};

struct Event{
    func f;
    bool in;
};

const int N = 100010;

T t[N];
std::vector <Event> vec[N];

int main(){
    int n, w, h;
    scanf("%d%d%d", &n, &w, &h);
    for (int i = 0; i < n; ++ i){
        t[i].read();
        if (t[i][0].x == t[i][1].x){
            func f(t[i][0].x, std::abs(t[i][0].y - t[i][1].y), t[i][2].x, 0);
            vec[t[i][0].x].push_back({f, true});
            vec[t[i][2].x].push_back({f, false});
        }
        else if (t[i][1].x == t[i][2].x){
            func f(t[i][0].x, 0, t[i][1].x, std::abs(t[i][2].y - t[i][1].y));
            vec[t[i][0].x].push_back({f, true});
            vec[t[i][1].x].push_back({f, false});
        }
        else{
            func f1(t[i][0].x, t[i][0].y, t[i][2].x, t[i][2].y);
            double y = f1.value(t[i][1].x);
            func f(t[i][0].x, 0, t[i][1].x, std::abs(y - t[i][1].y));
            vec[t[i][0].x].push_back({f, true});
            vec[t[i][1].x].push_back({f, false});
            f = func(t[i][1].x, std::abs(y - t[i][1].y), t[i][2].x, 0);
            vec[t[i][1].x].push_back({f, true});
            vec[t[i][2].x].push_back({f, false});
        }
    }
    func now;
    int sit;
    double min = INF;
    for (int i = 0; i < w; ++ i){
        for (auto &u : vec[i]){
            if (u.in){
                now = now + u.f;
            }
            else{
                now = now - u.f;
            }
        }
        if (min > now.value(i + 0.5)){
            min = now.value(i + 0.5);
            sit = i;
        }
    }
    double x = sit + 0.5;
    std::vector <pdi> vec;
    for (int i = 0; i < n; ++ i){
        std::vector <double> vvec = t[i].isTL(x);
        if (vvec.size() == 2){
            vec.push_back({vvec[0], 1});
            vec.push_back({vvec[1], -1});
        }
    }
    vec.push_back({0, 0});
    vec.push_back({h, 0});
    std::sort(vec.begin(), vec.end());
    for (int i = 0, sum = 0, sz = vec.size(); i < sz; ++ i){
        sum += vec[i].second;
        if (!sum && i < sz - 1 && sig(vec[i + 1].first - vec[i].first) > 0){
            printf("%.9f %.9f\n", x, (vec[i + 1].first + vec[i].first) / 2);
            return 0;
        }
    }
    return 0;
}
