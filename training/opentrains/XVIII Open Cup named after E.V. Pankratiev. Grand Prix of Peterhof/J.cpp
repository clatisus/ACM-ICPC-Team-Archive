#include<bits/stdc++.h>

int powermod(int a, int exp, int moder){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * ret * a % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

const int N = 1000010;

char s[N];
int min[N];
std::vector <int> prime;

int main(){
    srand((unsigned) time(NULL));
    int begin = clock();
    for (int i = 2; i < N; ++ i){
        if (!min[i]){
            min[i] = i;
            prime.push_back(i);
        }
        for (int j = 0, k, sz = prime.size(); j < sz && i * prime[j] < N; ++ j){
            min[k = i * prime[j]] = prime[j];
            if (i % prime[j] == 0){
                break;
            }
        }
    }
    scanf("%s", s);
    int n = strlen(s);
    while (true){
        if (1.0 * (clock() - begin) / CLOCKS_PER_SEC > 1.7){
            break;
        }
        int remain = 0, prime = ::prime[rand() % ::prime.size()];
        for (int j = 0; j < n; ++ j){
            remain = (remain * 10 + s[j] - '0') % prime;
        }
        if (remain == 0){
            continue;
        }
        if (powermod(remain, prime - 1 >> 1, prime) != 1){
            puts("No");
            return 0;
        }
    }
    puts("Yes");
    return 0;
}
