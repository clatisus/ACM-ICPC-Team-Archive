#include<bits/stdc++.h>

const int N = 100010;
const int moder = 1e9 + 7;

int powermod(int a, int exp){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * ret * a % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

int fac[N], inv[N];
int cnt[N];

char s[N], t[N];

int main(){
    fac[0] = 1;
    for (int i = 1; i < N; ++ i){
        fac[i] = 1ll * fac[i - 1] * i % moder;
    }
    inv[N - 1] = powermod(fac[N - 1], moder - 2);
    for (int i = N - 1; i; -- i){
        inv[i - 1] = 1ll * inv[i] * i % moder;
    }
    int test;
    scanf("%d", &test);
    while (test --){
        scanf("%s%s", s, t);
        int lens = strlen(s);
        int lent = strlen(t);
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < lens; ++ i){
            ++ cnt[s[i]];
        }
        for (int i = 0; i < lent; ++ i){
            -- cnt[t[i]];
        }
        int total = 0, ans = lens - lent + 1;
        for (int i = 'a'; i <= 'z'; ++ i){
            total += cnt[i];
            if (cnt[i] < 0){
                ans = 0;
            }
        }
        ans = 1ll * ans * fac[total] % moder;
        for (int i = 'a'; i <= 'z'; ++ i){
            ans = 1ll * ans * inv[cnt[i]] % moder;
        }
        printf("%d\n", ans);
    }
    return 0;
}
