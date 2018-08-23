#include <bits/stdc++.h>

const int max_N = 3000 + 21;

int n, c[max_N][max_N], x[max_N], y[max_N], y1[max_N];

double x1[max_N], x2[max_N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", c[i] + j);
        }
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", y + i);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", y1 + i);
    }
    for (int i = 1; i <= n; ++i) {
        x[i] = y[i];
        for (int j = 1; j <= n; ++j) x[i] += c[i][j];
    }
    for (int i = 1; i <= n; ++i) x1[i] = y1[i];
    for (int _ = 1; _ <= 10; ++_) {
        for (int i = 1; i <= n; ++i) x2[i] = x1[i];
        for (int i = 1; i <= n; ++i) {
            double xx = 0;
            for (int j = 1; j <= n; ++j) {
                xx += c[i][j] * x2[j] / x[j];
            }
            x1[i] = xx + y1[i];
        }
    }
    for (int i = 1; i <= n; ++i) {
        printf("%.10f%c", x1[i], " \n"[i == n]);
    }
    return 0;
}

