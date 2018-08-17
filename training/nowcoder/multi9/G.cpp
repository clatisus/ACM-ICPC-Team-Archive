#include <bits/stdc++.h>
  
const int max_N = 10000 + 21;
const int max_M = 8 * max_N;
  
int n, a[4][max_N], tot;
  
std::vector<int> vec[4][max_N];
  
struct node {
    int cor[3], min_cor[3], max_cor[3], val, max_val;
    node(int a = 0, int b = 0, int c = 0) {
        min_cor[0] = max_cor[0] = cor[0] = a;
        min_cor[1] = max_cor[1] = cor[1] = b;
        min_cor[2] = max_cor[2] = cor[2] = c;
        val = max_val = 0;
    }
} poi[max_M];
  
int rt, p[max_M], ls[max_M], rs[max_M], ord[max_M], dp[max_M];
  
#define mid ((l + r) >> 1)
#define next(x) ((x == 2) ? 0 : x + 1)
  
inline void min_it(int &x, int a) { if (x > a) x = a; }
inline void max_it(int &x, int a) { if (x < a) x = a; }
  
inline void updt(int x, int y) {
    if (!y) return;
    for (int i = 0; i < 3; ++i) {
        min_it(poi[x].min_cor[i], poi[y].min_cor[i]);
        max_it(poi[x].max_cor[i], poi[y].max_cor[i]);
    }
}
  
int build(int par, int l, int r, int d) {
    if (l > r) return 0;
    auto cmp = [&](int x, int y) { return poi[x].cor[d] < poi[y].cor[d]; };
    std::nth_element(ord + l, ord + mid, ord + r + 1, cmp);
    int x = ord[mid];
    p[x] = par;
    ls[x] = build(x, l, mid - 1, next(d));
    rs[x] = build(x, mid + 1, r, next(d));
    updt(x, ls[x]), updt(x, rs[x]);;
    return x;
}
  
int cor[3], val;
  
inline bool in(int x) {
    for (int i = 0; i < 3; ++i)
        if (poi[x].max_cor[i] > cor[i]) return false;
    return true;
}
  
inline bool out(int x) {
    for (int i = 0; i < 3; ++i)
        if (poi[x].min_cor[i] > cor[i]) return true;
    return false;
}
  
inline bool check(int x) {
    for (int i = 0; i < 3; ++i)
        if (poi[x].cor[i] > cor[i]) return false;
    return true;
}
  
void query(int x) {
    if (!x || out(x)) return;
    if (poi[x].max_val <= val) return;
    if (in(x)) val = poi[x].max_val;
    else {
        if (poi[x].val > val && check(x)) val = poi[x].val;
        query(ls[x]), query(rs[x]);
    }
}
  
inline void modify(int x, int a) {
    if (a <= poi[x].val) return;
    poi[x].val = a;
    for (; x; x = p[x]) max_it(poi[x].max_val, a);
}
  
int main() {
    scanf("%d", &n);
    for (int j = 0; j < 4; ++j) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a[j] + i);
            if (j < 3) vec[j][a[j][i]].push_back(i);
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (auto a : vec[0][i])
            for (auto b : vec[1][i])
                for (auto c : vec[2][i]) {
                    poi[++tot] = node(a, b, c);
                    vec[3][i].push_back(tot);
                }
    }
    for (int i = 1; i <= tot; ++i) ord[i] = i;
    rt = build(0, 1, tot, 0);
    for (int i = 1; i <= n; ++i) {
        int x = a[3][i];
        for (auto u : vec[3][x]) {
            for (int d = 0; d < 3; ++d) cor[d] = poi[u].cor[d] - 1;
            val = 0;
            query(rt);
            dp[u] = val + 1;
        }
        for (auto u : vec[3][x]) {
            modify(u, dp[u]);
        }
    }
    printf("%d\n", poi[rt].max_val);
    return 0;
}
