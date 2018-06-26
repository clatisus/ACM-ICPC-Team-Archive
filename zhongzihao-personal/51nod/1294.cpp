#include<bits/stdc++.h>

const int N = 100010;
const int MAX = 1 << 17;

int seg[MAX << 1];

void add(int sit, int value){
    seg[sit += MAX] = value;
    for (sit >>= 1; sit; sit >>= 1){
        seg[sit] = std::max(seg[sit << 1], seg[sit << 1 | 1]);
    }
}

int query(int l, int r){
    int ret = 0;
    for (l += MAX, r += MAX + 1; l < r; l >>= 1, r >>= 1){
        if (l & 1) ret = std::max(ret, seg[l ++]);
        if (r & 1) ret = std::max(ret, seg[-- r]);
    }
    return ret;
}

int dp[N], a[N], c[N];

int main(){
    int n, pren;
    scanf("%d", &n);
    pren = n;
    for (int i = 0; i < n; ++ i){
        scanf("%d", &a[i]);
        a[i] -= i;
    }
    n = 0;
    for (int i = 0, j = 0; j < pren; ++ j){
        if (a[j] > 0){
            a[i ++] = a[j];
            n = i;
        }
    }
    for (int i = 0; i < n; ++ i){
        c[i] = a[i];
    }
    std::sort(c, c + n);
    int cnt = std::unique(c, c + n) - c;
    for (int i = 0; i < n; ++ i){
        a[i] = std::lower_bound(c, c + cnt, a[i]) - c;
    }
    for (int i = 0; i < n; ++ i){
        dp[i] = query(0, a[i]) + 1;
        add(a[i], dp[i]);
    }
    int max = 0;
    for (int i = 0; i < n; ++ i){
        max = std::max(max, dp[i]);
    }
    printf("%d\n", pren - max);
    return 0;
}
