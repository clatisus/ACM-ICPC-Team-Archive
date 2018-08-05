#include<bits/stdc++.h>
  
const int N = 100010;
const int moder = 998244353;
inline int lowbit(int n){return n & -n;}
  
int c[N], tmp[N];
int p[N], d[N];
  
int powermod(int a, int exp){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * a * ret % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}
  
void mult(int sit, int value){
    for ( ; sit < N; sit += lowbit(sit)){
        c[sit] = 1ll * c[sit] * value % moder;
    }
}
  
int query(int sit){
    int ret = 1;
    for ( ; sit; sit -= lowbit(sit)){
        ret = 1ll * ret * c[sit] % moder;
    }
    return ret;
}
  
int main(){
    for (int i = 0; i < N; ++ i){
        c[i] = 1;
    }
    int n;
    while (scanf("%d", &n) != EOF){
        for (int i = 0; i < n; ++ i){
            scanf("%d%d", &p[i], &d[i]);
            p[i] = 1ll * p[i] * powermod(100, moder - 2) % moder;
            tmp[i] = d[i];
        }
        std::sort(tmp, tmp + n);
        int cnt = std::unique(tmp, tmp + n) - tmp;
        for (int i = 0; i < n; ++ i){
            d[i] = std::lower_bound(tmp, tmp + cnt, d[i]) - tmp + 1;
        }
        int ans = 0;
        for (int i = 0; i < n; ++ i){
            ans = (ans + 1ll * p[i] * query(N - d[i])) % moder;
            mult(N - d[i], (1 - p[i] + moder) % moder);
        }
        printf("%d\n", ans);
    }
    return 0;
}
