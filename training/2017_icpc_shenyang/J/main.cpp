#include<bits/stdc++.h>

typedef unsigned long long ull;
const int N = 200;
const int BIT = 19;
const int MAX = 1000;
const int MAX2 = 1000000;
const int moder = (int) 1e9 + 9;
typedef std::pair <ull, int> pui;

struct DP{
    ull cnt;
    int last;
    int sum;
};

DP dp[BIT][N][N];
int a[MAX2], ans[MAX2];
ull power[BIT];

int bitcount(ull n){
    int ret = 0;
    while (n){
        ret += n % 10;
        n /= 10;
    }
    return ret;
}

void init(){
    power[0] = 1;
    for (int i = 1; i < BIT; ++ i){
        power[i] = power[i - 1] * 10;
    }
    a[1] = ans[1] = 1;
    for (int i = 2; i < MAX2; ++ i){
        a[i] = a[i - 1] + bitcount(a[i - 1]);
        ans[i] = ans[i - 1] + a[i];
        ans[i] -= ans[i] >= moder ? moder : 0;
    }
    for (int i = 0; i < N; ++ i){
        for (int j = 0; j < N; ++ j){
            if (!i && !j) continue;
            ull cnt = 0;
            int x = j, sum = 0;
            while (x < MAX){
                ++ cnt;
                sum += x;
                x += i + bitcount(x);
            }
            dp[3][i][j] = {cnt, x - MAX, sum};
        }
    }
    for (int i = 4; i < BIT; ++ i){
        for (int j = 0; j < N; ++ j){
            for (int k = 0; k < N; ++ k){
                if (!j && !k) continue;
                ull cnt = 0;
                int x = k, sum = 0;
                bool flag = true;
                for (int u = 0; u < 10; ++ u){
                    if (j + u >= N || x >= N){
                        flag = false;
                        break;
                    }
                    cnt += dp[i - 1][j + u][x].cnt;
                    sum += dp[i - 1][j + u][x].sum;
                    sum -= sum >= moder ? moder : 0;
                    sum = (sum + (u * power[i - 1] % moder) * (dp[i - 1][j + u][x].cnt % moder)) % moder;
                    x = dp[i - 1][j + u][x].last;
                }
                if (!flag){
                    dp[i][j][k] = {0, 0, 0};
                }
                else{
                    dp[i][j][k] = {cnt, x, sum};
                }
            }
        }
    }
}

pui solve(ull n){
    if (n < MAX2){
        return {a[n], ans[n]};
    }
    //for (int i = 1; i <= 100; ++ i){
    //    printf("i = %d, ai = %d\n", i, a[i]);
    //} 
    ull nown = 14, nowans = 101;
    int nowsum = ans[nown - 1];
    for (int i = BIT - 1; ; -- i){
        while (true){
            if (n - nown < 100){
                nowsum = (nowsum + nowans) % moder;
                for (int i = 0; i < n - nown; ++ i){
                    nowans += bitcount(nowans);
                    nowsum = (nowsum + nowans) % moder;
                }
                return {nowans, nowsum};
            }
            int bitcnt = bitcount(nowans / power[i]);
            int nowx = nowans % 1000;
            if (nown + dp[i][bitcnt][nowx].cnt > n){
                break;
            }
            nown += dp[i][bitcnt][nowx].cnt;
            nowsum = (nowsum + (nowans / power[i] * power[i] % moder) * (dp[i][bitcnt][nowx].cnt % moder)) % moder;
            nowans = nowans / 1000 * 1000 + power[i] + dp[i][bitcnt][nowx].last;
            nowsum += dp[i][bitcnt][nowx].sum;
            nowsum -= nowsum >= moder ? moder : 0;
        }
    }
}

int main(){
    init();
    int test;
    for (int i = 1; i <= 10000; ++ i){
        //printf("i = %d, sumi = %d\n", i, ans[i]);
    }
    scanf("%d", &test);
    for (int i = 1; i <= test; ++ i){
        ull n;
        scanf("%llu", &n);
        pui p = solve(n);
        printf("Case #%d: %llu %d\n", i, p.first, p.second);
    }
    return 0;
}
