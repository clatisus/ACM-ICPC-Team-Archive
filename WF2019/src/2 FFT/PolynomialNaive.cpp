std::vector <int> interpolation(std::vector <int> x, std::vector <int> y){
    int n = (int) x.size() - 1;
    std::vector <int> dp(n + 2);
    dp[0] = 1;
    for (int i = 0; i <= n; ++ i){
        for (int j = i + 1; j >= 0; -- j){
            dp[j] = (1ll * dp[j] * -x[i] + (j ? dp[j - 1] : 0)) % moder;
        }
    }
    std::vector <int> ret(n + 1);
    for (int i = 0; i <= n; ++ i){
        int coe = 1, coe1 = 0;
        for (int j = 0; j <= n; ++ j){
            if (i != j) coe = 1ll * coe * (x[i] - x[j]) % moder;
        }
        coe = 1ll * powermod(coe, moder - 2) * y[i] % moder;
        for (int j = n; j >= 0; -- j){
            coe1 = (dp[j + 1] + 1ll * coe1 * x[i]) % moder;
            ret[j] = (ret[j] + 1ll * coe * coe1) % moder;
        }
    }
    for (int i = 0; i <= n; ++ i){
        ret[i] += ret[i] < 0 ? moder : 0;
    }
    return ret;
}
static int interpolation(std::vector <int> vec, int x){
    int n = vec.size() - 1;
    if (x >= 0 && x <= n) return vec[x];
    std::vector <int> pre(n + 1), suf(n + 1);
    pre[0] = suf[n] = 1;
    for (int i = 1; i <= n; ++ i){
        pre[i] = 1ll * pre[i - 1] * (x - i + 1) % moder;
        pre[i] += pre[i] < 0 ? moder : 0;
    }
    for (int i = n - 1; i >= 0; -- i){
        suf[i] = 1ll * suf[i + 1] * (x - i - 1) % moder;
        suf[i] += suf[i] < 0 ? moder : 0;
    }
    int ans = 0;
    for (int i = 0; i <= n; ++ i)
        ans = (ans + ((n - i) & 1 ? -1ll : 1ll) * vec[i] * pre[i] % moder * suf[i] % moder * invf[i] % moder * invf[n - i]) % moder;
    ans += ans < 0 ? moder : 0;
    return ans;
}
