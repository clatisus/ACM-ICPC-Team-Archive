#include<bits/stdc++.h>

typedef long long ll;

struct BigInteger{ // 仅支持非负整数
    static const int N = 100;
    static const int base = 1000000000; // 修改它时记得修改输入输出格式
    int a[N];
    int length;

    BigInteger():length(0){memset(a, 0, sizeof(a));}

    BigInteger(int p){
        memset(a, 0, sizeof(a));
        length = 0;
        if (!p) return;
        for (int x = std::abs(p); x; x /= base){
            a[length ++] = x % base;
        }
    }

    int &operator [](int sit){return a[sit];}

    BigInteger operator + (const BigInteger &p)const{
        BigInteger ret;
        ret.length = std::max(length, p.length) + 1;
        for (int i = 0; i < ret.length; ++ i){
            ret.a[i] += a[i] + p.a[i];
            if (ret.a[i] >= base) ret.a[i] -= base, ++ ret.a[i + 1];
        }
        for ( ; ret.length && !ret.a[ret.length - 1]; -- ret.length)
            ;
        return ret;
    }

    BigInteger operator / (int p)const{
        if (!p) assert(("Division by zero!", 0));
        ll remain = 0;
        BigInteger ret;
        for (int i = length - 1; ~i; -- i){
            remain = remain * base + a[i];
            ret.a[i] = remain / p;
            remain %= p;
        }
        for (ret.length = length; ret.length && !ret.a[ret.length - 1]; -- ret.length)
            ;
        return ret;
    }

    void write(){
        if (!length) return (void) printf("0");
        printf("%d", a[length - 1]);
        for (int i = length - 2; ~i; -- i){
            printf("%09d", a[i]);
        }
    }
};

const int N = 500;

BigInteger power[N];
std::vector <int> vecs[N << 2];
int n, m;

void init(){
    power[0] = BigInteger(1);
    for (int i = 1; i < N; ++ i){
        power[i] = power[i - 1] + power[i - 1];
    }
}

int &get(std::vector <int> &vec, int x, int y){
    return vec[x * m + y];
}

std::vector <int> rotate(std::vector <int> vec){
    std::vector <int> ret(n * m);
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < m; ++ j){
            get(ret, j, m - 1 - i) = get(vec, i, j);
        }
    }
    return ret;
}

std::vector <int> rotate180(std::vector <int> vec){
    std::vector <int> ret(n * m);
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < m; ++ j){
            get(ret, n - 1 - i, m - 1 - j) = get(vec, i, j);
        }
    }
    return ret;
}

void rotrow(std::vector <int> &vec){
    for (int i = 0; i < n; ++ i){
        int tmp = get(vec, i, 0);
        for (int j = 0; j < m - 1; ++ j){
            get(vec, i, j) = get(vec, i, j + 1);
        }
        get(vec, i, m - 1) = tmp;
    }
}

void rotcol(std::vector <int> &vec){
    for (int i = 0; i < m; ++ i){
        int tmp = get(vec, 0, i);
        for (int j = 0; j < n - 1; ++ j){
            get(vec, j, i) = get(vec, j + 1, i);
        }
        get(vec, n - 1, i) = tmp;
    }
}

void enumerate(int &cnt, std::vector <int> vec){
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < m; ++ j){
            vecs[cnt ++] = vec;
            rotrow(vec);
        }
        rotcol(vec);
    }
}

bool vis[N];

int calc(std::vector <int> vec){
    memset(vis, 0, sizeof(vis));
    int ret = 0;
    for (int i = 0; i < n * m; ++ i){
        if (vis[i]){
            continue;
        }
        int x = i;
        ++ ret;
        while (true){
            vis[x] = true;
            x = vec[x];
            if (x == i){
                break;
            }
        }
    }
    return ret;
}

int main(){
    init();
    scanf("%d%d", &n, &m);
    if (n < m){
        std::swap(n, m);
    }
    int cnt = 0;
    std::vector <int> vec(n * m);
    for (int i = 0; i < n * m; ++ i){
        vec[i] = i;
    }
    enumerate(cnt, vec);
    if (n == m){
        vec = rotate(vec);
        enumerate(cnt, vec);
        vec = rotate(vec);
    }
    else{
        vec = rotate180(vec);
    }
    enumerate(cnt, vec);
    if (n == m){
        vec = rotate(vec);
        enumerate(cnt, vec);
    }
    for (int i = 0; i < cnt; ++ i){
        for (auto u : vecs[i]){
            //printf("%d ", u);
        }
        //putchar('\n');
    }
    std::sort(vecs, vecs + cnt);
    cnt = std::unique(vecs, vecs + cnt) - vecs;
    for (int i = 0; i < cnt; ++ i){
        //printf("%d\n", (int) vec.size());
    }
    BigInteger ans;
    for (int i = 0; i < cnt; ++ i){
        ans = ans + power[calc(vecs[i])];
    }
    ans = ans / cnt;
    ans.write();
    putchar('\n');
    return 0;
}

