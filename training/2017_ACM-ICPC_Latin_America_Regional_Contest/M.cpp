#include <bits/stdc++.h>

inline void read(int &x) {
   char c;
   while (!isdigit(c = getchar()));
   x = c - '0';
   while (isdigit(c = getchar())) {
       (x *= 10) += c - '0';
   }
}

const int max_N = (int) 1e6 + 21;
const int mod = (int) 1e9 + 7;

int n, st[max_N], ed[max_N], sz[max_N], s[max_N], top[max_N];

int sa[max_N], rk[max_N];

int tmp[max_N], cnt[max_N], bc[max_N];

void build(int n) {
    int i, T, sigma;
    for (i = 1; i <= n; ++i) sa[i] = i;
    std::sort(sa + 1, sa + 1 + n, [&](int a, int b) { return s[a] < s[b]; });
    for (i = 2, bc[sa[1]] = 1; i <= n; ++i) {
        bc[sa[i]] = bc[sa[i - 1]] + (s[sa[i - 1]] < s[sa[i]]);
    }
    for (T = 1; (sigma = bc[sa[n]]) < n; T <<= 1) {
        auto cmp = [&](const int &a, const int &b) {
            if (bc[a] != bc[b])return bc[a] < bc[b];
            return (a + T > n || b + T > n) ? a > b : bc[a + T] < bc[b + T];
        };

        for (i = 0; i <= sigma; ++i)cnt[i] = 0;
        for (i = 1; i <= n; ++i)++cnt[(i + T > n) ? 0 : bc[i + T]];
        for (i = 1; i <= sigma; ++i)cnt[i] += cnt[i - 1];
        for (i = n; i; --i) {
            tmp[cnt[(sa[i] + T > n) ? 0 : bc[sa[i] + T]]--] = sa[i];
        }

        for (i = 0; i <= sigma; ++i)cnt[i] = 0;
        for (i = 1; i <= n; ++i)++cnt[bc[i]];
        for (i = 1; i <= sigma; ++i)cnt[i] += cnt[i - 1];
        for (i = n; i; --i)sa[cnt[bc[tmp[i]]]--] = tmp[i];

        for (i = 2, tmp[sa[1]] = 1; i <= n; ++i) {
            tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        }
        memcpy(bc + 1, tmp + 1, sizeof(int) * n);
    }
    for (i = 1; i <= n; ++i)rk[sa[i]] = i;
}

struct functor {
    bool operator() (int a, int b) {
        return rk[top[a]] > rk[top[b]];
    }
};

std::priority_queue<int, std::vector<int>, functor> pq;

int ret[max_N], tot;

void testCase() {
    st[1] = 1;
    for (int i = 1; i <= n; ++i) {
        // scanf("%d", sz + i);
        read(sz[i]);
        for (int j = 0; j < sz[i]; ++j) {
            // scanf("%d", s + st[i] + j);
            read(s[st[i] + j]);
        }
        s[ed[i] = st[i] + sz[i]] = 301;
        st[i + 1] = ed[i] + 1;
    }/*
    for (int i = 1; i < ed[n]; ++i) {
        printf("%d%c", s[i], " \n"[i + 1 == ed[n]]);
    }*/
    build(ed[n]);/*
    for (int i = 1; i < ed[n]; ++i) {
        printf("[%d]rk = %d\n", i, rk[i]);
    }*/
    for (int i = 1; i <= n; ++i) {
        top[i] = st[i];
        pq.push(i);
    }
    tot = 0;
    while (!pq.empty()) {
        int x = pq.top();
        pq.pop();
        ret[++tot] = s[top[x]++];
        if (top[x] < ed[x]) pq.push(x);
    }
    int ans = 0;
    for (int i = 1; i <= tot; ++i) {
        ans = (1ll * ans * 365 + ret[i]) % mod;
        //printf("%d%c", ret[i], " \n"[i == n]);
    }
    ans = 1ll * ans * 365 % mod;
    printf("%d\n", ans);
}

int main() {
    while (~scanf("%d", &n)) testCase();
    return 0;
}
