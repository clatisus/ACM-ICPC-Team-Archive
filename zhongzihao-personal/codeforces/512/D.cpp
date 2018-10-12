#include<bits/stdc++.h>

const int N = 2000010;
const int moder = 1e9 + 7;

int min[N];
std::vector <int> prime;
bool vis[N];
int max[N], cnt[N];

int powermod(int a, int exp){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * ret * a % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

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

bool flag = false;

void add(int x){
    bool flag1 = false;
    while (x > 1){
        int tmp = min[x], cnt = 0;
        while (x % tmp == 0){
            ++ cnt;
            x /= tmp;
        }
        if (max[tmp] < cnt){
            flag1 = true;
            max[tmp] = cnt;
        }
    }
    if (!flag1){
        flag = true;
    }
}

int main(){
    init();
    int n;
    scanf("%d", &n);
    for (int i = 0, p; i < n; ++ i){
        scanf("%d", &p);
        ++ cnt[p];
    }
    for (int i = 2; i < N; ++ i){
        if (cnt[i] >= 3){
            flag = true;
            add(i);
            add(i - 1);
        }
        else if (cnt[i] >= 2){
            add(i);
            add(i - 1);
        }
        else if (cnt[i] == 1){
            if (max[i]){
                add(i - 1);
            }
            else{
                add(i);
            }
        }
    }
    int ans = 1;
    for (int i = 0; i < N; ++ i){
        if (i == min[i]){
            ans = 1ll * ans * powermod(i, max[i]) % moder;
        }
    }
    ans += flag;
    ans -= ans >= moder ? moder : 0;
    printf("%d\n", ans);
    return 0;
}
