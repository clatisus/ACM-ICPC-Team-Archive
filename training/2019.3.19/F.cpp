#include <bits/stdc++.h>

const int N = 310;
const int moder = (int) 1e9 + 7;

int inv[N];

struct poly{
    int a[N];
    int len;

    poly():len(-1){memset(a, 0, sizeof(a));}
    explicit poly(int len):len(len){memset(a, 0, sizeof(a));}

    int &operator[](const int &n){return a[n];}

    poly operator *(const poly &p)const{
        if (len == -1 || p.len == -1){
            return poly();
        }
        poly ret(len + p.len);
        for (int i = 0; i <= len; ++ i){
            for (int j = 0; j <= p.len; ++ j){
                ret[i + j] = (ret[i + j] + 1ll * a[i] * p.a[j]) % moder;
            }
        }
        return ret;
    }

    poly operator *(const int &p)const{
        poly ret(len);
        for (int i = 0; i <= len; ++ i){
            ret[i] = 1ll * a[i] * p % moder;
        }
        return ret;
    }

    poly operator -()const{
        poly ret(len);
        for (int i = 0; i <= len; ++ i){
            ret[i] = -a[i];
            ret[i] += ret[i] < 0 ? moder : 0;
        }
        return ret;
    }

    poly inte()const{
        poly ret(len + 1);
        for (int i = 0; i <= len; ++ i){
            ret[i + 1] = 1ll * a[i] * inv[i + 1] % moder;
        }
        return ret;
    }

    int value(int x)const{
        int ret = 0;
        for (int i = len; i >= 0; -- i){
            ret = (1ll * ret * x + a[i]) % moder;
        }
        return ret;
    }

    int inte(int l, int r)const{
        poly p = inte();
        int ret = p.value(r) - p.value(l);
        ret += ret < 0 ? moder : 0;
        return ret;
    }
};

struct polyr{
    poly p;
    int l, r;
};

std::vector <int> e[N];
int b[N];
int ans = 1;
std::vector <polyr> polys[N];

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

void dfs(int u){
    int min = INT_MAX;
    for (auto v : e[u]){
        dfs(v);
        min = std::min(min, b[v]);
    }
    if (min < b[u]){
        ans = 1ll * ans * min % moder * powermod(b[u], moder - 2) % moder;
        b[u] = min;
    }
}

void solve(int u){
    int max = 0;
    for (auto v : e[u]) {
        solve(v);
        max = std::max(max, b[u]);
    }
    for (auto v : e[u]){
        if (polys[v].back().r < max){
            polys[v].push_back({poly(), polys[v].back().r, max});
        }
        if (polys[u].empty()){
            polys[u] = polys[v];
            continue;
        }
        std::vector <polyr> vec;
        int sz1 = polys[u].size(), sz2 = polys[v].size();
        for (int i = 0, j = 0; i < sz1 && j < sz2; ){
            int l = std::max(polys[u][i].l, polys[v][j].l);
            int r = std::min(polys[u][i].r, polys[v][j].r);
            vec.push_back({polys[u][i].p * polys[v][j].p, l, r});
            if (polys[u][i].r < polys[v][j].r){
                ++ i;
            }
            else if (polys[u][i].r > polys[v][j].r){
                ++ j;
            }
            else{
                ++ i, ++ j;
            }
        }
        polys[u] = vec;
    }
    if (e[u].empty()){
        poly p(1);
        p[0] = 1;
        p[1] = -powermod(b[u], moder - 2);
        p[1] += p[1] < 0 ? moder : 0;
        polys[u].push_back({p, 0, b[u]});
        return;
    }
    std::vector <polyr> vec;
    int nowinte = 0;
    int inv = powermod(b[u], moder - 2);
    for (int i = polys[u].size() - 1; i >= 0; -- i){
        if (polys[u][i].l >= b[u]){
            continue;
        }
        poly tmp = polys[u][i].p.inte();
        if (polys[u][i].r > b[u]){
            int x = tmp.value(b[u]);
            poly topush = -tmp;
            topush[0] += x;
            topush[0] -= topush[0] >= moder ? moder : 0;
            topush[0] += nowinte;
            topush[0] -= topush[0] >= moder ? moder : 0;
            vec.push_back({topush * inv, polys[u][i].l, b[u]});
            nowinte += polys[u][i].p.inte(polys[u][i].l, b[u]);
            nowinte -= nowinte >= moder ? moder : 0;
            continue;
        }
        int x = tmp.value(polys[u][i].r);
        tmp = -tmp;
        tmp[0] += x;
        tmp[0] -= tmp[0] >= moder ? moder : 0;
        tmp[0] += nowinte;
        tmp[0] -= tmp[0] >= moder ? moder : 0;
        vec.push_back({tmp * inv, polys[u][i].l, std::min(polys[u][i].r, b[u])});
        nowinte += polys[u][i].p.inte(polys[u][i].l, polys[u][i].r);
        nowinte -= nowinte >= moder ? moder : 0;
    }
    polys[u] = vec;
}

int main(){
    inv[1] = 1;
    for (int i = 2; i < N; ++ i){
        inv[i] = moder - 1ll * (moder / i) * inv[moder % i] % moder;
    }
    int n;
    scanf("%d", &n);
    int root = 0;
    for (int i = 1; i <= n; ++ i){
        int p;
        scanf("%d%d", &b[i], &p);
        if (p){
            e[p].push_back(i);
        }
        else{
            root = i;
        }
    }
    dfs(root);
    solve(root);
    ans = 1ll * ans * polys[root][0].p[0] % moder;
    printf("%d\n", ans);
    return 0;
}
