#include<bits/stdc++.h>

const int BIT = 16;
const int N = 1 << BIT;
typedef long long ll;
const int moder = (int) 1e9 + 7;

int rev[N][BIT];

void init(){
    for (int i = 0; i < N; ++ i){
        for (int j = 0; j < BIT; ++ j){
            int x = i;
            for (int k = 0; k < j; ++ k){
                rev[i][j] = rev[i][j] << 1 | (x & 1);
                x >>= 1;
            }
        }
    }
}

int k, n;
int m, l, r;
int a, b, c;
ll h;

int reverse(int x, int k){
    if (k < BIT){
        return rev[x][k];
    }
    int low = x & 0x7fff;
    int high = x >> 15;
    int lowinv = 15;
    int highinv = k - lowinv;
    return rev[low][lowinv] << highinv | rev[high][highinv];
}

int get(int sit){
    if (!(sit & 1)){
        return reverse(sit >> 1, k);
    }
    return reverse(n - 1 - (sit >> 1), k);
}

void solve(){
    if (l & 1){
        if (l == r){
            h = get(l);
            return;
        }
        int tot = (r - l) >> 1;
        h = 1ll * tot * (n - 1);
        h += get(l);
        if (!(r & 1)){
            h += get(r);
        }
    }
    else{
        int tot = (r - l + 1) >> 1;
        h = tot & 1 ? n - 1 : 0;
        if (!(r & 1)){
            h ^= get(r);
        }
    }
}

int main(){
    init();
    scanf("%d", &k);
    n = 1 << k;
    scanf("%d%d%d", &m, &l, &r);
    scanf("%d%d%d", &a, &b, &c);
    for (int i = 0; i < m; ++ i){
        ll prevh = h;
        solve();
        h = ((l ^ r ^ h ^ prevh) + c) % moder;
        l = (l ^ a ^ h) % (n + 1) % n;
        r = (r ^ b ^ h) % (n - l) + l;
    }
    printf("%lld\n", h);
}

/*
3
1 3 7
0 0 0
*/
