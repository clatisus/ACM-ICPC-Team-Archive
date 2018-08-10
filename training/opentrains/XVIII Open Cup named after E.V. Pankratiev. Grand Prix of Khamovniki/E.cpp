#include<bits/stdc++.h>

const int moder = 998244353;
const int root = 3;
const int invroot = (moder + 1) / 3;
const int N = 1000010;

typedef long long ll;
typedef unsigned uint;

int powermod(int a, int exp, int moder){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * a * ret % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

void NTT(int *a, int length, int type, int moder, int root){
    if (length == 1) return;
    for(int i = 1, j = 0; i < length - 1; ++ i){
        for(int s = length; j ^= s >>= 1, ~j & s; )
            ;
        if(i < j){
            std::swap(a[i], a[j]);
        }
    }
    std::vector <int> w(length);
    w[0] = 1, w[1] = powermod(root, (moder - 1) / length, moder);
    for (int i = 2; i < length; ++ i){
        w[i] = 1ll * w[i - 1] * w[1] % moder;
    }
    for (int i = 2; i <= length; i <<= 1){
        for (int j = 0; j < length; j += i){
            int *u = a + j;
            for (int k = 0; k < i / 2; ++ k){
                int t = 1ll * w[length / i * k] * u[k + i / 2] % moder;
                u[k + i / 2] = u[k] - t + (u[k] - t < 0 ? moder : 0);
                u[k] += t; u[k] -= u[k] >= moder ? moder : 0;
            }
        }
    }
    if (type == 1) return;
    int inv = powermod(length, moder - 2, moder);
    for (int i = 0; i < length; ++ i){
        a[i] = (ll) a[i] * inv % moder;
    }
}

void mult(int *a, int *b, int lena, int lenb){
    int n = lena + lenb;
    int lengthret = 1;
    for ( ; lengthret <= n; lengthret <<= 1)
        ;
    std::fill(a + lena + 1, a + lengthret, 0);
    static int tmp[N];
    memset(tmp, 0, sizeof(tmp));
    memcpy(tmp, b, sizeof(int) * (lenb + 1));
    NTT(a, lengthret, 1, moder, root);
    NTT(tmp, lengthret, 1, moder, root);
    for (int i = 0; i < lengthret; ++ i){
        a[i] = 1ll * a[i] * tmp[i] % moder;
    }
    NTT(a, lengthret, -1, moder, invroot);
}

void add(int *a, int x){
    a[0] += x;
    int now = 0;
    while (a[now] >= 10){
        a[now + 1] += a[now] / 10;
        a[now] %= 10;
        ++ now;
    }
}

int d[N], b[N], dd[N];

int main(){
    int l;
    uint s;
    scanf("%d%u", &l, &s);
    for (int i = 0; i < l; ++ i){
        d[i] = (s >> 10) % 10;
        s = 747796405 * s - 1403630843;
    }
    std::reverse(d, d + l);
    int remain = 0;
    for (int i = 0; i < l; ++ i){
        d[i] = 9 * d[i] + remain;
        remain = d[i] / 10;
        d[i] %= 10;
    }
    if (remain){
        d[l ++] = remain;
    }
    memcpy(dd, d, sizeof(d));
    int ll = l;
    std::reverse(d, d + l);
    for (int i = 2; i < l; ++ i){
        for (int j = i; j < l; j += i){
            ++ b[j];
        }
    }
    mult(d, b, l - 1, l - 1);
    std::fill(d + l, d + N, 0);
    std::reverse(d, d + l);
    for (int i = 0; i < l; ++ i){
        d[i + 1] += d[i] / 10;
        d[i] %= 10;
    }
    while (d[l]){
        d[l + 1] += d[l] / 10;
        d[l] %= 10;
        ++ l;
    }
    for ( ; l && !d[l - 1]; -- l);
    const int MAX = 20;
    for (int i = 2; i <= ll; ++ i){
        __int128 sum = 0;
        for (int j = i - 1; j < ll + i; j += i){
            __int128 total = 0;
            for (int k = 0; k < MAX; ++ k){
                total = total * 10 + (k >= i ? 0 : dd[j - k]);
            }
            sum += total;
        }
        __int128 div = 0;
        for (int j = 0; j < MAX; ++ j){
            div = div * 10 + (j >= i ? 0 : 9);
        }
        add(d, sum / div);
    }
    l = N - 1;
    for ( ; l && !d[l - 1]; -- l);
    if (!l){
        puts("0");
    }
    else{
        for (int i = l - 1; i >= 0; -- i){
            putchar('0' + d[i]);
        }
        putchar('\n');
    }
    return 0;
}
