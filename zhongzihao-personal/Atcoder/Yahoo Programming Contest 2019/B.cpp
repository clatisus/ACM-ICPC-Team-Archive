#include<bits/stdc++.h>

int cnt[10];

int main(){
    int a, b;
    for (int i = 0; i < 3; ++ i){
        scanf("%d%d", &a, &b);
        ++ cnt[a], ++ cnt[b];
    }
    int ans = 0;
    for (int i = 1; i <= 4; ++ i){
        ans += cnt[i] & 1;
    }
    puts(ans <= 2 ? "YES" : "NO");
    return 0;
}
