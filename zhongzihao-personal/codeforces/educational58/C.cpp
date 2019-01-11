#include<bits/stdc++.h>

const int N = 100010;

struct inter{
    int l, r, id;

    bool operator <(const inter &i)const{
        return r < i.r;
    }
};

inter a[N];
int ans[N], suf[N];

void solve(){
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i){
        scanf("%d%d", &a[i].l, &a[i].r);
        a[i].id = i;
    }
    std::sort(a + 1, a + n + 1);
    suf[n + 1] = INT_MAX;
    for (int i = n; i >= 1; -- i){
        suf[i] = std::min(suf[i + 1], a[i].l);
    }
    for (int i = 1; i < n; ++ i){
        if (a[i].r < suf[i + 1]){
            for (int j = 1; j <= i; ++ j){
                ans[a[j].id] = 1;
            }
            for (int j = i + 1; j <= n; ++ j){
                ans[a[j].id] = 2;
            }
            for (int j = 1; j <= n; ++ j){
                printf("%d%c", ans[j], " \n"[j == n]);
            }
            return;
        }
    }
    puts("-1");
}

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        solve();
    }
    return 0;
}
