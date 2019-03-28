#include<bits/stdc++.h>

const int N = 30;
typedef long long ll;

ll comb[N][N];

double power(double a, int exp){
    double ret = 1.0;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret *= a;
        }
        a *= a;
    }
    return ret;
}

int main(){
    for (int i = 0; i < N; ++ i){
        comb[i][0] = 1;
        for (int j = 1; j <= i; ++ j){
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
        }
    }
    std::map <double, ll> map;
    int n;
    scanf("%d", &n);
    double p[4];
    for (int i = 0; i < 4; ++ i){
        scanf("%lf", &p[i]);
    }
    for (int i = 0; i <= n; ++ i){
        for (int j = 0; i + j <= n; ++ j){
            for (int k = 0; i + j + k <= n; ++ k){
                int u = n - i - j - k;
                map[power(p[0], i) * power(p[1], j) * power(p[2], k) * power(p[3], u)] +=
                        comb[n][i] * comb[n - i][j] * comb[n - i - j][k];
            }
        }
    }
    double ans = 0;
    while (true){
        if (map.size() == 1 && map.begin() -> second == 1){
            break;
        }
        auto u = map.begin();
        if (u -> second > 1){
            ans += 2.0 * u -> first * (u -> second >> 1);
            map[u -> first * 2] += u -> second >> 1;
            map.begin() -> second &= 1;
            if (!(map.begin() -> second)){
                map.erase(map.begin());
            }
            continue;
        }
        double prob = u -> first;
        map.erase(map.begin());
        u = map.begin();
        prob += u -> first;
        ans += prob;
        -- u -> second;
        if (!(u -> second)){
            map.erase(map.begin());
        }
        map[prob] += 1;
    }
    printf("%.15f\n", ans);
    return 0;
}
