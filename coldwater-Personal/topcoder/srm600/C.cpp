#include<bits/stdc++.h>

const int N = 1210;
typedef long long ll;

class LotsOfLines{
public:
    ll countDivisions(int, int);
};

int cnt[N][N];

ll LotsOfLines::countDivisions(int a, int b){
    for (int i = 1; i < N; ++ i){
        for (int j = 1; j < N; ++ j){
            cnt[i][j] = std::__gcd(i, j) == 1;
        }
    }
    for (int i = 1; i < N; ++ i){
        for (int j = 1; j < N; ++ j){
            cnt[i][j] += cnt[i][j - 1];
        }
    }
    for (int i = 1; i < N; ++ i){
        for (int j = 1; j < N; ++ j){
            cnt[i][j] += cnt[i - 1][j];
        }
    }
    ll ans = a * b + 1;
    for (int i = 0; i < a; ++ i){
        for (int j = 0; j < b; ++ j){
            if (i){
                ++ ans;
            }
            ans += cnt[i][j] + cnt[i][b - 1 - j];
        }
    }
    return ans;
}

/*int main(){
    int a, b;
    LotsOfLines l;
    scanf("%d%d", &a, &b);
    printf("%lld\n", l.countDivisions(a, b));
    return 0;
}*/
