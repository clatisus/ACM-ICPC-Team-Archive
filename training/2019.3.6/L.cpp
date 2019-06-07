#include<bits/stdc++.h>

const int moder = (int) 1e9 + 7;
const int N = 6010;
typedef long long ll;

int powermod(int a, ll exp, int mod = moder) {
    int ret = 1;
    for (; exp > 0; exp >>= 1) {
        if (exp & 1) {
            ret = 1ll * ret * a % mod;
        }
        a = 1ll * a * a % mod;
    }
    return ret;
}

int main() {
    std::vector<int> vec;
    int b = powermod(4, moder - 2);
    for (int i = 0; i < N; ++i) {
        vec.push_back(b);
        b = (b - 1ll * b * b) % moder;
        b += b < 0 ? moder : 0;
    }
    int begin = -1, end = -1;
    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < i; ++j) {
            if (vec[j] == vec[i]) {
                begin = j, end = i;
                break;
            }
        }
        if (begin != -1) {
            break;
        }
    }
    ll n;
    scanf("%lld", &n);
    ll tmp = n - 1;
    if (tmp >= begin) {
        tmp = begin + (tmp - begin) % (end - begin);
    }
    int ans = 1ll * vec[tmp] * powermod(2, powermod(2, n, moder - 1)) % moder;
    int ans2 = powermod(2, powermod(2, n, moder - 1) - 2 + moder - 1);
    printf("%d %d\n", ans, ans2);
    return 0;
}
