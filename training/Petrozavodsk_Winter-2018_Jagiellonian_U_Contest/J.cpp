#include <bits/stdc++.h>

const int N = 200010;
typedef long double ld;
const ld eps = 1e-9;

inline int sig(ld p){return (p > eps) - (p < -eps);}

int min[N], cnt[N];
std::vector <int> prime;
ld fac[N];

bool check(int m, int a, int b){
    for (auto u : prime){
        if (u > m){
            break;
        }
        int ccnt = 0;
        int aa = a, bb = b, carry = 0;
        while (aa || bb){
            int x = aa % u + bb % u + carry;
            aa /= u, bb /= u;
            carry = x >= u;
            ccnt += carry;
        }
        if (ccnt != cnt[u]){
            return false;
        }
    }
    return true;
}

void solve(){
    int t, m;
    scanf("%d%d", &t, &m);
    ld prod = 0;
    for (int i = 0, x; i < t; ++ i){
        scanf("%d", &x);
        prod += std::log((ld) x);
        ++ cnt[x];
    }
    for (int i = 0; i <= m; ++ i){
        int left = 0, right = i >> 1;
        while (left < right){
            int mid = (left + right) >> 1;
            if (sig(fac[i] - fac[mid] - fac[i - mid] - prod) < 0){
                left = mid + 1;
            }
            else{
                right = mid;
            }
        }
        for ( ; left <= i >> 1; ++ left){
            ld diff = fac[i] - fac[left] - fac[i - left] - prod;
            if (sig(diff) > 0){
                break;
            }
            if (sig(diff) < 0){
                continue;
            }
            if (check(m, left, i - left)){
                puts("YES");
                printf("%d %d\n", i, left);
                memset(cnt, 0, sizeof(int) * (m + 1));
                return;
            }
        }
    }
    memset(cnt, 0, sizeof(int) * (m + 1));
    puts("NO");
}

int main(){
    for (int i = 2; i < N; ++ i){
        if (!min[i]){
            min[i] = i;
            prime.push_back(i);
        }
        for (auto u : prime){
            if (i * u >= N) {
                break;
            }
            min[i * u] = u;
            if (i % u == 0){
                break;
            }
        }
    }
    for (int i = 1; i < N; ++ i){
        fac[i] = fac[i - 1] + std::log((ld) i);
    }
    int test;
    scanf("%d", &test);
    while (test --){
        solve();
    }
    return 0;
}
