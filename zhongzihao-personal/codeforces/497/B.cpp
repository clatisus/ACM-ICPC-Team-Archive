#include<bits/stdc++.h>

const int N = 100010;
typedef long long ll;

std::vector <int> vec[N];

ll comb(int n, int m){
    ll ret = 1;
    for (int i = 0; i < m; ++ i){
        ret *= n - i;
    }
    for (int i = 1; i <= m; ++ i){
        ret /= i;
    }
    return ret;
}

void calc(int *cnt, int a, int b, int c){
    for (auto u : vec[a]){
        int x = b % u == 0;
        int y = c % u == 0;
        ++ cnt[y << 1 | x];
    }
}

ll solve(){
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    int cnt[3][4] = {}, sit[3][4];
    calc(cnt[0], a, b, c);
    sit[0][0] = 0, sit[0][1] = 1, sit[0][2] = 2, sit[0][3] = 3;
    calc(cnt[1], b, a, c);
    sit[1][0] = 4, sit[1][1] = 1, sit[1][2] = 5, sit[1][3] = 3;
    calc(cnt[2], c, a, b);
    sit[2][0] = 6, sit[2][1] = 2, sit[2][2] = 5, sit[2][3] = 3;
    ll ans = 0, ans2 = 0;
    for (int i = 0; i < 4; ++ i){
        for (int j = 0; j < 4; ++ j){
            for (int k = 0; k < 4; ++ k){
                int x = (sit[0][i] == sit[1][j]) + (sit[1][j] == sit[2][k]) + (sit[0][i] == sit[2][k]);
                int cnt3 = (i == 3) + (j == 3) + (k == 3);
                if (x < 3){
                    ++ x;
                }
                if (x == 3){
                    ans += comb(cnt[0][i] + x - 1, x);
                }
                else if (x == 2){
                    if (sit[0][i] == sit[1][j]){
                        ans += comb(cnt[0][i] + x - 1, x) * cnt[2][k];
                    }
                    if (sit[0][i] == sit[2][k]){
                        ans += comb(cnt[0][i] + x - 1, x) * cnt[1][j];
                    }
                    if (sit[2][k] == sit[1][j]){
                        ans += comb(cnt[1][j] + x - 1, x) * cnt[0][i];
                    }
                }
                else{
                    ans += 1ll * cnt[0][i] * cnt[1][j] * cnt[2][k];
                }
            }
        }
    }
    return ans + ans2 / 2;
}

int main(){
    for (int i = 1; i < N; ++ i){
        for (int j = i; j < N; j += i){
            vec[j].push_back(i);
        }
    }
    int test;
    scanf("%d", &test);
    while (test --){
        printf("%lld\n", solve());
    }
    return 0;
}
