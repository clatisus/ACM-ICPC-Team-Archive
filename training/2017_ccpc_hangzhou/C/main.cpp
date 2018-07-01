#include<bits/stdc++.h>

void solve(){
    int n, d;
    scanf("%d%d", &n, &d);
    int cnt = 0;
    for (int i = 0, x; i < n; ++ i){
        scanf("%d", &x);
        cnt += x >= 2;
    }
    if (n == 1){
        puts(d == 1 ? "Yes" : "No");
        return;
    }
    if (n == 2){
        puts("Yes");
        return;
    }
    if (cnt >= 2){
        puts("Yes");
        return;
    }
    if (cnt == 1){
        if (d == 1){
            puts("Yes");
            return;
        }
        puts((n - 1) % 3 == 0 || n % 3 == 0 ? "No" : "Yes");
        return;
    }
    if (d == 1){
        puts(n % 3 == 0 ? "No" : "Yes");
        return;
    }
    puts(n % 3 == 1 ? "No" : "Yes");
}

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        solve();
    }
    return 0;
}

