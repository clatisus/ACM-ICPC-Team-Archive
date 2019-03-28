//
// Created by zzh on 2019/3/16.
//

#include <bits/stdc++.h>

using pair = std::pair<double, double>;

int n, w, u, v;

std::vector<pair> vec;

double d, t, t1, t2;

const double inf = 1e10;

int main() {
    scanf("%d%d%d%d%lf%lf", &n, &w, &u, &v, &t1, &t2);
    t = 1. * w / v;
    //printf("t = %.10f\n", t);
    vec.emplace_back(-inf, t1);
    vec.emplace_back(t2, inf);
    for (int i = 1, m, p, l; i <= n; ++i) {
        char dir[5];
        scanf("%s%d", dir, &m);
        while (m--) {
            scanf("%d%d", &l, &p);
            double head = p;
            double tail = p + (*dir == 'E' ? -l : l);
            if (head * tail <= 0) {
                t1 = -d - t;
                t2 = std::abs(tail) / u - d;
                vec.emplace_back(t1, t2);
            } else {
                if (head < 0 && *dir == 'W') continue;
                if (head > 0 && *dir == 'E') continue;
                t1 = std::abs(head) / u - d - t;
                t2 = std::abs(tail) / u - d;
                vec.emplace_back(t1, t2);
            }
        }
        d += t;
    }
    std::sort(vec.begin(), vec.end());
    double cur = -inf, ans = 0;
    for (auto &pr : vec) {
        //printf("%.10f %.10f\n", pr.first, pr.second);
        if (pr.first > cur) {
            ans = std::max(ans, pr.first - cur);
        }
        cur = std::max(cur, pr.second);
    }
    printf("%.10f\n", ans);
}
/*
3 100 5 10 0 100
E 2 100 -300 50 -100
W 3 10 60 50 200 200 400
E 1 100 -300

1 100 5 10 0 200
W 4 100 100 100 300 100 700 100 900
 */