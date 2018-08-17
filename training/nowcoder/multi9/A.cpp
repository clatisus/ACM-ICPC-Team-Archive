#include<bits/stdc++.h>
 
const int moder = 1e9 + 7;
 
int powermod(int a, int exp){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * ret * a % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}
 
void FWT_XOR(std::vector <int> &a, int length, int type){
    int len = -1;
    for (int x = length; x; ++ len, x >>= 1)
        ;
    for (int i = 1; i <= len; ++ i){
        for (int j = 0; j < length; j += 1 << i){
            for (int k = j, szk = 1 << (i - 1); k < j + szk; ++ k){
                int s = a[k], t = a[k + szk];
                a[k] = s + t >= moder ? s + t - moder : s + t;
                a[k + szk] = s - t < 0 ? s - t + moder : s - t;
            }
        }
    }
    if (type == 1) return;
    int inv = powermod(length, moder - 2);
    for (int i = 0; i < length; ++ i){
        a[i] = 1ll * a[i] * inv % moder;
    }
}
 
std::vector <int> solve(std::vector <int> a, std::vector <int> b){
    int n = a.size();
    if (n == 1){
        return std::vector <int> {(int)(1ll * powermod(a[0], moder - 2) * b[0] % moder)};
    }
    std::vector <int> aa(n >> 1), bb(n >> 1);
    for (int i = 0; i < n; i += 2){
        aa[i >> 1] = (a[i] + a[i + 1]) % moder;
        bb[i >> 1] = (b[i] + b[i + 1]) % moder;
    }
    std::vector <int> vec = solve(aa, bb), tmp = vec;
    std::vector <int> vvec(n >> 1);
    for (int i = 1; i < n; i += 2){
        vvec[i >> 1] = a[i];
    }
    FWT_XOR(vec, n >> 1, 1);
    FWT_XOR(vvec, n >> 1, 1);
    for (int i = 0; i < n >> 1; ++ i){
        vec[i] = 1ll * vec[i] * vvec[i] % moder;
    }
    FWT_XOR(vec, n >> 1, -1);
    for (int i = 0; i < n; i += 2){
        bb[i >> 1] = b[i] - vec[i >> 1];
        bb[i >> 1] += bb[i >> 1] < 0 ? moder : 0;
        aa[i >> 1] = a[i] - a[i + 1];
        aa[i >> 1] += aa[i >> 1] < 0 ? moder : 0;
    }
    vec = solve(aa, bb);
    std::vector <int> ret(n);
    for (int i = 0; i < n; i += 2){
        ret[i] = vec[i >> 1];
        ret[i + 1] = tmp[i >> 1] - ret[i];
        ret[i + 1] += ret[i + 1] < 0 ? moder : 0;
    }
    return ret;
}
 
int main(){
    int n;
    scanf("%d", &n);
    std::vector <int> a(n), b(n);
    for (int i = 0; i < n; ++ i){
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; ++ i){
        scanf("%d", &b[i]);
    }
    std::vector <int> vec = solve(a, b);
    for (int i = 0; i < n; ++ i){
        printf("%d\n", vec[i]);
    }
    return 0;
}
