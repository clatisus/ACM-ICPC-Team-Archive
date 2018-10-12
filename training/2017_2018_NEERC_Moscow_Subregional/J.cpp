#include<bits/stdc++.h>

const long double eps = 1e-10;
const long double PI = acos(-1.0);
const long double INF = 1e100;
typedef std::pair <long double, int> pdi;

inline int sig(long double p){
    return (p > eps) - (p < -eps);
}

inline long double sqr(long double q){return q * q;}

struct P{
    long double x, y;
    explicit P (long double x = 0, long double y = 0):x(x), y(y){}

    P operator + (const P &p)const{return P(x + p.x, y + p.y);}
    P operator - (const P &p)const{return P(x - p.x, y - p.y);}
    P operator * (const long double &p)const{return P(x * p, y * p);}
    P operator / (const long double &p)const{return P(x / p, y / p);}

    long double operator ^ (const P &p)const{return x * p.y - y * p.x;}
    long double operator % (const P &p)const{return x * p.x + y * p.y;}

    bool operator < (const P &p)const{
        return sig(y - p.y) ? y < p.y : x < p.x;
    }

    bool operator == (const P &p)const{
        return !sig(x - p.x) && !sig(y - p.y);
    }

    bool less(const P &p)const{
        return x * p.y > y * p.x;
    }

    void read(){
        int x, y;
        scanf("%d%d", &x, &y);
        this -> x = x;
        this -> y = y;
    }
};

struct L{
    P p, v;

    L (){}
    L (P a, P b):p(a), v(b - a){}

    P point(long double t){return p + v * t;}
};

bool para(L l1, L l2){
    return !sig(l1.v ^ l2.v);
}

long double isLL(L l1, L l2){
    P u = l2.p - l1.p;
    return (u ^ l2.v) / (l1.v ^ l2.v);
}

long double area(P p1, P p2, P p3){
    return std::abs((p2 - p1) ^ (p3 - p1)) / 2;
}

struct T{
    P p[3];

    void read(){
        for (int i = 0; i < 3; ++ i){
            p[i].read();
        }
    }

    std::vector <long double> isTL(L l){
        std::vector <long double> ret;
        for (int i = 0; i < 3; ++ i){
            L tmp(p[i], p[(i + 1) % 3]);
            if (para(l, tmp)){
                continue;
            }
            long double x = isLL(tmp, l);
            if (sig(x - 0) >= 0 && sig(x - 1) <= 0){
                ret.push_back(isLL(l, tmp));
            }
        }
        std::sort(ret.begin(), ret.end());
        ret.erase(std::unique(ret.begin(), ret.end(), [](long double p1, long double p2){return !sig(p1 - p2);}), ret.end());
        return ret;
    }

    long double area(long double low, long double high){
        L l(P(high, 0), P(high, 1)), l2(P(low, 0), P(low, 1));
        std::vector <P> vec;
        for (auto u : isTL(l)){
            vec.push_back(l.point(u));
        }
        for (auto u : isTL(l2)){
            vec.push_back(l2.point(u));
        }
        for (int i = 0; i < 3; ++ i){
            if (sig(p[i].x - high) <= 0 && sig(p[i].x - low) >= 0){
                vec.push_back(p[i]);
            }
        }
        std::sort(vec.begin(), vec.end());
        std::vector <P> vvec;
        for (auto u : vec){
            if (!(u == vec[0])){
                vvec.push_back(u);
            }
        }
        if (vvec.size() < 2) return 0.0;
        std::sort(vvec.begin(), vvec.end(), [&](const P &p1, const P &p2){return (p1 - vec[0]).less(p2 - vec[0]);});
        long double area = 0;
        for (int i = 0, sz = vvec.size(); i < sz - 1; ++ i){
            area += ::area(vec[0], vvec[i], vvec[i + 1]);
        }
        return area;
    }

    bool in(P q){
        long double atot = ::area(p[0], p[1], p[2]);
        long double a1 = ::area(q, p[1], p[2]);
        long double a2 = ::area(p[0], q, p[2]);
        long double a3 = ::area(p[0], p[1], q);
        return !sig(atot - a1 - a2 - a3);
    }
};

const int N = 100010;

T t[N];

int main(){
    int n, w, h;
    scanf("%d%d%d", &n, &w, &h);
    for (int i = 0; i < n; ++ i){
        t[i].read();
    }
    long double left = 0, right = w;
    for (int i = 0; ; ++ i){
        long double mid = (left + right) / 2;
        std::vector <pdi> vec;
        for (int j = 0; j < n; ++ j){
            std::vector <long double> vvec = t[j].isTL(L (P (mid, 0), P(mid, 1)));
            if (vvec.size() == 2){
                vec.push_back({vvec[0], 1});
                vec.push_back({vvec[1], -1});
            }
        }
        vec.push_back({0.0, 0});
        vec.push_back({(long double) h, 0});
        std::sort(vec.begin(), vec.end());
        for (auto u : vec){
            //printf("%.10f %d\n", u.first, u.second);
        }
        bool flag = false;
        long double ansy;
        for (int i = 0, j, sz = vec.size(), sum = 0; i < sz; i = j){
            j = i;
            while (j < sz && !sig(vec[j].first - vec[i].first)){
                sum += vec[j ++].second;
            }
            if (j < sz && !sum){
                flag = true;
                ansy = (vec[j].first + vec[j - 1].first) / 2;
                break;
            }
        }
        if (flag){
            for (int j = 0; j < n; ++ j){
                assert(!t[j].in(P (mid, ansy)));
            }
            printf("%.9f %.9f\n", (double) mid, (double) ansy);
            return 0;
        }
        long double area = 0;
        for (int i = 0; i < n; ++ i){
            area += t[i].area(left, mid);
        }
        if (sig(area - (mid - left) * h) < 0){
            right = mid;
        }
        else{
            left = mid;
        }
    }
    return 0;
}

/*
3 6 3
0 0 6 0 3 3
0 0 0 3 6 3
6 1 6 3 0 0
*/

