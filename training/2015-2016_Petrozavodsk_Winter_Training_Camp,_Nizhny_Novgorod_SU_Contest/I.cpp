#include <bits/stdc++.h>

const int max_N = 21;
const int max_S = (1 << max_N);
const int max_M = 1000 + 21;

int n, m, bit[max_S], cnt[max_S];

int u[max_M], v[max_M], w[max_M], Q[max_M];

int f[max_N], ID, id[max_N], a[max_M], b[max_M], ans;

int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}

int getID(int x) {
    if (!id[x]) id[x] = ++ID;
    return id[x];
}

void merge(int l, int r) {
    for (int i = l; i <= r; ++i) {
        if (!a[i]) continue;
        int x = find(u[Q[i]]);
        int y = find(v[Q[i]]);
        if (x == y) {
            ++ans;
            ++w[Q[i]];
        } else {
            f[x] = y;
        }
    }
}

void link(int l, int r) {
    while (true) {
        for (int i = 1; i <= n; ++i) id[i] = 0;
        for (int i = l; i <= r; ++i) a[i] = 0;
        ID = 0;
        for (int i = l; i <= r; ++i) {
            int x = find(u[Q[i]]);
            int y = find(v[Q[i]]);
            if (x == y) continue;
            a[i] = getID(x);
            b[i] = getID(y);
        }
        int s = (1 << ID);
        memset(cnt, 0, s * sizeof(int));
        for (int i = l; i <= r; ++i) {
            if (!a[i]) continue;
            int ss = (1 << (a[i] - 1)) | (1 << (b[i] - 1));
            ++cnt[ss];
        }
        for (int i = 0; i < ID; ++i)
            for (int ss = 0; ss < s; ++ss)
                if ((ss >> i) & 1) {
                    cnt[ss] += cnt[ss ^ (1 << i)];
                }
        int ret = 0;
        for (int ss = 1; ss < s; ++ss) {
            if (bit[ss] > 1 && cnt[ss] > 2 * (bit[ss] - 1)) {
                if (!ret || bit[ret] > bit[ss]) ret = ss;
            }
        }
        if (!ret) return merge(l, r);
        for (int i = l; i <= r; ++i) {
            if (!a[i]) continue;
            if ((~ret >> (a[i] - 1)) & 1) continue;
            if ((~ret >> (b[i] - 1)) & 1) continue;
            int x = find(u[Q[i]]);
            int y = find(v[Q[i]]);
            if (x != y) {
                f[x] = y;
                ++ans;
                --w[Q[i]];
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    int s = (1 << n);
    for (int i = 1; i < s; ++i) {
        bit[i] = bit[i - (i & -i)] + 1;
    }
    for (int i = 1; i <= m; ++i) {
        Q[i] = i;
        scanf("%d%d%d", u + i, v + i, w + i);
    }
    std::sort(Q + 1, Q + 1 + m, [&](int x, int y) { return w[x] < w[y]; });
    for (int i = 1; i <= n; ++i) f[i] = i;
    for (int i = 1, j; i <= m; i = j) {
        for (j = i; j <= m && w[Q[i]] == w[Q[j]]; ++j);
        link(i, j - 1);
    }
    printf("%d\n", ans);
    for (int i = 1; i <= m; ++i) {
        printf("%d %d %d\n", u[i], v[i], w[i]);
    }
    return 0;
}

