#include<bits/stdc++.h>

typedef unsigned long long ull;
typedef long long ll;

const int N = 10010;

int a[N];

ull decode(int *&a){
    ull ret = 0, now = 1;
    while (((*a) >> 7 & 1) != 0){
        ret += now * (*a ^ 1 << 7);
        now *= 128;
        ++ a;
    }
    ret += now * *a;
    ++ a;
    return ret;
}

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
        scanf("%d", &a[i]);
    }
    int *p = a;
    while (p != a + n){
        ull ans = decode(p);
        if (ans & 1){
            if (ans == ULLONG_MAX){
                printf("%lld\n", LLONG_MIN);
            }
            else{
                ans = ans + 1 >> 1;
                printf("%lld\n", -(ll) ans);
            }
        }
        else{
            printf("%llu\n", ans >> 1);
        }
    }
    return 0;
}
