#include<bits/stdc++.h>

const int N = 100010;

typedef long long ll;

ll x[N], p[N];

int main(){
    int n, s;
    scanf("%d%d", &n, &s);
    for (int i = 0; i < n; ++ i){
        scanf("%lld%lld", &x[i], &p[i]);
    }
    int sit = std::lower_bound(x, x + n, s) - x;
    int left = 0, right = n - 1;
    ll ans = 0;
    int previouschoice = -1;
    while (true){
        if (left == sit){
            ans += x[right] - s;
            break;
        }
        if (right == sit - 1){
            ans += s - x[left];
            break;
        }
        if ((p[left] >= p[right]) != previouschoice){
            ans += x[right] - x[left];
            previouschoice = p[left] >= p[right];
        }
        if (p[left] >= p[right]){
            p[left] += p[right];
            -- right;
        }
        else{
            p[right] += p[left];
            ++ left;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
