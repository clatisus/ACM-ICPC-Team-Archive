#include<bits/stdc++.h>

typedef long long ll;
const int N = 100;

ll u[N], v[N];

int main(){
    int a, b, c;
    ll k;
    scanf("%d%d%d", &a, &b, &c);
    scanf("%lld", &k);
    printf("%d\n", k & 1 ? b - a : a - b);
    return 0;
}
