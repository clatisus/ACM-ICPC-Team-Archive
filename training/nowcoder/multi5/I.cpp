#include<bits/stdc++.h>
 
const int N = 100010;
const int moder = 998244353;
typedef std::pair <int, int> pii;
typedef long long ll;
 
int x[N], y[N], tmp[N];
int c[N], left[N], right[N];
pii p[N];
 
ll comb(int n, int m){
    ll ret = 1;
    for (int i = 0; i < m; ++ i){
        ret = ret * (n - i) / (i + 1);
    }
    return ret;
}
 
void add(int sit, int value){
    for ( ; sit < N; sit += sit & -sit){
        c[sit] += value;
    }
}
 
int query(int sit){
    int ret = 0;
    for ( ; sit; sit -= sit & -sit){
        ret += c[sit];
    }
    return ret;
}
 
int main(){
    int n;
    while (scanf("%d", &n) != EOF){
        memset(c, 0, sizeof(c));
        std::map <int, int> hy;
        for (int i = 0; i < n; ++ i){
            scanf("%d%d", &x[i], &y[i]);
            tmp[i] = x[i];
            ++ hy[y[i]];
        }
        std::sort(tmp, tmp + n);
        int cnt = std::unique(tmp, tmp + n) - tmp;
        for (int i = 0; i < n; ++ i){
            p[i] = {y[i], std::lower_bound(tmp, tmp + cnt, x[i]) - tmp + 1};
        }
        std::sort(p, p + n);
        for (int i = 0, nowy; i < n; ){
            nowy = p[i].first;
            for (int j = i; j < n && p[j].first == nowy; ++ j){
                left[j] = query(N - p[j].second - 1);
            }
            while(i < n && p[i].first == nowy){
                add(N - p[i].second, 1);
                ++ i;
            }
        }
        memset(c, 0, sizeof(c));
        for (int i = n - 1, nowy; i >= 0; ){
            nowy = p[i].first;
            for (int j = i; j >= 0 && p[j].first == nowy; -- j){
                right[j] = query(N - p[j].second - 1);
            }
            while(i >= 0 && p[i].first == nowy){
                add(N - p[i].second, 1);
                -- i;
            }
        }
        ll ans = 0;
        for (int i = 0; i < n; ++ i){
            ans += 1ll * left[i] * right[i];
        }
        ans += comb(n, 2);
        ans += n;
        for (auto u : hy){
            ans -= comb(u.second, 2);
        }
        printf("%lld\n", ans % moder);
    }
    return 0;
}
