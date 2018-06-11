#include<bits/stdc++.h>

const int N = 200010;

int p[N], inv[N];
int max[N];

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i){
        scanf("%d", &p[i]);
        inv[p[i]] = i;
    }
    int ans = 0;
    for (int i = n; i >= 1; -- i){
        if (inv[i + 1] > inv[i]){
            max[i] = max[i + 1] + 1;
        }
        else{
            max[i] = 1;
        }
        ans = std::max(ans, max[i]);
    }
    printf("%d\n", n - ans);
    return 0;
}
