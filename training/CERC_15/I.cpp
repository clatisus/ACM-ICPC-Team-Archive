#include <bits/stdc++.h>

#define MAXC (510)

int n;
double r[MAXC][MAXC];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        scanf("%lf", &r[x][y]);
    }
    int q;
    scanf("%d", &q);
    while (q --) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        if (x1 > x2 || (x1 == x2 && y1 > y2)) {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }
        int ret = 0;
        if (x1 == x2) for (int i = y1; i <= y2; ++i) ret += r[x1][i] > 0.0;
        else if (y1 == y2) for (int i = x1; i <= x2; ++i) ret += r[i][y1] > 0.0;
        else {
            double a, b, c, k, l;
            a = y2 - y1;
            b = x2 - x1;
            k = a / b;
            l = y1 - k * x1;
            double len = std::sqrt(a * a + b * b);
            a /= len;
            b /= len;
            c = b * y1 - a * x1;

            auto dis = [&](int x, int y) -> double {
                return std::abs(a * x - b * y + c);
            };

            auto getY = [&](int x) -> double {
                if (x == x2) return y2; // or ceil will get y2 + 1
                return k * x + l;
            };

            auto solve = [&](int x, int low, int high) -> int {
                int t = 0;
                for (int i = low; i <= high; ++i) {
                    t += r[x][i] > 0.0 && r[x][i] >= dis(x, i);
                }
                return t;
            };

            if (y1 < y2) {
                int low = y1, high = std::ceil(getY(x1 + 1));
                ret += solve(x1, low, high);
                for (int i = x1 + 1; i < x2; ++i) {
                    high = std::ceil(getY(i + 1));
                    ret += solve(i, low, high);
                    low = std::floor(getY(i));
                }
                ret += solve(x2, low, high);
            } else {
                int low = std::floor(getY(x1 + 1)), high = y1;
                ret += solve(x1, low, high);
                for (int i = x1 + 1; i < x2; ++i) {
                    low = std::floor(getY(i + 1));
                    ret += solve(i, low, high);
                    high = std::ceil(getY(i));
                }
                ret += solve(x2, low, high);
            }

        }
        printf("%d\n", ret);
    }
    return 0;
}

