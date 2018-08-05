#include <bits/stdc++.h>
 
#define ll long long
 
int main() {
    int c, n;
    while(~scanf("%d%d", &c, &n)) {
        int d = n / c;
        if (d == 0) {
                printf("-1\n");
        continue;
        }
        if (d == 1) {
            printf("%lld\n", 1ll * c * c);
        } else {
            printf("%lld\n", 1ll * d * (d - 1) * c * c);
        }
    }
    return 0;
}
