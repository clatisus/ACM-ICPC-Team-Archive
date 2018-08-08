#include <bits/stdc++.h>

const double PI = acos(-1.0);

int main() {
    int n, m;
    double R;
    scanf("%d%d%lf", &m, &n, &R);
    int ax, ay, bx, by;
    scanf("%d%d%d%d", &ax, &ay, &bx, &by);
    double ret = 1e100;
    for (int i = 0; i <= std::min(ay, by); ++i) {
        double r = R / n * i;
        ret = std::min(ret,
        R / n * (std::abs(ay - i) + std::abs(by - i)) + r * PI / m * std::abs(ax - bx));
    }
    printf("%.15f\n", ret);
    return 0;
}
