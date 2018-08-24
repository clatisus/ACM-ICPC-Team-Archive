#include<bits/stdc++.h>

const int moder = 1e9 + 7;
const int N = 300010;

int powermod(int a, int exp){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * ret * a % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

char s[N];

int main(){
    int n, m;
    scanf("%d%d%s", &n, &m, s);
    int now = 0, cnt = 0;
    for (int i = 0; i < n; ++ i){
        now = (now * 10 + s[i] - '0') % m;
        cnt += !now;
        if (i == n - 1 && now){
            puts("0");
            return 0;
        }
    }
    printf("%d\n", powermod(2, cnt - 1));
    return 0;
}

