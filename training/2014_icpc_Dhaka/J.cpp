#include <bits/stdc++.h>

const int max_N = (int) 1e5 + 21;
const int mod = (int) 1e9 + 7;

using ll = unsigned long long;

int T, n;

std::pair<int, int> p[max_N];

ll sum[max_N], cnt[max_N], ans;

void testCase() {
    static int caseID = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &p[i].first, &p[i].second);
    }
    std::sort(p + 1, p + 1 + n);
    ans = 0;
    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i - 1] + p[i].second;
        ans += sum[i] * p[i].second;
    }
    cnt[n] = 1;
    for (int i = n - 1; i; --i) {
        cnt[i] = cnt[i + 1] * (p[i].second + 1) % mod;
    }
    printf("Case %d: %llu %llu\n", ++caseID, ans, cnt[1]);
}

int main() {
    scanf("%d", &T);
    while (T--) testCase();
    return 0;
}
