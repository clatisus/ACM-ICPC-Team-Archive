#include <bits/stdc++.h>

#define MAXN (10010)

int n, m;
int a[MAXN], b[MAXN];
std::pair<int, int> pa[MAXN], pb[MAXN];
int la[MAXN], card[MAXN];
bool va[MAXN];

int check(int mid = 0) {
    int ret = 0;
    for (int i = 1, j = 1; i <= n && j <= m; ++i, ++j) {
        if (va[i]) {
            --j;
            continue;
        }
        for (; j <= m && (pb[j].first <= pa[i].first || j == mid); ++j);
        if (j > m) break;
        ++ret;
    }
    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        pa[i] = {a[i], i};
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", b + i);
        pb[i] = {b[i], i};
    }
    std::sort(pa + 1, n + pa + 1);
    std::sort(pb + 1, n + pb + 1);
    for (int i = 1; i <= n; ++i) {
        la[pa[i].second] = i;
    }
    m = n;
    int ans = check();
    for (int i = 1; i <= n; ++i) {
        va[la[i]] = true;
        int j = (int)(std::upper_bound(pb + 1, m + pb + 1, std::make_pair(a[i], INT_MAX)) - pb);
        int left = j, right = m, find = -1;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (check(mid) + 1 == ans) {
                find = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        if (find == -1) {
            left = 1; right = j - 1;
            while (left <= right) {
                int mid = (left + right) >> 1;
                if (check(mid) == ans) {
                    find = mid;
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        } else {
            --ans;
        }

        card[i] = pb[find].first;

        for (int k = find + 1; k <= m; ++k) {
            pb[k - 1] = pb[k];
        }
        --m;

    }
    for (int i = 1; i <= n; ++i) {
        printf("%d%c", card[i], " \n"[i == n]);
    }
    return 0;
}