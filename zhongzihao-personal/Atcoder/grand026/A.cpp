#include<bits/stdc++.h>

const int N = 110;

int a[N];

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
        scanf("%d", &a[i]);
    }
    int pre = 0, ans = 0;
    for (int i = 0; i < n; ++ i){
        if (a[i] != a[i + 1]){
            ans += i - pre + 1 >> 1;
            pre = i + 1;
        }
    }
    printf("%d\n", ans);
    return 0;
}
