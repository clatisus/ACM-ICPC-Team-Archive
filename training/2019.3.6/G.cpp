//
// Created by zzh on 2019/3/6.
//

#include <bits/stdc++.h>

using LL = long long;

const int max_N = (int) 1e6 + 21;

int n, c, a[max_N], last[max_N];

LL A[max_N], B[max_N];

int main() {
    scanf("%d%d", &n, &c);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        int l = last[a[i]], r = i;
        if (!l) {
            --A[1], ++A[i];
            B[1] += i, B[i] -= i;
        } else {
            int mid = (l + r) >> 1;
            ++A[last[a[i]]], --A[mid + 1];
            B[l] -= l, B[mid + 1] += l;
            --A[mid + 1], ++A[i];
            B[mid + 1] += r, B[r] -= r;
        }
        last[a[i]] = i;
    }
    for (int i = 1; i <= c; ++i) {
        int l = last[i];
        ++A[l], B[l] -= l;
    }
    LL ans = LLONG_MAX;
    for (int i = 1; i <= n; ++i) {
        A[i] += A[i - 1];
        B[i] += B[i - 1];
        ans = std::min(ans, A[i] * i + B[i]);
    }
    LL g = std::__gcd(ans, (LL) c);
    ans /= g, c /= g;
    printf("%lld/%d\n", ans, c);
}
