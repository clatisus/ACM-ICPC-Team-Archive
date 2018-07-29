#include <bits/stdc++.h>

#define MAXN (4010)
#define ll long long
#define pii std::pair<int, int>

int n, x, y;
pii a[MAXN];
int b[MAXN];
ll dp[MAXN][MAXN];
int queue[MAXN];
int head, tail;
ll cost[MAXN];

int main() {
    scanf("%d", &n);
    if (n == 2) {
        int p1, p2, d;
        scanf("%d%d", &p1, &d);
        scanf("%d%d", &p2, &d);
        printf("%d\n", std::abs(p1 - p2));
        return 0;
    }
    int tot = 0;
    for (int i = 1; i <= n; ++ i) {
        int p, d;
        scanf("%d%d", &p, &d);
        if (d == 1) {
            b[++ y] = p;
        } else {
            a[++ x] = {p, d};
            tot += d;
        }
    }
    std::sort(a + 1, x + a + 1);
    std::sort(b + 1, y + b + 1);
    ll ans = 0;
    if (x >= 2) {
        ans += a[x].first - a[1].first;
        for (int i = 2; i < x; ++ i) a[i].second -= 2, tot -= 2;
        -- a[1].second;
        -- a[x].second;
        tot -= 2;
    }
    if (tot < y) {
        printf("-1\n");
        return 0;
    }
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i <= x; ++ i) dp[i][0] = 0;
    for (int i = 1; i <= x; ++ i) {
        head = tail = 0;
        for (int j = 1; j <= y; ++ j) {
            cost[j] = cost[j - 1] + std::abs(b[j] - a[i].first);
        }
        queue[tail ++] = 0;

        auto calc = [&](int k, int j) {
            return dp[i - 1][k] + cost[j] - cost[k];
        };
        for (int j = 1; j <= y; ++ j) {
            int d = std::min(j, a[i].second);
            while (tail - head && queue[head] + d < j) ++ head;
            if (tail - head) {
                //printf("dp[%d][%d] <- %d\n", i, j, queue[head]);
                dp[i][j] = calc(queue[head], j);
            }
            dp[i][j] = std::min(dp[i][j], dp[i - 1][j]);
            while (tail - head && calc(queue[tail - 1], j + 1) >= calc(j, j + 1)) -- tail;
            queue[tail ++] = j;
        }
    }
    ans += dp[x][y];
    printf("%lld\n", ans);
    return 0;
}

/*
4
1 1
8 2
9 1
14 2

4
181 4
815 4
634 4
370 4

4
52 1
40 1
81 2
73 1

10
330 1
665 3
260 1
287 2
196 3
243 1
815 1
287 3
330 1
473 4
*/

