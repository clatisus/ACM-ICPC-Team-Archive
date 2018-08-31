#include<bits/stdc++.h>

const int N = 100010;

char s[N];
bool vis[N];

void solve(){
    memset(vis, 0, sizeof(vis));
    int n = strlen(s);
    for (int i = 1; i < n; ++ i){
        if (n % i) continue;
        bool flag = false;
        for (int j = 0; j < i; ++ j){
            bool fflag = true;
            for (int k = 0; k < n / i; ++ k){
                if (s[k * i + j] != 'R'){
                    fflag = false;
                    break;
                }
            }
            if (fflag){
                flag = true;
                break;
            }
        }
        vis[i] = flag;
    }
    int cnt = 0;
    for (int i = 1; i < n; ++ i){
        if (vis[std::__gcd(i, n)]){
            ++ cnt;
        }
    }
    printf("%d\n", cnt);
}

int main(){
    while (scanf("%s", s) != EOF){
        solve();
    }
    return 0;
}

