#include<bits/stdc++.h>

struct Query{
    int l, r, id;
    int value;

    bool operator < (const Query &q)const{
        return l < q.l;
    }
};

struct Seg{
    int value;
    Seg *child[2];
};

const int N = 100010;
const int BIT = 30;
const int MAX = 1 << BIT;

int segcnt = 0;
Seg *segpool, *seg;

Seg *newseg(){
    if (!segcnt){
        segpool = new Seg [segcnt += N];
    }
    return segpool + (-- segcnt);
}

int getvalue(Seg *seg){
    return seg == nullptr ? INT_MAX : seg -> value;
}

Seg *getchild(Seg *seg, int i){
    return seg == nullptr ? nullptr : seg -> child[i];
}

void add(Seg *seg, int l, int r, int q, int value){
    if (l == r){
        seg -> value = value;
        return;
    }
    int mid = l + r >> 1;
    if (q <= mid){
        if (seg -> child[0] == nullptr){
            seg -> child[0] = newseg();
        }
        add(seg -> child[0], l, mid, q, value);
    }
    else{
        if (seg -> child[1] == nullptr){
            seg -> child[1] = newseg();
        }
        add(seg -> child[1], mid + 1, r, q, value);
    }
    seg -> value = std::min(getvalue(seg -> child[0]), getvalue(seg -> child[1]));
}

void add(int q, int value){
    add(seg, 0, MAX - 1, q, value);
}

int query(int sit, int value){
    Seg *now = seg;
    int ret = 0;
    for (int i = BIT - 1; i >= 0; -- i){
        int x = value >> i & 1;
        if (getvalue(getchild(now, 1 ^ x)) <= sit){
            now = getchild(now, 1 ^ x);
            ret |= 1 << i;
        }
        else{
            now = getchild(now, x);
        }
    }
    return ret;
}

Query q[N];
int ans[N];
int a[N];

int main(){
    seg = newseg();
    int n, q;
    scanf("%d%d", &n, &q);
    std::map <int, std::queue <int>> Hash;
    for (int i = 0; i < n; ++ i){
        scanf("%d", &a[i]);
        if (!Hash.count(a[i])){
            Hash[a[i]] = std::queue <int>();
        }
        Hash[a[i]].push(i);
    }
    for (auto &u : Hash){
        add(u.first, u.second.front());
    }
    for (int i = 0, l, r, value; i < q; ++ i){
        scanf("%d%d%d", &value, &l, &r);
        ::q[i] = {l, r, i, value};
    }
    std::sort(::q, ::q + q);
    for (int i = 0, j = 0; i < q; ++ i){
        while (j < n && j < ::q[i].l){
            auto &u = Hash[a[j]];
            u.pop();
            int x = u.empty() ? INT_MAX : u.front();
            add(a[j], x);
            ++ j;
        }
        ans[::q[i].id] = query(::q[i].r, ::q[i].value);
    }
    for (int i = 0; i < q; ++ i){
        printf("%d\n", ans[i]);
    }
    return 0;
}
