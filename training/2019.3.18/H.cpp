#include<bits/stdc++.h>

struct event{
    int y1, y2;
};

const int N = 100010;
const int MAX = 1 << 17;
typedef long long ll;

int seg1[MAX << 1], lazy1[MAX << 1];
int x1[N], Y1[N], x2[N], y2[N];

void push1(int sit, int l, int r){
    if (!lazy1[sit]){
        return;
    }
    int len = (r - l + 1) >> 1;
    seg1[sit << 1] = len - seg1[sit << 1];
    seg1[sit << 1 | 1] = len - seg1[sit << 1 | 1];
    lazy1[sit << 1] ^= 1;
    lazy1[sit << 1 | 1] ^= 1;
    lazy1[sit] = 0;
}

void pull1(int sit){
    seg1[sit] = seg1[sit << 1] + seg1[sit << 1 | 1];
}

void add1(int sit, int l, int r, int ql, int qr){
    if (ql <= l && qr >= r){
        seg1[sit] = (r - l + 1) - seg1[sit];
        lazy1[sit] ^= 1;
        return;
    }
    if (l > qr || r < ql){
        return;
    }
    push1(sit, l, r);
    int mid = (l + r) >> 1;
    add1(sit << 1, l, mid, ql, qr);
    add1(sit << 1 | 1, mid + 1, r, ql, qr);
    pull1(sit);
}

int query1(int sit, int l, int r, int ql, int qr){
    if (ql <= l && qr >= r){
        return seg1[sit];
    }
    if (l > qr || r < ql){
        return 0;
    }
    push1(sit, l, r);
    int mid = (l + r) >> 1;
    return query1(sit << 1, l, mid, ql, qr) + query1(sit << 1 | 1, mid + 1, r, ql, qr);
}

void add1(int ql, int qr){
    add1(1, 0, MAX - 1, ql, qr);
}

int query1(int ql, int qr){
    return query1(1, 0, MAX - 1, ql, qr);
}

ll ans = 0;
int countx[N], county[N];
std::vector <event> vec[N];

void process(int n, int *count){
    for (int i = 1; i <= n + 1; ++ i){
        for (auto u : vec[i]){
            add1(u.y1, u.y2);
        }
        count[i] = query1(0, MAX - 1) & 1;
        ans += query1(0, MAX - 1);
    }
}

int main(){
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i < q; ++ i){
        scanf("%d%d%d%d", &x1[i], &Y1[i], &x2[i], &y2[i]);
    }
    for (int i = 0; i < q; ++ i){
        vec[x1[i]].push_back({Y1[i], y2[i]});
        vec[x2[i] + 1].push_back({Y1[i], y2[i]});
    }
    process(n, countx);
    for (int i = 0; i < N; ++ i){
        vec[i].clear();
    }
    memset(seg1, 0, sizeof(seg1));
    memset(lazy1, 0, sizeof(lazy1));
    for (int i = 0; i < q; ++ i){
        vec[Y1[i]].push_back({x1[i], x2[i]});
        vec[y2[i] + 1].push_back({x1[i], x2[i]});
    }
    ans = 0;
    process(m, county);
    typedef std::pair <int, int> pii;
    std::set <pii> set;
    int oddx = 0, oddy = 0;
    for (int i = 1; i <= n; ++ i){
        oddx += countx[i];
    }
    for (int i = 1; i <= m; ++ i){
        oddy += county[i];
    }
    while (oddx || oddy){
        if (set.count({oddx, oddy})){
            puts("-1");
            return 0;
        }
        set.insert({oddx, oddy});
        int noddx = 0, noddy = 0;
        if ((m - oddy) % 2 == 1){
            noddx += oddx;
        }
        if (oddy % 2 == 1){
            noddx += n - oddx;
        }
        if ((n - oddx) % 2 == 1){
            noddy += oddy;
        }
        if (oddx % 2 == 1){
            noddy += m - oddy;
        }
        ans += 1ll * oddx * (m - oddy);
        ans += 1ll * (n - oddx) * oddy;
        oddx = noddx, oddy = noddy;
    }
    printf("%lld\n", ans);
    return 0;
}
