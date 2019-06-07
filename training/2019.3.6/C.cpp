#include <bits/stdc++.h>

int n;
double a[40];

void ask(int t, double x, int now) {
    printf("%d %.15f\n", t, x);
    fflush(stdout);
    a[now] = a[t] * x;
    a[t] -= a[now];
}

void get(int now) {
    int t;
    double x;
    scanf("%d %lf", &t, &x);
    a[now] = a[t] * x;
    a[t] -= a[now];
}

void solve() {
    a[0] = 1;
    if (n == 1) {
        ask(0, 2.0 / 3, 1);
        return;
    }
    ask(0, 1.0 / 3, 1);
    for (int i = 2; i < n; ++i) {
        // me
        if (i & 1) {
            int sit = 39;
            for (int j = 2; j < i; j += 2) {
                if (a[sit] < a[j]) {
                    sit = j;
                }
            }
            ask(sit, 2.0 / 3, i);
        } else {
            get(i);
        }
    }
    ask(0, 2.0 / 3, n);
//    double wjj = 0;
//    for (int i = 1; i <= n; i += 2) {
//        wjj += a[i];
//    }
//    printf("wjj = %.10f\n", wjj);
    int ans;
    scanf("%d", &ans);
    if (ans == 0) {
        exit(0);
    }
}

int main() {
    int T;
    scanf("%d%d", &T, &n);
    while (T--) {
        solve();
    }
    return 0;
}