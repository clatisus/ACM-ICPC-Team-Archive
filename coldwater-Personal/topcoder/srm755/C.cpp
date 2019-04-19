#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200010;

class DejaVu {
public:
    long long b[MAXN];
    int a[MAXN], nxt[MAXN], last[MAXN];
    int seg[MAXN << 2], lazy[MAXN << 2];

    void pushdown(int u) {
        if (!lazy[u])
            return;
        int ls = u << 1, rs = ls | 1;
        lazy[ls] += lazy[u];
        seg[ls] += lazy[u];
        lazy[rs] += lazy[u];
        seg[rs] += lazy[u];
        lazy[u] = 0;
    }

    void modify(int u, int l, int r, int ql, int qr, int c) {
        if (ql <= l && r <= qr) {
            lazy[u] += c;
            seg[u] += c;
            return;
        }
        pushdown(u);
        int m = (l + r) >> 1, ls = u << 1, rs = ls | 1;
        if (ql <= m) modify(ls, l, m, ql, qr, c);
        if (m < qr) modify(rs, m + 1, r, ql, qr, c);
        seg[u] = std::max(seg[ls], seg[rs]);
    }

    int query(int u, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return seg[u];
        }
        pushdown(u);
        int ret = 0;
        int m = (l + r) >> 1, ls = u << 1, rs = ls | 1;
        if (ql <= m) ret = std::max(ret, query(ls, l, m, ql, qr));
        if (m < qr) ret = std::max(ret, query(rs, m + 1, r, ql, qr));
        return ret;
    }

    int mostDejaVus(int n, int seed, int R) {
        b[0] = seed;
        for (int i = 1; i < n; ++i) {
            b[i] = (b[i - 1] * 1664525ll + 1013904223ll) % 4294967296ll;
        }
        std::vector<int> h;
        for (int i = 0; i < n; ++i) {
            a[i] = (int)(b[i] % R);
            h.push_back(a[i]);
        }
        std::sort(h.begin(), h.end());
        h.erase(std::unique(h.begin(), h.end()), h.end());
        for (int i = 0; i < n; ++i) {
            a[i] = (int)(std::lower_bound(h.begin(), h.end(), a[i]) - h.begin());
        }
        for (int i = 0; i < n; ++i) last[i] = n;
        for (int i = n - 1; ~i; --i) {
            nxt[i] = last[a[i]];
            last[a[i]] = i;
        }
        for (int i = 0; i < n; ++i) {
            if (last[a[i]] != i) continue;
            int j = nxt[i];
            if (j == n) continue;
            int k = nxt[j];
            modify(1, 0, n - 1, j, k - 1, 1);
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = std::max(ans, query(1, 0, n - 1, i, n - 1));
            int j = nxt[i];
            if (j == n) continue;
            int k = nxt[j];
            modify(1, 0, n - 1, j, k - 1, -1);
            if (k == n) continue;
            int t = nxt[k];
            modify(1, 0, n - 1, k, t - 1, 1);
        }
        return ans;
    }
};
