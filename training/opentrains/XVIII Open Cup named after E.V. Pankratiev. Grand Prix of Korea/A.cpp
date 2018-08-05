#include<bits/stdc++.h>

const int N = 2000010;
const int MAX = 1 << 20;

struct Event{
    int x, y1, y2;
    int in, s;
    
    bool operator < (const Event &e)const{
        if (x != e.x){
            return x < e.x;
        }
        return in < e.in;
    }
};

int ecnt = 0;
Event e[N];
int x[N], y[N], s[N];
int cy[N];
int seg[MAX << 1], lazy[MAX << 1];

void push(int sit){
    if (lazy[sit] == 0) return;
    seg[sit << 1] += lazy[sit];
    lazy[sit << 1] += lazy[sit];
    seg[sit << 1 | 1] += lazy[sit];
    lazy[sit << 1 | 1] += lazy[sit];
    lazy[sit] = 0;
}

void pull(int sit){
    seg[sit] = std::max(seg[sit << 1], seg[sit << 1 | 1]);
}

void add(int sit, int l, int r, int ql, int qr, int value){
    if (ql <= l && qr >= r){
        seg[sit] += value;
        lazy[sit] += value;
        return;
    }
    push(sit);
    int mid = l + r >> 1;
    if (ql <= mid){
        add(sit << 1, l, mid, ql, qr, value);
    }
    if (qr > mid){
        add(sit << 1 | 1, mid + 1, r, ql, qr, value);
    }
    pull(sit);
}

void add(int ql, int qr, int value){
    add(1, 0, MAX - 1, ql, qr, value);
}

int query(int sit, int l, int r, int ql, int qr){
    if (ql <= l && qr >= r){
        return seg[sit];
    }
    push(sit);
    int mid = l + r >> 1;
    int max = INT_MIN;
    if (ql <= mid){
        max = std::max(max, query(sit << 1, l, mid, ql, qr));
    }
    if (qr > mid){
        max = std::max(max, query(sit << 1 | 1, mid + 1, r, ql, qr));
    }
    return max;
}

int query(int ql, int qr){
    return query(1, 0, MAX - 1, ql, qr);
}

void build(int x1, int x2, int y1, int y2, int s){
    if (y1 >= y2) return;
    e[ecnt ++] = {x1, y1, y2, 1, s};
    e[ecnt ++] = {x2, y1, y2, 0, s};
}

int main(){
    int n, l, r;
    scanf("%d%d%d", &n, &l, &r);
    for (int i = 0; i < n; ++ i){
        scanf("%d%d%d", &x[i], &y[i], &s[i]);
    }
    int cycnt = 0;
    for (int i = 0; i < n; ++ i){
        cy[cycnt ++] = y[i] - r;
        cy[cycnt ++] = y[i] - l;
        cy[cycnt ++] = y[i] - l + 1;
        cy[cycnt ++] = y[i] + l;
        cy[cycnt ++] = y[i] + l + 1;
        cy[cycnt ++] = y[i] + r;
        cy[cycnt ++] = y[i] + r + 1;
    }
    std::sort(cy, cy + cycnt);
    cycnt = std::unique(cy, cy + cycnt) - cy;
    for (int i = 0; i < n; ++ i){
        int y1 = std::lower_bound(cy, cy + cycnt, y[i] - r) - cy;
        int y2 = std::lower_bound(cy, cy + cycnt, y[i] - l) - cy;
        int y3 = std::lower_bound(cy, cy + cycnt, y[i] - l + 1) - cy;
        int y4 = std::lower_bound(cy, cy + cycnt, y[i] + l) - cy;
        int y5 = std::lower_bound(cy, cy + cycnt, y[i] + l + 1) - cy;
        int y6 = std::lower_bound(cy, cy + cycnt, y[i] + r) - cy;
        int y7 = std::lower_bound(cy, cy + cycnt, y[i] + r + 1) - cy;
        build(x[i] - r, x[i] - l, y1, y4, s[i]);
        build(x[i] - l, x[i] + l, y1, y3, s[i]);
        build(x[i] - l, x[i] - l + 1, y3, y4, s[i]);
        build(x[i] + l, x[i] + r + 1, y1, y4, s[i]);
        build(x[i] - r, x[i] + r + 1, y4, y7, s[i]);
    }
    std::sort(e, e + ecnt);
    int max = 0;
    for (int i = 0, j; i < ecnt; i = j){
        for (j = i; j < ecnt && e[j].x == e[i].x; ++ j){
            add(e[j].y1, e[j].y2 - 1, e[j].in ? e[j].s : -e[j].s);
        }
        max = std::max(max, query(0, MAX - 1));
    }
    printf("%d\n", max);
    return 0;
}
