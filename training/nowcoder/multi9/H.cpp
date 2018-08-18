#include<bits/stdc++.h>
 
const int N = 100010;
const int M = 50;
const int moder = 1e9 + 7;
 
int n, m, k;
int a[N];
int b[M], comb[M][M];
int power[N][M];
 
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
 
struct fenwick{
    int c[N];
    int power;
 
    void add(int sit, int value){
        value = 1ll * value * powermod(sit, power) % moder;
        for (++ sit; sit < N; sit += sit & -sit){
            c[sit] += value;
            c[sit] -= c[sit] >= moder ? moder : 0;
        }
    }
 
    int query(int sit){
        int ret = 0;
        for (++ sit; sit; sit -= sit & -sit){
            ret += c[sit];
            ret -= ret >= moder ? moder : 0;
        }
        return ret;
    }
};
 
fenwick f[M];
int coe[M];
 
void init(){
    for (int i = 0; i < M; ++ i){
        comb[i][0] = 1;
        for (int j = 1; j <= i; ++ j){
            comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % moder;
        }
    }
    b[0] = 1;
    for (int i = 1; i <= k; ++ i){
        for (int j = i - 1; j >= 0; -- j){
            b[j + 1] = (b[j] + 1ll * b[j + 1] * i) % moder;
        }
        b[0] = 1ll * b[0] * i % moder;
    }
    for (int i = 0; i <= k; ++ i){
        for (int j = 1; j <= k; ++ j){
            b[i] = 1ll * b[i] * powermod(j, moder - 2) % moder;
        }
    }
    for (int i = 0; i <= k; ++ i){
        f[i].power = i;
    }
    for (int i = 0; i < N; ++ i){
        power[i][0] = 1;
        for (int j = 1; j < M; ++ j){
            power[i][j] = 1ll * power[i][j - 1] * i % moder;
        }
    }
}
 
int main(){
    scanf("%d%d%d", &n, &m, &k);
    -- k;
    init();
    while (m --){
        int type;
        scanf("%d", &type);
        if (type == 0){
            int sit, value;
            scanf("%d%d", &sit, &value);
            -- sit;
            for (int i = 0; i <= k; ++ i){
                f[i].add(sit, value);
            }
        }
        else{
            int sit;
            scanf("%d", &sit);
            -- sit;
            memset(coe, 0, sizeof(coe));
            for (int j = 0; j <= k; ++ j){
                for (int u = 0; u <= j; ++ u){
                    coe[j - u] = (coe[j - u] + (j - u & 1 ? -1ll : 1ll) * b[j] * power[sit][u] % moder * comb[j][u]) % moder;
                }
            }
            int ans = 0;
            for (int i = 0; i <= k; ++ i){
                ans = (ans + 1ll * f[i].query(sit) * coe[i]) % moder;
            }
            ans += ans < 0 ? moder : 0;
            printf("%d\n", ans);
        }
    }
    return 0;
}
 
/*
4 5 1
0 1 1
1 1
1 2
1 3
1 4
*/
