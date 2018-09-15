#include<bits/stdc++.h>

typedef long long ll;

const int N = 30;
inline ll sqr(int n){return 1ll * n * n;}

ll a[N], b[N];
ll mat[N][N];

int main(){
    int n, m;
    scanf("%d%d", &m, &n);
    ll sum = 0;
    int now = 2;
    for (int i = 0; i < n - 2; ++ i){
        a[i] = sqr(now ++);
        sum += a[i];
    }
    if ((sum & 1) == (now & 1)){
        ++ now;
    }
    a[n - 2] = sqr(now);
    sum += a[n - 2];
    a[n - 1] = sqr(sum >> 1);
    sum = 0;
    ++ now;
    std::set <ll> set;
    for (int i = 0; i < m - 2; ++ i){
        while (true){
            bool flag = true;
            for (int j = 0; j < n; ++ j){
                if (set.count(a[j] * sqr(now))){
                    flag = false;
                    break;
                }
            }
            if (flag){
                break;
            }
            ++ now;
        }
        b[i] = sqr(now ++);
        sum += b[i];
        for (int j = 0; j < n; ++ j){
            set.insert(a[j] * b[i]);
        }
    }
    if ((sum & 1) == (now & 1)){
        ++ now;
    }
    while (true){
        bool flag = true;
        for (int j = 0; j < n; ++ j){
            if (set.count(a[j] * sqr(now))){
                flag = false;
                break;
            }
        }
        if (flag){
            break;
        }
        now += 2;
    }
    b[m - 2] = sqr(now);
    sum += b[m - 2];
    for (int j = 0; j < n; ++ j){
        set.insert(a[j] * b[m - 2]);
    }
    b[m - 1] = sqr(sum >> 1);
    set.clear();
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < m; ++ j){
            mat[i][j] = a[i] * b[j];
            assert(!set.count(mat[i][j]));
            set.insert(mat[i][j]);
        }
    }
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < m; ++ j){
            printf("%lld%c", mat[i][j], " \n"[j == m - 1]);
        }
    }
    return 0;
}
