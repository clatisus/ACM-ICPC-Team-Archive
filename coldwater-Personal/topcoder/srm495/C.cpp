#include<bits/stdc++.h>

const int N = 40010;
const int M = 100;
typedef long long ll;
const int moder = (int) 1e9 + 7;

int min[N];
std::vector <int> prime;

ll comb[M][M];

void init(){
    for (int i = 2; i < N; ++ i){
        if (!min[i]){
            min[i] = i;
            prime.push_back(i);
        }
        for (int j = 0, sz = prime.size(); j < sz && prime[j] * i < N; ++ j){
            min[i * prime[j]] = prime[j];
            if (i % prime[j] == 0){
                break;
            }
        }
    }
    for (int i = 0; i < M; ++ i){
        comb[i][0] = 1;
        for (int j = 1; j <= i; ++ j){
            comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % moder;
        }
    }
}

std::map <int, int> defact(int n){
    std::map <int, int> ret;
    for (auto u : prime){
        if (n % u == 0){
            while (n % u == 0){
                n /= u;
                ++ ret[u];
            }
        }
    }
    if (n > 1){
        ++ ret[n];
    }
    return ret;
}

std::vector <int> getc(std::map <int, int> Hash){
    int sum = 0;
    for (auto u : Hash){
        sum += u.second;
    }
    std::vector <int> c(sum + 1), d(sum + 1);
    for (int i = 1; i <= sum; ++ i){
        d[i] = 1;
        for (auto u : Hash){
            d[i] = 1ll * d[i] * comb[u.second + i - 1][i - 1] % moder;
        }
    }
    for (int i = 1; i <= sum; ++ i){
        for (int j = 0; j <= i; ++ j){
            c[i] = (c[i] + (i - j & 1 ? -1 : 1) * d[j] * comb[i][j]) % moder;
        }
        c[i] += c[i] < 0 ? moder : 0;
    }
    return c;
}

class StrangeElevator{
public:
    int theCount(int h, int n){
        if (h % n) return 0;
        if (n == 1 || h == n){
            return 1;
        }
        std::vector <int> c1 = getc(defact(n));
        std::vector <int> c2 = getc(defact(h / n));
        c1.resize(101), c2.resize(101);
        int ans = 0;
        for (int i = 1; i < 100; ++ i){
            ans = (ans + 1ll * c1[i] * (c2[i] + c2[i + 1])) % moder;
            ans = (ans + 1ll * c2[i] * (c1[i] + c1[i + 1])) % moder;
        }
        return ans;
    }
};

int main(){
    init();
    int h, n;
    scanf("%d%d", &h, &n);
    StrangeElevator se;
    printf("%d\n", se.theCount(h, n));
    return 0;
}
