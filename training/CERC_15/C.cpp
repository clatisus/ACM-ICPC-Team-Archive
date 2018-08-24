#include<bits/stdc++.h>

void read(int &x){
    x = 0;
    char ch;
    while (!isdigit(ch = getchar()))
        ;
    x = ch - '0';
    while (isdigit(ch = getchar())){
        x = x * 10 + ch - '0';
    }
}

const int N = 1000010;
const int M = 200010;

typedef std::pair <int, int> pii;

struct Fence{
    int l, r, u, d;

    void read(){
        ::read(u);
        ::read(l);
        ::read(d);
        ::read(r);
        u = N - u, d = N - d;
    }
};

struct Flower{
    int x, y;
    int value;

    void read(){
        ::read(y);
        ::read(x);
        y = N - y;
        value = 1;
    }

    bool operator <(const Flower &f)const{
        return y < f.y;
    }
};

struct Cow{
    int x, y;
    int id;

    void read(){
        ::read(y);
        ::read(x);
        y = N - y;
    }

    bool operator <(const Cow &c)const{
        return x < c.x;
    }
};

struct EventF{
    int u, d, id;
    bool in;
};

struct EventFl{
    int x, value;
    bool in;
};

struct Fenwick{
    int c[N + 10];

    void add(int sit, int value){
        for (++ sit; sit < N + 10; sit += sit & -sit){
            c[sit] += value;
        }
    }

    int query(int sit){
        int ret = 0;
        for (++ sit; sit; sit -= sit & -sit){
            ret += c[sit];
        }
        return ret;
    }
    
    int query(int l, int r){
        return query(r) - query(l - 1);
    }
};

std::vector <EventF> vecf[N + 10];
std::vector <Flower> vecfl[N + 10];
std::vector <EventFl> vecefl[N + 10];
std::vector <Cow> vecc[N + 10];
Fence fence[M];
Cow cow[M];
Fenwick fen;
bool isroot[M];
std::vector <int> e[M];
int ans[M];

void dfs(int u){
    for (auto v : e[u]){
        ans[v] += ans[u];
        dfs(v);
    }
}

int main(){
    int f;
    read(f);
    for (int i = 0; i < f; ++ i){
        fence[i].read();
        vecf[fence[i].r].push_back({fence[i].u, fence[i].d, i, true});
        vecf[fence[i].l].push_back({fence[i].u, fence[i].d, i, false});
    }
    int m;
    read(m);
    for (int i = 0; i < m; ++ i){
        Flower f;
        f.read();
        vecfl[f.x].push_back(f);
    }
    std::map <int, int> dfence, ufence;
    for (int i = N - 1; i >= 0; -- i){
        std::vector <Flower> tmp;
        std::sort(vecfl[i].begin(), vecfl[i].end());
        for (auto u : vecfl[i]){
            if (!tmp.empty() && tmp.back().y == u.y){
                tmp.rbegin() -> value += u.value;
            }
            else{
                tmp.push_back(u);
            }
        }
        for (auto u : vecf[i]){
            if (!u.in) continue;
            dfence[u.d] = u.id;
            ufence[u.u] = u.id;
        }
        for (auto u : tmp){
            auto u1 = dfence.lower_bound(u.y + 1);
            auto u2 = ufence.lower_bound(u.y);
            int x1 = u1 == dfence.end() ? INT_MAX : u1 -> first - 1;
            int x2 = u2 == ufence.end() ? INT_MAX : u2 -> first;
            if (x1 < x2){
                int id = u1 -> second;
                vecfl[fence[id].l - 1].push_back({fence[id].l - 1, fence[id].u + 1, u.value});
            }
            int down = u.y, up = std::min(std::min(x1, x2), N - 1);
            vecefl[up].push_back({u.x, u.value, true});
            vecefl[down].push_back({u.x, u.value, false});
        }
        for (auto u : vecf[i]){
            if (u.in) continue;
            dfence.erase(u.d);
            ufence.erase(u.u);
        }
    }
    int n;
    read(n);
    for (int i = 0; i < n; ++ i){
        cow[i].read();
        cow[i].id = i;
        isroot[i] = true;
        vecc[cow[i].y].push_back(cow[i]);
    }
    for (int i = 0; i < N + 10; ++ i){
        vecf[i].clear();
    }
    for (int i = 0; i < f; ++ i){
        vecf[fence[i].u].push_back({fence[i].l, fence[i].r, i, true});
        vecf[fence[i].d].push_back({fence[i].l, fence[i].r, i, false});
    }
    std::map <int, int> lfence, rfence;
    for (int i = N; i >= 0; -- i){
        std::vector <Cow> tmp;
        std::sort(vecc[i].begin(), vecc[i].end());
        for (auto u : vecc[i]){
            if (!tmp.empty() && tmp.back().x == u.x){
                e[tmp.rbegin() -> id].push_back(u.id);
                ans[u.id] -= ans[tmp.rbegin() -> id];
                isroot[u.id] = false;
            }
            else{
                tmp.push_back(u);
            }
        }
        for (auto u : vecf[i]){
            if (!u.in) continue;
            lfence[u.u] = u.id;
            rfence[u.d] = u.id;
        }
        for (auto u : vecefl[i]){
            if (!u.in) continue;
            fen.add(u.x, u.value);
        }
        for (auto u : tmp){
            auto u1 = lfence.lower_bound(u.x + 1);
            auto u2 = rfence.lower_bound(u.x);
            int x1 = u1 == lfence.end() ? INT_MAX : u1 -> first - 1;
            int x2 = u2 == rfence.end() ? INT_MAX : u2 -> first;
            if (x1 < x2){
                int id = u1 -> second;
                vecc[fence[id].d - 1].push_back({fence[id].l, fence[id].d - 1, u.id});
            }
            int left = u.x, right = std::min(std::min(x1, x2), N - 1);
            ans[u.id] += fen.query(left, right);
        }
        for (auto u : vecefl[i]){
            if (u.in) continue;
            fen.add(u.x, -u.value);
        }
        for (auto u : vecf[i]){
            if (u.in) continue;
            lfence.erase(u.u);
            rfence.erase(u.d);
        }
    }
    for (int i = 0; i < n; ++ i){
        if (isroot[i]){
            dfs(i);
        }
    }
    for (int i = 0; i < n; ++ i){
        printf("%d\n", ans[i]);
    }
    return 0;
}
