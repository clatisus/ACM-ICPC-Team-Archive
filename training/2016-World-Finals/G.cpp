#include<bits/stdc++.h>

typedef long long ll;

struct P{
    int x, y;

    P operator -(const P &p)const{
        return {x - p.x, y - p.y};
    }

    ll operator ^(const P &p)const{
        return 1ll * x * p.y - 1ll * y * p.x;
    }

    int getarea()const{
        if (y) return y > 0 ? 0 : 1;
        return x > 0 ? 0 : 1;
    }

    bool operator <(const P &p)const{
        int a1 = getarea(), a2 = p.getarea();
        if (a1 != a2){
            return a1 < a2;
        }
        return (*this ^ p) > 0;
    }
};

struct event{
    P p;
    int len;
    bool in;

    bool operator <(const event &e)const{
        if (p < e.p){
            return true;
        }
        if (e.p < p){
            return false;
        }
        return in > e.in;
    }
};

const int N = 2010;

P p1[N], p2[N];

int main(){
    int n;
    scanf("%d", &n);
    std::vector <std::pair <P, int>> vec;
    for (int i = 0; i < n; ++ i){
        int x1, x2, y;
        scanf("%d%d%d", &x1, &x2, &y);
        if (x1 > x2){
            std::swap(x1, x2);
        }
        p1[i] = {x1, y};
        p2[i] = {x2, y};
        int len = x2 - x1;
        vec.push_back({p1[i], len});
        vec.push_back({p2[i], len});
    }
    ll ans = 0;
    for (auto u : vec){
        std::vector <event> events;
        for (int i = 0; i < n; ++ i){
            if (p1[i].y == u.first.y){
                continue;
            }
            P p = p1[i] - u.first, q = p2[i] - u.first;
            if (p.y < 0){
                p.x = -p.x;
                q.x = -q.x;
                p.y = -p.y;
                q.y = -q.y;
            }
            if (q < p){
                std::swap(p, q);
            }
            int len = std::abs(p2[i].x - p1[i].x);
            events.push_back({p, len, true});
            events.push_back({q, len, false});
        }
        std::sort(events.begin(), events.end());
        ll nowlen = u.second;
        ans = std::max(ans, nowlen);
        for (auto u : events){
            if (u.in){
                nowlen += u.len;
            }
            else{
                nowlen -= u.len;
            }
            ans = std::max(ans, nowlen);
        }
    }
    printf("%lld\n", ans);
    return 0;
}
