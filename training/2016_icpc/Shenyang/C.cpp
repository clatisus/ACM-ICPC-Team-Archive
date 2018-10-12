#include<bits/stdc++.h>

typedef long long ll;
const ll moder = 2147493647;
const int N = 10;

struct matrix{
    int n;
    ll a[N][N];

    matrix (int n):n(n){memset(a, 0, sizeof(a));}

    matrix operator *(const matrix &m)const{
        matrix ret(n);
        for (int k = 0; k < n; ++ k){
            for (int i = 0; i < n; ++ i){
                for (int j = 0; j < n; ++ j){
                    ret.a[i][j] = (ret.a[i][j] + a[i][k] * m.a[k][j]) % moder;
                }
            }
        }
        return ret;
    }

    ll *operator [](const int &x){return a[x];}
    
    matrix power(int exp){
        matrix ret(n), a = *this;
        for (int i = 0; i < n; ++ i){
            ret.a[i][i] = 1;
        }
        for ( ; exp > 0; exp >>= 1){
            if (exp & 1){
                ret = ret * a;
            }
            a = a * a;
        }
        return ret;
    }
};

void solve(){
    int n, a, b;
    scanf("%d%d%d", &n, &a, &b);
    matrix trans(7);
    trans[0][1] = 1;
    trans[1][0] = 2;
    trans[1][1] = trans[1][6] = 1;
    for (int i = 2; i < 7; ++ i){
        trans[i][2] = 1;
        for (int j = 3; j <= i; ++ j){
            trans[i][j] = trans[i - 1][j - 1] + trans[i - 1][j];
        }
    }
    trans = trans.power(n - 1);
    ll tmp[] = {a, b, 1, 3, 9, 27, 81};
    ll ans = 0;
    for (int i = 0; i < 7; ++ i){
        ans = (ans + trans[0][i] * tmp[i]) % moder;
    }
    printf("%lld\n", ans);
}

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        solve();
    }
    return 0;
}

