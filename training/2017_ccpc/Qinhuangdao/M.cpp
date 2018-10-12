#include<bits/stdc++.h>

int n, R, r;

struct P{
    int x, y, id;
    int dis;

    P ():x(0), y(0), id(0), dis(0){}
    P (int x, int y, int id):x(x), y(y), id(id){
        dis = x * x + y * y;
        dis = std::max(dis, (R - 2 * r) * (R - 2 * r));
    }

    bool operator < (const P &p) const{
        return dis > p.dis;
    }

    bool operator == (const P &p) const{
        return dis == p.dis;
    }
};

const int N = 110;

P p[N];

void solve(){
    scanf("%d%d%d", &n, &R, &r);
    for (int i = 0, x, y; i < n; ++ i){
        scanf("%d%d", &x, &y);
        p[i] = P(x, y, i + 1);
    }
    std::sort(p, p + n);
    std::vector <int> ans;
    for (int i = 0; i < n; ++ i){
        if (p[i].dis == p[n - 1].dis){
            ans.push_back(p[i].id);
        }
    }
    std::sort(ans.begin(), ans.end());
    int sz = ans.size();
    printf("%d\n", sz);
    for (int i = 0; i < sz; ++ i){
        printf("%d%c", ans[i], " \n"[i == sz - 1]);
    }
}

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        solve();
    }
    return 0;
}
