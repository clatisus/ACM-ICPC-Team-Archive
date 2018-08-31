#include<bits/stdc++.h>

const int N = 1010;

int n, k;
int cnt[N];

void solve(){
    for (int i = 1; i <= k; ++ i){
        cnt[i] = 0;
    }
    for (int i = 0, x; i < n; ++ i){
        scanf("%d", &x);
        ++ cnt[x];
    }
    int target;
    if ((n + 1) % k == 0){
        target = (n + 1) / k;
    }
    if ((n - 1) % k == 0){
        target = (n - 1) / k;
    }
    if (n % k == 0){
        target = n / k;
    }
    int add = 0, minus = 0;
    for (int i = 1; i <= k; ++ i){
        if (cnt[i] <= target - 2 || cnt[i] >= target + 2){
            puts("*");
            return;
        }
        if (cnt[i] == target - 1){
            if (add){
                puts("*");
                return;
            }
            add = i;
        }
        if (cnt[i] == target + 1){
            if (minus){
                puts("*");
                return;
            }
            minus = i;
        }
    }
    if (!add){
        printf("-%d\n", minus);
    }
    if (!minus){
        printf("+%d\n", add);
    }
    if (add && minus){
        printf("-%d +%d\n", minus, add);
    }
}

int main(){
    while (scanf("%d%d", &k, &n) != EOF){
        solve();
    }
    return 0;
}
