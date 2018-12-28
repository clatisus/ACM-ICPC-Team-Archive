#include<bits/stdc++.h>

const int N = 200010;
const int moder = 998244353;

int p[N];
int vis[N];
int vpre[N], vsuf[N], spre[N], ssuf[N];
int fac[N], inv[N], invf[N];
int c[N];

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

void init(){
    fac[0] = invf[0] = 1;
    for (int i = 1; i < N; ++ i){
        fac[i] = 1ll * fac[i - 1] * i % moder;
        inv[i] = i == 1 ? 1 : moder - 1ll * (moder / i) * inv[moder % i] % moder;
        invf[i] = 1ll * invf[i - 1] * inv[i] % moder;
    }
}

int main(){
    init();
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i){
        scanf("%d", &p[i]);
        if (p[i] != -1){
            vis[p[i]] = i;
        }
    }
    for (int i = 1; i <= n; ++ i){
        vpre[i] = vpre[i - 1];
        if (!vis[i]){
            ++ vpre[i];
        }
    }
    for (int i = n; i >= 1; -- i){
        vsuf[i] = vsuf[i + 1];
        if (!vis[i]){
            ++ vsuf[i];
        }
    }
    for (int i = 1; i <= n; ++ i){
        spre[i] = spre[i - 1];
        if (p[i] == -1){
            ++ spre[i];
        }
    }
    for (int i = n; i >= 1; -- i){
        ssuf[i] = ssuf[i + 1];
        if (p[i] == -1){
            ++ ssuf[i];
        }
    }
    int ans = 0;
    for (int i = n; i >= 1; -- i){
        if (vis[i]){
            ans += query(vis[i]);
            ans -= ans >= moder ? moder : 0;
            add(vis[i], 1);
        }
    }
    int cnt = spre[n];
    ans = 1ll * ans * fac[cnt] % moder;
    if (!cnt){
        printf("%d\n", ans);
        return 0;
    }
    for (int i = 1; i <= n; ++ i){
        if (vis[i]){
            ans = (ans + (1ll * spre[vis[i]] * vsuf[i] + 1ll * ssuf[vis[i]] * vpre[i]) % moder * fac[cnt - 1]) % moder;
        }
    }
    if (cnt >= 2){
        ans = (ans + (1ll * cnt * (cnt - 1) / 2 % moder) * (1ll * cnt * (cnt - 1) / 2 % moder) % moder * fac[cnt - 2]) % moder;
    }
    ans = 1ll * ans * invf[cnt] % moder;
    printf("%d\n", ans);
    return 0;
}
