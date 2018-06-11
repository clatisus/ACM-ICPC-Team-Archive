#include<bits/stdc++.h>

const int N = 200010;
const int moder = 1e9 + 7;
inline int lowbit(int n){return n & -n;}
typedef std::pair <int, int> pii;

int inv[N], a[N], cnt[N];
pii c[N], suf[N];
std::vector <int> vec[N];

void addmod(int &a, int b){
    a += b;
    a -= a >= moder ? moder : 0;
}

void submod(int &a, int b){
    a -= b;
    a += a < 0 ? moder : 0;
}

void multmod(int &a, int b, int c){
    a = (a + 1ll * b * c) % moder;
}

int powermod(int a, int exp){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1) ret = 1ll * ret * a % moder;
        a = 1ll * a * a % moder;
    }
    return ret;
}

void addmod(pii &a, pii b){
    if (a.second > b.second){
        a = b;
    }
    else if (a.second == b.second){
        addmod(a.first, b.first);
    }
}

void add(int sit, pii value){
    for ( ; sit < N; sit += lowbit(sit)){
        addmod(c[sit], value);
    }
}

pii query(int sit){
    pii ret = {0, INT_MAX};
    for ( ; sit; sit -= lowbit(sit)){
        addmod(ret, c[sit]);
    }
    return ret;
}

int c1[N];

void add1(int sit, int value){
    for ( ; sit < N; sit += lowbit(sit)){
        c1[sit] += value;
    }
}

int query1(int sit){
    int ret = 0;
    for ( ; sit; sit -= lowbit(sit)){
        ret += c1[sit];
    }
    return ret;
}

int main(){
    inv[0] = 0, inv[1] = 1;
    for (int i = 2; i < N; ++ i){
        inv[i] = (moder - 1ll * (moder / i) * inv[moder % i] % moder) % moder;
    }
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i){
        scanf("%d", &a[i]);
        ++ cnt[a[i]];
        vec[a[i]].push_back(i);
    }
    for (int i = n - 1; i >= 1; -- i){
        cnt[i] += cnt[i + 1];
    }
    int total = 1;
    for (int i = 1; i <= n; ++ i){
        cnt[i] -= n - i;
        if (cnt[i] <= 0){
            puts("0");
            return 0;
        }
        total = 1ll * total * cnt[i] % moder;
    }
    suf[n + 1] = {1, 0};
    for (int i = n; i >= 1; -- i){
        suf[i] = suf[i + 1];
        if (cnt[i] == 1){
            ++ suf[i].second;
        }
        else{
            suf[i].first = 1ll * suf[i].first * (cnt[i] - 1) % moder * inv[cnt[i]] % moder;
        }
    }
    for (int i = 1; i < N; ++ i){
        c[i] = {0, INT_MAX};
    }
    int ans = 0;
    for (int i = 1; i <= n; ++ i){
        for (auto u : vec[i]){
            int num = query1(n) - query1(u), sum = 0;
            multmod(sum, num, total);
            pii p1 = query(u - 1), p2 = query(n);
            addmod(p1, p1);
            p2.first = p2.first ? moder - p2.first : 0;
            addmod(p1, p2);
            if (p1.second == suf[i + 1].second){
                multmod(sum, 1ll * p1.first * powermod(suf[i + 1].first, moder- 2) % moder * inv[2] % moder, total);
            }
            addmod(ans, sum);
        }
        for (auto u : vec[i]){
            add1(u, 1);
            add(u, suf[i + 1]);
        }
        multmod(ans, 1ll * vec[i].size() * (vec[i].size() - 1) % moder * inv[4] % moder, total);
    }
    printf("%d\n", ans);
    return 0;
}
