#include<bits/stdc++.h>

const int N = 310;
const int moder = 998244353;

std::bitset <N> set[N];
int power[N];

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < m; ++ j){
            int x;
            scanf("%d", &x);
            set[i][j] = x;
        }
    }
    int now = 0;
    for (int i = 0; i < m; ++ i){
        for (int j = now; j < n; ++ j){
            if (set[j][i]){
                std::swap(set[now], set[j]);
                break;
            }
        }
        if (!set[now][i]){
            continue;
        }
        for (int j = now + 1; j < n; ++ j){
            if (set[j][i]){
                set[j] ^= set[now];
            }
        }
        ++ now;
    }
    power[0] = 1;
    for (int i = 1; i < N; ++ i){
        power[i] = 2 * power[i - 1] % moder;
    }
    int ans = (1ll * power[n] * (power[m - 1]) - 1ll * power[n - now] * power[m - 1]) % moder;
    ans += ans < 0 ? moder : 0;
    printf("%d\n", ans);
    return 0;
}
