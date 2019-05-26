//
// Created by zzh on 2019/3/19.
//

#include <bits/stdc++.h>

const int max_N = (int) 1e5 + 21;

namespace sais {
    int t[max_N << 1], sa[max_N], rk[max_N];

    int p[max_N], cnt[max_N], cur[max_N];

#define pushS(x) sa[cur[s[x]]--] = x
#define pushL(x) sa[cur[s[x]]++] = x
#define inducedSort(v) \
    std::fill_n(sa, n, -1), std::fill_n(cnt, m, 0); \
    for (int i = 0; i < n; ++i) ++cnt[s[i]]; \
    for (int i = 1; i < m; ++i) cnt[i] += cnt[i - 1]; \
    for (int i = 0; i < m; ++i) cur[i] = cnt[i] - 1; \
    for (int i = n1 - 1; ~i; --i) pushS(v[i]); \
    for (int i = 1; i < m; ++i) cur[i] = cnt[i - 1]; \
    for (int i = 0; i < n; ++i) \
        if (sa[i] > 0 && t[sa[i] - 1]) pushL(sa[i] - 1); \
    for (int i = 0; i < m; ++i) cur[i] = cnt[i] - 1; \
    for (int i = n - 1; ~i; --i) \
        if (sa[i] > 0 && !t[sa[i] - 1]) pushS(sa[i] - 1);

    void sais(int n, int m, int *s, int *t, int *p) {
        int n1 = t[n - 1] = 0, ch = rk[0] = -1, *s1 = s + n;
        for (int i = n - 2; ~i; --i)
            t[i] = s[i] == s[i + 1] ? t[i + 1] : s[i] > s[i + 1];
        for (int i = 1; i < n; ++i)
            rk[i] = t[i - 1] && !t[i] ? (p[n1] = i, n1++) : -1;
        inducedSort(p);
        for (int i = 0, x, y; i < n; ++i) {
            if (~(x = rk[sa[i]])) {
                if (ch < 1 || p[x + 1] - p[x] != p[y + 1] - p[y]) {
                    ++ch;
                } else {
                    for (int j = p[x], k = p[y]; j <= p[x + 1]; ++j, ++k) {
                        if ((s[j] << 1 | t[j]) != (s[k] << 1 | t[k])) {
                            ++ch;
                            break;
                        }
                    }
                }
                s1[y = x] = ch;
            }
        }
        if (ch + 1 < n1) {
            sais(n1, ch + 1, s1, t + n, p + n1);
        } else {
            for (int i = 0; i < n1; ++i) sa[s1[i]] = i;
        }
        for (int i = 0; i < n1; ++i) s1[i] = p[sa[i]];
        inducedSort(s1);
    }

    void solve(int *s, int n, int m) {
        sais(++n, m, s, t, p);
        for (int i = 0; i < n; ++i) rk[sa[i]] = i;
    }
}

int T, k, n, m, S[max_N << 1], mx[max_N];

char s[max_N], ans[max_N];

struct node {
    int a, b, c;

    node(int a = 0, int b = 0, int c = 0) : a(a), b(b), c(c) {}

    bool operator<(const node &p) const {
        if (a != p.a) return a > p.a;
        if (b != p.b) return b > p.b;
        return c < p.c;
    }
} p[max_N];

void solve(int l, int r, int k) {
    if (l > r) return;
    if (!k) {
        for (int i = l; i <= r; ++i) {
            ans[m++] = s[i];
        }
        return;
    }
    std::vector<std::pair<int, int>> vec;
    int x = mx[l];
    if (S[l] == x) {
        int i = l;
        while (i <= r && S[i] == x) {
            ++i;
            ans[m++] = 'a' + x - 1;
        }
        return solve(i, r, k);
    }
    for (int i = l, j; i <= r; i = j) {
        if (S[i] != x) {
            j = i + 1;
            continue;
        }
        for (j = i; j <= r && S[j] == x; ++j);
        vec.emplace_back(j - 1, j - i);
    }
    int sz = vec.size();
    int ret = -1, sum = 0;
    std::priority_queue<int> pq;
    for (int i = 0; i < sz; ++i) {
        sum += vec[i].second;
        while (pq.size() + 1 > k) {
            sum += pq.top();
            pq.pop();
        }
        pq.push(-vec[i].second);
        int cur = vec[i].first;
        int cost = pq.size();
        assert(cost <= k);
        p[cur] = {sum, sais::rk[cur + 1], cost};
        if (ret == -1 || p[cur] < p[ret]) {
            ret = cur;
        }
    }
    for (int i = 0; i < p[ret].a; ++i) {
        ans[m++] = 'a' + x - 1;
    }
    solve(ret + 1, r, k - p[ret].c);
}

void testCase() {
    scanf("%d%s", &k, s);
    n = strlen(s);
    for (int i = 0; i < n; ++i) {
        S[i] = s[i] - 'a' + 1;
    }
    S[n] = 0;
    sais::solve(S, n, 27);
    m = mx[n] = 0;
    for (int i = n - 1; ~i; --i) {
        mx[i] = std::max(mx[i + 1], S[i]);
    }
    solve(0, n - 1, k);
    ans[m] = '\0';
    puts(ans);
    fflush(stdout);
}

int main() {
    scanf("%d", &T);
    while (T--) {
        testCase();
    }
}
/*
6
7 aazazabzyyyabybbyabxxbaxxxxbbbxxccxffxee

2 abcdcada
1 ababb
2 ababb
1 dadbdcdbdad
2 abxxxxabxcdxxxefxxab
 */