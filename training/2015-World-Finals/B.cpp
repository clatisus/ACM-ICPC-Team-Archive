#include <bits/stdc++.h>

const double eps = 1e-9;

inline int sig(double p){return (p > eps) - (p < -eps);}

struct P{
    double x, y;

    explicit P(double x = 0, double y = 0):x(x), y(y){}

    P operator +(const P &p)const{return P(x + p.x, y + p.y);}
    P operator -(const P &p)const{return P(x - p.x, y - p.y);}
    P operator *(const double &p)const{return P(x * p, y * p);}
    P operator /(const double &p)const{return P(x / p, y / p);}

    double operator %(const P &p)const{return x * p.x + y * p.y;}
    double operator ^(const P &p)const{return x * p.y - y * p.x;}

    void read(){
        scanf("%lf%lf", &x, &y);
    }
};

struct L{
    P p, v;
    double angle;

    L():angle(0){}
    L(P a, P b):p(a), v(b - a){angle = std::atan2(v.y, v.x);}

    bool operator <(const L &l)const{
        return angle < l.angle;
    }

    P point(double t){
        return p + v * t;
    }
};

bool para(L l1, L l2){
    return !sig(l1.v ^ l2.v);
}

double isLL(L l1, L l2){
    P u = l2.p - l1.p;
    return (u ^ l2.v) / (l1.v ^ l2.v);
}

double onLeft(L l, P p){
    return l.v ^ (p - l.p);
}

std::vector <P> isHalfPlane(std::vector <L> &ls){
    std::sort(ls.begin(), ls.end());
    std::deque <L> dq;
    std::deque <P> ps;
    dq.push_back(ls[0]);
    int n = ls.size();
    auto isLLP = [](L l1, L l2){return l1.point(isLL(l1, l2));};
    for (int i = 1; i < n; ++ i){
        while (!ps.empty() && sig(onLeft(ls[i], ps.back())) <= 0) ps.pop_back(), dq.pop_back();
        while (!ps.empty() && sig(onLeft(ls[i], ps.front())) <= 0) ps.pop_front(), dq.pop_front();
        L l = dq.back();
        if (sig(ls[i].v ^ l.v)){
            dq.push_back(ls[i]);
            ps.push_back(isLLP(l, ls[i]));
        }
        else{
            if (sig(onLeft(l, ls[i].p)) > 0){
                dq.pop_back();
                if (!dq.empty()){
                    ps.pop_back();
                    ps.push_back(isLLP(dq.back(), ls[i]));
                }
                dq.push_back(ls[i]);
            }
        }
    }
    while (!ps.empty() && sig(onLeft(dq.front(), ps.back())) <= 0) ps.pop_back(), dq.pop_back();
    if (dq.size() <= 2) return {};
    ps.push_back(isLLP(dq.front(), dq.back()));
    std::vector <P> ret;
    while (!ps.empty()){
        ret.push_back(ps.front());
        ps.pop_front();
    }
    return ret;
}

std::vector <P> getpol(){
    int n;
    scanf("%d", &n);
    std::vector <P> ps(n);
    for (int i = 0; i < n; ++ i){
        ps[i].read();
    }
    std::reverse(ps.begin(), ps.end());
    return ps;
}

void addpoint(std::vector <P> ps, std::vector <P> qs, P v1, P v2, std::vector <double> &vec) {
    int n = ps.size(), m = qs.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            P v = v1 - v2;
            L l;
            l.p = ps[i], l.v = v;
            L l1(qs[j], qs[(j + 1) % m]);
            if (para(l, l1)) {
                continue;
            }
            double t1 = isLL(l, l1);
            double t2 = isLL(l1, l);
            if (sig(t1) <= 0 || sig(t2) < 0 || sig(t2 - 1) > 0) {
                continue;
            }
            vec.push_back(t1);
        }
    }
}

double calc(std::vector <P> ps, std::vector <P> qs, P v, double t){
    std::vector <L> ls;
    int n = ps.size(), m = qs.size();
    for (int i = 0; i < n; ++ i){
        ls.emplace_back(ps[i] + v * t, ps[(i + 1) % n] + v * t);
    }
    for (int i = 0; i < m; ++ i){
        ls.emplace_back(qs[i], qs[(i + 1) % m]);
    }
    std::vector <P> pps = isHalfPlane(ls);
    double area = 0;
    for (int i = 0, sz = pps.size(); i < sz; ++ i){
        area += pps[i] ^ pps[(i + 1) % sz];
    }
    return area * 0.5;
}

int main(){
    P v1, v2;
    std::vector <P> ps = getpol();
    v1.read();
    std::vector <P> qs = getpol();
    v2.read();
    std::vector <double> vec = {0};
    addpoint(ps, qs, v1, v2, vec);
    addpoint(qs, ps, v2, v1, vec);
    if (vec.size() == 1){
        puts("never");
        return 0;
    }
    std::sort(vec.begin(), vec.end());
    vec.erase(std::unique(vec.begin(), vec.end(), [](const double &p1, const double &p2){return !sig(p1 - p2);}), vec.end());
    double ans = 0, sit = 0;
    for (int i = 0, sz = vec.size(); i < sz - 1; ++ i){
        double left = vec[i], right = vec[i + 1];
        double nowans = 0;
        for (int _ = 0; _ < 100; ++ _){
            double mid1 = (2 * left + right) / 3, mid2 = (left + 2 * right) / 3;
            double ans1 = calc(ps, qs, v1 - v2, mid1), ans2 = calc(ps, qs, v1 - v2, mid2);
            nowans = ans1;
            if (ans1 < ans2){
                left = mid1;
            }
            else{
                right = mid2;
            }
        }
        if (nowans > ans){
            ans = nowans;
            sit = left;
        }
    }
    if (!sig(ans)){
        printf("%.15f\n", vec[1]);
        return 0;
    }
    printf("%.15f\n", sit);
    return 0;
}
