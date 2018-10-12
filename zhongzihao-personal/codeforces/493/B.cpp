#include<bits/stdc++.h>

const int N = 9000;
typedef long long ll;
std::bitset <(N + 10) * 50> set;
const int M = 4;

int a[M] = {1, 5, 10, 50};
bool vis[N * 100];

int main(){
    int n;
    scanf("%d", &n);
    if (n <= N){
        set[0] = 1;
        for (int i = 0; i < n; ++ i){
            set = (set << 1) | (set << 5) | (set << 10) | (set << 50);
        }
        printf("%d\n", (int) set.count());
        return 0;
    }
    set[0] = 1;
    for (int i = 0; i <= N; ++ i){
        for (int j = 0; j <= 10 * i; ++ j){
            if (set.test(j)){
                ll x = j + 50ll * (n - i);
                if (x > 50ll * (n - (N / 5))){
                    vis[x - 50ll * (n - (N / 5))] = true;
                }
            }
        }
        set = (set << 1) | (set << 5) | (set << 10);
    }
    ll ans = 49ll * (n - (N / 5)) + 1;
    for (int i = 0; i < N * 100; ++ i){
        ans += vis[i];
    }
    printf("%lld\n", ans);
    return 0;
}
