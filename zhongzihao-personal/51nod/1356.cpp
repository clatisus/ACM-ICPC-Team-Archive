#include<bits/stdc++.h>

const int N = 5010;
const int moder = (int) 1e9 + 7;

std::bitset <N> set[N];
std::vector <int> vec[N];
int c[N];

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0, x; i < n; ++ i){
        scanf("%d", &x);
        for (int j = 2; j * j <= x; ++ j){
            if (x % j == 0){
                int cnt = 0;
                while (x % j == 0){
                    x /= j;
                    cnt ^= 1;
                }
                if (cnt){
                    vec[i].push_back(j);

                }
            }
        }
        if (x > 1){
            vec[i].push_back(x);
        }
    }
    int cnt = 0;
    for (int i = 0; i < n; ++ i){
        for (auto u : vec[i]){
            c[cnt ++] = u;
        }
    }
    std::sort(c, c + cnt);
    cnt = std::unique(c, c + cnt) - c;
    for (int i = 0; i < n; ++ i){
        for (auto u : vec[i]){
            set[i].set(std::lower_bound(c, c + cnt, u) - c);
        }
    }
    int now = 0;
    for (int i = 0; i < N; ++ i){
        for (int j = now; j < n; ++ j){
            if (set[j].test(i)){
                std::swap(set[now], set[j]);
                break;
            }
        }
        if (!set[now].test(i)) continue;
        for (int j = now + 1; j < n; ++ j){
            if (set[j].test(i)){
                set[j] ^= set[now];
            }
        }
        ++ now;
    }
    int ans = 1;
    for (int i = 0; i < now; ++ i){
        ans <<= 1;
        ans -= ans >= moder ? moder : 0;
    }
    printf("%d\n", ans);
    return 0;
}
