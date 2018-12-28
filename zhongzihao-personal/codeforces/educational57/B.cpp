#include<bits/stdc++.h>

const int N = 200010;
const int moder = 998244353;

char s[N];

int main(){
    int ans = 1;
    int n;
    scanf("%d%s", &n, s);
    for (int i = 0; i < 26; ++ i){
        int left = -1, right = -1;
        for (int j = 0; j < n; ++ j){
            if (s[j] != 'a' + i){
                left = j;
                break;
            }
        }
        for (int j = n - 1; j >= 0; -- j){
            if (s[j] != 'a' + i){
                right = j;
                break;
            }
        }
        if (left != -1){
            ans = (ans + 1ll * (left + 1) * (n - right) - 1) % moder;
            ans += ans < 0 ? moder : 0;
        }
    }
    printf("%d\n", ans);
    return 0;
}
