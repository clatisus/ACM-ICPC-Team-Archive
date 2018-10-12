#include<bits/stdc++.h>

const int N = 200010;
typedef long long ll;

int a[N];
ll pre[N];

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i){
        scanf("%d", &a[i]);
        pre[i] = pre[i - 1] + a[i];
    }
    ll min = LLONG_MAX;
    for (int i = 2; i <= n - 2; ++ i){
        int sit1 = std::lower_bound(pre + 1, pre + i + 1, pre[i] / 2) - pre;
        ll ans1 = LLONG_MAX;
        for (int j = sit1 - 5; j <= sit1 + 5; ++ j){
            if (j >= 1 && j < i){
                ans1 = std::min(ans1, std::max(pre[j], pre[i] - pre[j]));
            }
        }
        int sit2 = std::lower_bound(pre + i + 1, pre + n + 1, pre[i] + (pre[n] - pre[i]) / 2) - pre;
        ll ans2 = LLONG_MAX;
        for (int j = sit2 - 5; j <= sit2 + 5; ++ j){
            if (j > i && j < n){
                ans2 = std::min(ans2, std::max(pre[j] - pre[i], pre[n] - pre[j]));
            }
        }
        min = std::min(min, std::max(ans1, ans2) - std::min(pre[i] - ans1, pre[n] - pre[i] - ans2));
    }
    printf("%lld\n", min);
    return 0;
}
