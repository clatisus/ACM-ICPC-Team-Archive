#include<bits/stdc++.h>

const int N = 210;
typedef long long ll;
typedef std::pair <ll, ll> pii;
const long double eps = 1e-9;
inline int sig(ll x){return (x > 0) - (x < 0);}
inline int sig(long double x){return (x > eps) - (x < -eps);}

struct P{
    int x, y;

    explicit P(int x = 0, int y = 0):x(x), y(y){}

    P operator +(const P &p)const{return P(x + p.x, y + p.y);}
    P operator -(const P &p)const{return P(x - p.x, y - p.y);}
    ll operator ^(const P &p)const{return 1ll * x * p.y - 1ll * y * p.x;}
    ll operator %(const P &p)const{return 1ll * x * p.x + 1ll * y * p.y;}

    ll abs2()const {
        return *this % *this;
    }

    long double abs()const{
        return std::sqrt(abs2());
    }

    void read(){
        scanf("%d%d", &x, &y);
    }
};

struct L{
    P p, v;

    L(P p1, P p2):p(p1), v(p2 - p1){}
};

pii isLL(L l1, L l2){
    ll x = (l2.p - l1.p) ^ l2.v, y = l1.v ^ l2.v;
    if (y < 0){
        x = -x, y = -y;
    }
    return {x, y};
}

long double dis(P p1, P p2){
    return 1.0 * (p1 % p2) / p1.abs2();
}

bool para(L l1, L l2){
    return !(l1.v ^ l2.v);
}

P p[N];

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
        p[i].read();
    }
    long double ans = 0;
    for (int i = 0; i < n; ++ i){
        for (int j = i + 1; j < n; ++ j){
            L l(p[i], p[j]);
            typedef std::pair <long double, int> pdi;
            std::vector <pdi> event;
            for (int k = 0; k < n; ++ k){
                P p1 = p[k], p2 = p[(k + 1) % n];
                L l1(p1, p2);
                if (para(l, l1)){
                    if (((p1 - p[i]) ^ l.v) != 0){
                        continue;
                    }
                    P v1 = p[(k + 2) % n] - p2, v2 = p[(k - 1 + n) % n] - p1;
                    long double t1 = dis(l.v, p1 - l.p), t2 = dis(l.v, p2 - l.p);
                    if (t1 > t2){
                        std::swap(t1, t2);
                    }
                    event.push_back({t1, 2});
                    if (sig(v1 ^ l.v) != sig(v2 ^ l.v)){
                        event.push_back({t2, 1});
                    }
                    else{
                        event.push_back({t2, 0});
                    }
                }
                else{
                    pii frac = isLL(l1, l);
                    if (frac.first < 0 || frac.first > frac.second){
                        continue;
                    }
                    if (frac.first == 0){
                        P v = p[(k - 1 + n) % n] - p1;
                        if ((v ^ l.v) == 0){
                            continue;
                        }
                        if (sig(l1.v ^ l.v) != sig(v ^ l.v)){
                            event.push_back({dis(l.v, p1 - l.p), 1});
                        }
                    }
                    else if (frac.first == frac.second){
                        P v = p[(k + 2) % n] - p2;
                        if ((v ^ l.v) == 0){
                            continue;
                        }
                        if (sig(-(l1.v ^ l.v)) != sig(v ^ l.v)){
                            event.push_back({dis(l.v, p2 - l.p), 1});
                        }
                    }
                    else{
                        frac = isLL(l, l1);
                        event.push_back({1.0 * frac.first / frac.second, 1});
                    }
                }
            }
            std::sort(event.begin(), event.end());
            long double sum = 0;
            long double coe = l.v.abs();
            int in = 0;
            for (int k = 0, sz = event.size(); k < sz; ++ k){
                if (k && !sig(event[k].first - event[k - 1].first)){
                    continue;
                }
                if (event[k].second == 1){
                    if (in){
                        sum += event[k].first - event[k - 1].first;
                        ans = std::max(ans, sum * coe);
                        sum = 0;
                    }
                    in ^= 1;
                }
                else{
                    if (in){
                        sum += event[k].first - event[k - 1].first;
                    }
                    sum += event[k + 1].first - event[k].first;
                    int nin = in ^ event[k + 1].second;
                    if (!nin){
                        ans = std::max(ans, sum * coe);
                        sum = 0;
                    }
                    in = nin;
                    ++ k;
                }
            }
        }
    }
    printf("%.15Lf\n", ans);
}
