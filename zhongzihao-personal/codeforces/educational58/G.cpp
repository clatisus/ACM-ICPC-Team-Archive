#include<bits/stdc++.h>

const int N = 200010;

int a[N], pre[N];

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i){
        scanf("%d", &a[i]);
        pre[i] = pre[i - 1] ^ a[i];
    }
    std::swap(pre[n], pre[0]);
    if (!pre[0]){
        puts("-1");
        return 0;
    }
    int bit;
    for (int i = 0; i < 30; ++ i){
        if (pre[0] >> i & 1){
            bit = i;
            break;
        }
    }
    for (int i = 1; i < n; ++ i){
        if (pre[i] >> bit & 1){
            pre[i] ^= pre[0];
        }
    }
    int cnt = 1;
    for (int i = 29; i >= 0; -- i){
        if (i == bit){
            continue;
        }
        for (int j = cnt; j <= n; ++ j){
            if (pre[j] >> i & 1){
                std::swap(pre[cnt], pre[j]);
                break;
            }
        }
        if (!(pre[cnt] >> i & 1)){
            continue;
        }
        for (int j = cnt + 1; j <= n; ++ j){
            if (pre[j] >> i & 1){
                pre[j] ^= pre[cnt];
            }
        }
        ++ cnt;
    }
    printf("%d\n", cnt);
    return 0;
}
