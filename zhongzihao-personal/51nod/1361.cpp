#include<bits/stdc++.h>

typedef long long ll;
typedef __int128 i128;

int moder;

struct Root{
    int x, y, a;

    Root(int x, int y, int a):x(x), y(y), a(a){}

    Root operator *(const Root &r)const{
        int newx = (1ll * x * r.x + 1ll * y * r.y % moder * a) % moder;
        int newy = (1ll * x * r.y + 1ll * y * r.x) % moder;
        return Root(newx, newy, a);
    }

    Root powermod(ll exp)const{
        Root ret(1, 0, a), x = *this;
        for ( ; exp > 0; exp >>= 1){
            if (exp & 1){
                ret = ret * x;
            }
            x = x * x;
        }
        return ret;
    }
};

ll powermod(ll a, ll exp, ll moder){
    ll ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = (i128) ret * a % moder;
        }
        a = (i128) a * a % moder;
    }
    return ret;
}

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        ll n;
        scanf("%lld%d", &n, &moder);
        if (moder == 2 || moder == 3){
            puts("1");
            continue;
        }
        if (moder == 13){
            puts(n == 1 ? "1" : "6");
            continue;
        }
        ll phi = 1ll * (powermod(13, moder - 1 >> 1, moder) == 1 ? moder - 1 : moder + 1) * (moder - 1);
        ll exp = powermod(2, n - 1, phi);
        int inv6 = powermod(6, moder - 2, moder);
        int inv12 = powermod(12, moder - 2, moder);
        Root r(11ll * inv12 % moder, 3ll * inv12 % moder, 13);
        Root r1 = r.powermod(exp) * Root(powermod(6, exp - 1 + phi, moder), 0, 13);
        Root r2 = r.powermod(phi - exp) * Root(powermod(6, phi - exp - 1, moder), 0, 13);
        assert((r1.y + r2.y) % moder == 0);
        int ans = (r1.x + r2.x - 5ll * inv6) % moder;
        ans += ans < 0 ? moder : 0;
        printf("%d\n", ans);
    }
    return 0;
}
