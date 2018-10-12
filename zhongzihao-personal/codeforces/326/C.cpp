#include<bits/stdc++.h>

const int N = 100010;
const int MAX = 1 << 17;

std::vector <int> e[N], vec[N];
int dep[N], son[N], top[N], fa[N], sz[N];
int c[N], cnt[N];

std::vector <int> merge(std::vector <int> vec1, std::vector <int> vec2){
    std::vector <int> vec;
    for (auto u : vec1){
        vec.push_back(u);
    }
    for (auto u : vec2){
        vec.push_back(u);
    }
    std::sort(vec.begin(), vec.end());
    if (vec.size() > 10){
        vec.erase(vec.begin() + 10, vec.end());
    }
    return vec;
}

struct Seg{
    std::vector <int> vec;
    int cnt;
    Seg *child[2];
    
    Seg():vec(std::vector <int>()), cnt(0){child[0] = child[1] = NULL;}

    static std::vector <int> getvec(Seg *seg){
        return seg == NULL ? std::vector <int>() : seg -> vec;
    }

    static int getcnt(Seg *seg){
        return seg == NULL ? 0 : seg -> cnt;
    }

    static Seg *getchild(Seg *seg, int i){
        return seg == NULL ? NULL : seg -> child[i];
    }
};

Seg *segpool;
int segcnt = 0;
Seg *seg[N];

Seg *newSeg(){
    if (!segcnt){
        segpool = new Seg [MAX];
        segcnt += MAX;
    }
    return segpool + -- segcnt;
}

void add(Seg *seg, int l, int r, int q, int value, std::vector <int> vec){
    seg -> vec = merge(seg -> vec, vec);
    seg -> cnt += value;
    if (l == r) return;
    int mid = l + r >> 1;
    if (q <= mid){
        if (!seg -> child[0]){
            seg -> child[0] = newSeg();
        }
        add(seg -> child[0], l, mid, q, value, vec);
    }
    else{
        if (!seg -> child[1]){
            seg -> child[1] = newSeg();
        }
        add(seg -> child[1], mid + 1, r, q, value, vec);
    }
}

typedef std::pair <std::vector <int>, int> pvi;
pvi query(Seg *seg, int l, int r, int ql, int qr){
    if (ql <= l && qr >= r){
        return {Seg::getvec(seg), Seg::getcnt(seg)};
    }
    int mid = l + r >> 1;
    std::vector <int> ret;
    int cnt = 0;
    if (ql <= mid){
        pvi p = query(Seg::getchild(seg, 0), l, mid, ql, qr);
        ret = merge(ret, p.first);
        cnt += p.second;
    }
    if (qr > mid){
        pvi p = query(Seg::getchild(seg, 1), mid + 1, r, ql, qr);
        ret = merge(ret, p.first);
        cnt += p.second;
    }
    return {ret, cnt};
}

void dfs(int u, int fa){
    ::fa[u] = fa;
    sz[u] = 1;
    for (auto v : e[u]){
        if (v == fa) continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]){
            son[u] = v;
        }
    }
}

int segid1[N], segcnt2[N], segid2[N], segcnt1 = 0;

void dfs1(int u, int fa){
    if (!fa){
        top[u] = u;
        segid1[u] = segcnt1;
        seg[segcnt1] = newSeg();
        ++ segcnt1;
    }
    segid2[u] = segcnt2[segid1[u]] ++;
    add(seg[segid1[u]], 0, MAX - 1, segid2[u], cnt[u], vec[u]);
    for (auto v : e[u]){
        if (v == fa) continue;
        if (son[u] == v){
            top[v] = top[u];
            segid1[v] = segid1[u];
        }
        else{
            top[v] = v;
            segid1[v] = segcnt1;
            seg[segcnt1] = newSeg();
            ++ segcnt1;
        }
        dfs1(v, u);
    }
}

pvi lca(int u, int v){
    std::vector <int> vec;
    int cnt = 0;
    while (true){
        if (dep[u] > dep[v]){
            std::swap(u, v);
        }
        if (top[u] == top[v]){
            pvi p = query(seg[segid1[u]], 0, MAX - 1, segid2[u], segid2[v]);
            vec = merge(vec, p.first);
            cnt += p.second;
            return {vec, cnt};
        }
        if (dep[top[u]] < dep[top[v]]){
            std::swap(u, v);
        }
        pvi p = query(seg[segid1[u]], 0, MAX - 1, 0, segid2[u]);
        vec = merge(vec, p.first);
        cnt += p.second;
        u = fa[top[u]];
    }
}

int main(){
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0, u, v; i < n - 1; ++ i){
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for (int i = 1; i <= m; ++ i){
        scanf("%d", &c[i]);
        ++ cnt[c[i]];
        vec[c[i]].push_back(i);
    }
    for (int i = 1; i <= n; ++ i){
        std::sort(vec[i].begin(), vec[i].end());
        if (vec[i].size() > 10){
            vec[i].erase(vec[i].begin() + 10, vec[i].end());
        }
    }
    dfs(1, 0);
    dfs1(1, 0);
    while (q --){
        int u, v, a;
        scanf("%d%d%d", &u, &v, &a);
        pvi p = lca(u, v);
        int sz = std::min((int) p.first.size(), a);
        printf("%d ", sz);
        for (int i = 0; i < sz; ++ i){
            printf("%d ", p.first[i]);
        }
        putchar('\n');
    }
    return 0;
}
