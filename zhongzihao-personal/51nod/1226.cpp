#include<bits/stdc++.h>

typedef long long ll;
const int N = 3200010;

int min[N];
std::vector <int> prime;

void init(){
    for (int i = 2; i < N; ++ i){
        if (!min[i]){
            min[i] = i;
            prime.push_back(i);
        }
        for (int j = 0, sz = prime.size(); j < sz && i * prime[j] < N; ++ j){
            min[i * prime[j]] = prime[j];
            if (i % prime[j] == 0){
                break;
            }
        }
    }
}

bool flag[N];
ll value[N];

struct field2{
    int x, y, a, p;

    field2():x(0), y(0), a(0), p(0){}
    field2(int x, int y, int a, int p):x(x), y(y), a(a), p(p){}

    field2 operator *(const field2 &f)const{
        int retx = (1ll * x * f.x + 1ll * y * f.y % p * a) % p;
        int rety = (1ll * x * f.y + 1ll * y * f.x) % p;
        return field2(retx, rety, a, p);
    }

    field2 powermod(int exp)const{
        field2 ret(1, 0, a, p), aux = *this;
        for ( ; exp > 0; exp >>= 1){
            if (exp & 1){
                ret = ret * aux;
            }
            aux = aux * aux;
        }
        return ret;
    }
};

int randint(int n){
    return rand() % n;
}

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

std::vector <int> remain2(int a, int p){
    while (true){
        field2 f(randint(p - 1) + 1, randint(p - 1) + 1, a, p);
        f = f.powermod(p - 1 >> 1);
        if (f.x) continue;
        int ret = powermod(f.y, p - 2, p);
        return {ret, p - ret};
    }
}

int main(){
    srand((unsigned) time(NULL));
    init();
    ll a, b;
    scanf("%lld%lld", &a, &b);
    for (int i = 1; i < N; ++ i){
        value[i] = 2ll * i * i + 2ll * i + 1;
        if (a <= value[i] && value[i] <= b){
            flag[i] = true;
        }
    }
    for (auto u : prime){
        if ((u & 3) != 1) continue;
        std::vector <int> vec = remain2(u - 1, u);
        for (auto v : vec){
            for (int i = 1ll * (u + 1 >> 1) * (v - 1) % u; i < N; i += u){
                if (value[i] != u){
                    flag[i] = false;
                }
            }
        }
    }
    int cnt = 0;
    for (int i = 0; i < N; ++ i){
        cnt += flag[i];
    }
    printf("%d\n", cnt);
    return 0;
}
