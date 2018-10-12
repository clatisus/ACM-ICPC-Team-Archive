#include <bits/stdc++.h>

#define MAXN (3010)
#define N (2000010)

int n, k;
int a[MAXN];

int min[N];
std::vector<int> prime;

void init() {
    for (int i = 2; i < N; ++i) {
        if (!min[i]) {
            min[i] = i;
            prime.push_back(i);
        }
        for (int j = 0, sz = (int)prime.size(); j < sz && i * prime[j] < N; ++j) {
            min[i * prime[j]] = prime[j];
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}

std::vector<int> vec[MAXN];
int match[MAXN];
bool check[MAXN];
bool on[MAXN];

bool dfs(int u) {
    for (auto v : vec[u]) {
        if (!check[v]) {
            check[v] = true;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                match[u] = v;
                return true;
            }
        }
    }
    return false;
}

void testCase() {
    scanf("%d%d", &n, &k);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        vec[i].clear();
        on[i] = false;
        match[i] = -1;
    }

    std::vector<int> odd;
    for (int i = 1; i <= n; ++i) if (a[i] & 1) {
        for (int j = 1; j <= n; ++j) if (!(a[j] & 1)) {
            int t = a[i] + a[j];
            if (min[t] != t) continue;
            vec[i].push_back(j);
            on[i] = on[j] = true;
        }
        if (a[i] == 1) on[i] = true;
        if (on[i]) odd.push_back(i);
    }

    std::sort(odd.begin(), odd.end(), [&](const int &i, const int &j) {
        return a[i] > a[j];
    });

    int ans = 0;
    for (auto u : odd) {
        if (match[u] == -1) {
            memset(check, 0, sizeof(check));
            if (dfs(u)) {
                ++ans;
            }
        }
    }

    int ones = 0;
    int tot = 0;
    for (int i = 1; i <= n; ++i) {
        if (on[i]) {
            ++tot;
        }
    }
    for (auto u : odd) {
        if (match[u] == -1 && a[u] == 1) {
            ++ones;
        }
    }
    ans += ones / 2;
    if (ans >= k) {
        printf("%d\n", 2 * k);
    } else {
        k -= ans;
        tot -= ans * 2;
        printf("%d\n", ans * 2 + std::min(k, tot));
    }
}

int main() {
    init();
    int T;
    scanf("%d", &T);
    while (T--) {
        testCase();
    }
    return 0;
}
#include <bits/stdc++.h>

#define MAXN (100010)
#define sqr(x) ((x) * (x))
#define ll long long
#define ls (u << 1)
#define rs (ls | 1)

int n, m;
int a[MAXN], pre[MAXN], suf[MAXN];

int seg1[MAXN << 2], seg2[MAXN << 2], cmp[MAXN << 2];
bool lazy[MAXN << 2];

void clear(int u, int l, int r) {
    lazy[u] = false;
    seg1[u] = seg2[u] = cmp[u] = 0;
    if (l == r) return;
    int m = (l + r) >> 1;
    clear(ls, l, m);
    clear(rs, m + 1, r);
}

void copy(int u) {
    lazy[u] = true;
    cmp[u] = 0;
    seg1[u] = seg2[u];
}

void pushdown(int u) {
    if (lazy[u]) {
        copy(ls);
        copy(rs);
        lazy[u] = false;
    }
}

void update(int u, int l, int r, int p, int c) {
    if (l == r) {
        seg2[u] += c;
        cmp[u] = seg1[u] - seg2[u];
        return;
    }
    pushdown(u);
    int m = (l + r) >> 1;
    if (p <= m) update(ls, l, m, p, c);
    else update(rs, m + 1, r, p, c);

    cmp[u] = cmp[ls] ? cmp[ls] : cmp[rs];
}

void testCase() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        pre[i] = suf[i] = i;
    }
    if (n - m == 1) {
        printf("1\n");
        return;
    }
    std::sort(pre + 1, n + pre + 1, [&](const int &i, const int &j) {
        return a[i] == a[j] ? i < j : a[i] < a[j];
    });
    std::sort(suf + 1, n + suf + 1, [&](const int &i, const int &j) {
        return a[i] == a[j] ? i > j : a[i] < a[j];
    });
    std::sort(a + 1, n + a + 1);
    clear(1, 1, n);

    ll ans = 0, sum1 = 0, sum2 = 0;
    int sit = 0;
    for (int i = m + 1; i <= n; ++i) {
        sum1 += a[i];
        sum2 += sqr(a[i]);
        update(1, 1, n, suf[i], 1);
    }
    ans = (n - m) * sum2 - sqr(sum1);
    copy(1);

    // no need for i = n - m
    for (int i = 1; i < n - m; ++i) {
        sum1 += a[i] - a[i + m];
        sum2 += sqr(a[i]) - sqr(a[i + m]);
        update(1, 1, n, pre[i], 1);
        update(1, 1, n, suf[i + m], -1);

        if (a[i] == a[i + m + 1]) continue;
        ll now = (n - m) * sum2 - sqr(sum1);
        if (now > ans || (now == ans && cmp[1] == -1)) {
            ans = now;
            copy(1);
            sit = i;
        }
    }

    std::vector<int> vec;
    for (int i = 1; i <= sit; ++i) vec.push_back(pre[i]);
    for (int i = m + sit + 1; i <= n; ++i) vec.push_back(suf[i]);
    std::sort(vec.begin(), vec.end());
    for (int i = 1; i <= n - m; ++i) {
        printf("%d%c", vec[i - 1], " \n"[i == n - m]);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        testCase();
    }
    return 0;
}
// again
