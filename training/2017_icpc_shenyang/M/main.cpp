#include<bits/stdc++.h>

typedef std::pair <int, int> pii;
const int N = 1010;

int x[N], y[N];
int n;

int type(int x, int y){
    return 5 + 2 * !(x == 0 || x == n - 1) + 2 * !(y == 0 || y == n - 1);
}

pii solve(){
    int k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < k; ++ i){
        scanf("%d%d", &x[i], &y[i]);
    }
    if (n == 1){
        return {1, 1};
    }
    std::set <pii> set;
    int p = 3 * 3 + (2 * n - 4) * 4 + (n * (n + 1) / 2 - (2 * n - 1)) * 5;
    for (int i = 0; i < k; ++ i){
        if (x[i] + y[i] >= n){
            p -= type(x[i], y[i]);
        }
        if (x[i] + y[i] == n - 1){
            p -= !x[i] || !y[i] ? 4 : 7;
        }
        if (x[i] + y[i] == n - 2){
            p -= 2;
        }
        if (x[i] + y[i] >= n - 2){
            set.insert({x[i], y[i]});
        }
    }
    for (int i = 0; i < k; ++ i){
        if (x[i] + y[i] >= n - 2){
            if (set.count({x[i], y[i] + 1})){
                p += x[i] + y[i] == n - 2 ? 1 : 2;
            }
            if (set.count({x[i] + 1, y[i]})){
                p += x[i] + y[i] == n - 2 ? 1 : 2;
            }
        }
    }
    set.clear();
    int q = 4 * 3 + (4 * n - 8) * 4 + ((n - 2) * (n - 2)) * 5;
    for (int i = 0; i < k; ++ i){
        q -= type(x[i], y[i]);
        set.insert({x[i], y[i]});
    }
    for (int i = 0; i < k; ++ i){
        if (set.count({x[i], y[i] + 1})){
            q += 2;
        }
        if (set.count({x[i] + 1, y[i]})){
            q += 2;
        }
    }
    int gcd = std::__gcd(p, q);
    p /= gcd, q /= gcd;
    return {p, q};
}

int main(){
    int test;
    scanf("%d", &test);
    for (int i = 1; i <= test; ++ i){
        pii p = solve();
        printf("Case #%d: %d/%d\n", i, p.first, p.second);
    }
    return 0;
}
