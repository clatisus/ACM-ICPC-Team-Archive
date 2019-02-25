#include<bits/stdc++.h>

const int N = 1000010;
const int moder = 998244353;

int min[N], ans[N];
std::vector <int> prime;

int main(){
    for (int i = 2; i < N; ++ i){
        if (!min[i]){
            min[i] = i;
            prime.push_back(i);
        }
        for (auto u : prime){
            int x = i * u;
            if (x >= N) break;
            min[x] = u;
            if (i % u == 0) break;
        }
    }
    for (int i = 1; i < N - 1; ++ i){
        ans[i] = 1;
        int x = i;
        while (x > 1){
            int cnt = 0, tmp = min[x];
            while (x % tmp == 0){
                x /= tmp;
                ++ cnt;
            }
            ans[i] = 1ll * ans[i] * (cnt + 1) % moder;
        }
        x = i + 1;
        while (x > 1){
            int cnt = 0, tmp = min[x];
            while (x % tmp == 0){
                x /= tmp;
                ++ cnt;
            }
            ans[i] = 1ll * ans[i] * (cnt * i + 1) % moder;
        }
        ans[i] += ans[i - 1];
        ans[i] -= ans[i] >= moder ? moder : 0;
    }
    int test;
    scanf("%d", &test);
    for (int i = 1; i <= test; ++ i){
        int x;
        scanf("%d", &x);
        printf("Case #%d: %d\n", i, ans[x]);
    }
    return 0;
}
