#include <bits/stdc++.h>

#define MAXN (500010)

const int MAX = 1 << 19;

int n, k;
char s[MAXN], t[MAXN];
int pre[MAXN];

int seg[MAX << 1];

void modify(int sit, int x){
    seg[sit += MAX] = x;
    for (sit >>= 1; sit; sit >>= 1){
        seg[sit] = std::min(seg[sit << 1], seg[sit << 1 | 1]);
    }
}

int query(int l, int r){
    int min = INT_MAX;
    for (l += MAX, r += MAX + 1; l < r; l >>= 1, r >>= 1){
        if (l & 1) min = std::min(min, seg[l ++]);
        if (r & 1) min = std::min(min, seg[-- r]);
    }
    return min;
}

int main() {
    scanf("%d%d", &n, &k);
    scanf("%s%s", s + 1, t + 1);
    pre[1] = 1;
    for (int i = 2; i <= n; ++i) {
        pre[i] = pre[i - 1] + (t[i] != t[i - 1]);
    }
    int dp = 0;
    modify(0, 0 + 0 - 1);
    for (int i = 1; i <= n; ++i) {
        if (s[i] != t[i]) {
            int tmp = query(std::max(0, i - k), i - 1);
            dp = (tmp + pre[i] + 1) / 2 + 1;
        }
        modify(i, dp + dp - pre[i + 1]);
    }
    printf("%d\n", dp);
    return 0;
}
