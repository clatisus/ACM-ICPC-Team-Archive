#include <bits/stdc++.h>

inline int sqr(int a) { return a * a; }

inline int cube(int a) { return a * a * a; }

int n, l, r;

double inte(int x, int y) {
    if (!y) {
        return (pow(r, x + 1) - pow(l, x + 1)) / (x + 1);
    }
    double ans = pow(r, x + 1) * pow(std::log(r), y) - pow(l, x + 1) * pow(std::log(l), y);
    ans /= x + 1;
    return ans - inte(x, y - 1) * y / (x + 1);
}

double value(std::vector<int> coe1, std::vector<double> coe2) {
    int n = coe1.size(), m = coe2.size();
    double ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            ans += inte(i, j) * coe1[i] * coe2[j];
        }
    }
    return ans;
}

void solve() {
    scanf("%d%d%d", &n, &l, &r);
    double logr = std::log(r);
    if (n == 2) {
        double ans = value({r, -1}, {1});
        ans += value({0, 1}, {logr, -1}) * -0.5;
        printf("%.15f\n", ans * 2 / pow(r - l, 2));
        return;
    }
    if (n == 3) {
        double ans = value({sqr(r), -2 * r, 1}, {1});
        ans += value({0, -r, 1}, {logr, -1});
        ans += value({0, 0, 1}, {logr * logr, -2 * logr, 1}) / 3;
        printf("%.15f\n", ans * 3 / pow(r - l, 3));
        return;
    }
    double ans = value({cube(r), -3 * sqr(r), 3 * r, -1}, {1});
    ans += value({0, sqr(r), -2 * r, 1}, {logr, -1}) * -1.5;
    ans += value({0, 0, r, -1}, {logr * logr, -2 * logr, 1});
    ans += value({0, 0, 0, 1}, {logr * logr * logr, -3 * logr * logr, 3 * logr, -1}) * -0.25;
    printf("%.15f\n", ans * 4 / pow(r - l, 4));
}

int main() {
    int test;
    scanf("%d", &test);
    while (test--) {
        solve();
    }
    return 0;
}
