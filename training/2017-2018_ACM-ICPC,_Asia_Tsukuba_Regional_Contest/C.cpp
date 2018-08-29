#include <bits/stdc++.h>

#define MAXN (100010)
#define ll long long

int n, t;

int main() {
    scanf("%d%d", &n, &t);
    int pre = 0;
    ll sum = 0;
    for (int i = 1; i <= n; ++i) {
        int h;
        scanf("%d", &h);
        pre = std::max(pre, h);
        sum += h;
        if (t < sum) printf("1\n");
        else printf("%lld\n", (t - sum) / pre + 2);
    }
    return 0;
}
/*
3 1
4
5
6

*/

