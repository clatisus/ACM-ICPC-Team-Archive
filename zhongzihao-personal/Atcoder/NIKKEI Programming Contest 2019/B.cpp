#include<bits/stdc++.h>

const int N = 110;

char a[N], b[N], c[N];

int main(){
    int n;
    scanf("%d%s%s%s", &n, a, b, c);
    int ans = 0;
    for (int i = 0; i < n; ++ i){
        if (a[i] == b[i] && b[i] == c[i]) continue;
        if (a[i] != b[i] && a[i] != c[i] && b[i] != c[i]){
            ans += 2;
        }
        else{
            ans += 1;
        }
    }
    printf("%d\n", ans);
    return 0;
}
