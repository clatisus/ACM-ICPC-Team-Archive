//
// Created by zzh on 2019/4/27.
//

#include <bits/stdc++.h>

using db = long double;

const db pi = acos(-1.);

struct poi {
    db x, y;

    poi() = default;
    explicit poi(db x, db y) : x(x), y(y) {}
};

std::vector<std::pair<db, int>> ret;

int n;

std::vector<poi> p;

int main() {
    scanf("%d", &n);
    for (int i = 0, x, y; i < n; ++i) {
        scanf("%d%d", &x, &y);
        p.emplace_back(x, y);
    }
    for (int k = 3; k <= 8; ++k) {
        db alpha = 2 * pi / k;
        db r1 = 1e100, r2 = 0;
        for (auto &it : p) {
            db beta = fmod(atan2(it.y, it.x), alpha);
            if (beta < 0) beta += alpha;
            db R = std::sqrt(it.x * it.x + it.y * it.y);
            db r = R * cos(beta) + R * sin(beta) * tan(alpha * 0.5);
            r1 = std::min(r, r1);
            r2 = std::max(r, r2);
        }
        db score = (r1 * r1) / (r2 * r2);
        ret.emplace_back(score, k);
    }
    std::sort(ret.begin(), ret.end());
    printf("%d %.10f\n", ret.back().second, (double) ret.back().first);
}