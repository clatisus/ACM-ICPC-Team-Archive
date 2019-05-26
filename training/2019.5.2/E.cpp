//
// Created by nonsensetime on 19-5-2.
//

#include <bits/stdc++.h>

using LL = long long;

const int max_N = (int) 1e5 + 21;

int n, q, cnt[2], last;

std::pair<int, int> Q[max_N];

std::map<int, LL> map;

LL cur, sum, ret[max_N];

int main() {
    freopen("expect.in", "r", stdin);
    freopen("expect.out", "w", stdout);

    scanf("%d%d", &n, &q);
    for (int i = 1, t, k; i <= n; ++i) {
        char opt[5];
        scanf("%s%d%d", opt, &t, &k);
        if (*opt == '-') {
            map[cnt[1] - cnt[0] + 1] += t;
            map[cnt[1] - cnt[0] + 1 + k] -= t;
            cnt[1] += k;
            sum -= 1LL * t * k;
        } else {
            map[cnt[1] - cnt[0] - k + 1] -= t;
            map[cnt[1] - cnt[0] + 1] += t;
            cnt[0] += k;
            sum += 1LL * t * k;
        }
    }
    for (int i = 1; i <= q; ++i) {
        scanf("%d", &Q[i].first);
        Q[i].second = i;
    }
    std::sort(Q + 1, Q + 1 + q);
    for (int i = 1; i <= q; ++i) {
        if (Q[i].first + cnt[0] < cnt[1]) {
            ret[Q[i].second] = -1;
            continue;
        }
        while (!map.empty() && map.begin()->first <= Q[i].first) {
            auto it = map.begin();
            sum += cur * (map.begin()->first - last);
            last = map.begin()->first;
            cur += map.begin()->second;
            map.erase(it);
        }
        sum += cur * (Q[i].first - last);
        last = Q[i].first;
        ret[Q[i].second] = sum + cur;
    }
    for (int i = 1; i <= q; ++i) {
        if (ret[i] == -1) {
            puts("INFINITY");
        } else {
            printf("%lld\n", ret[i]);
        }
    }
}
