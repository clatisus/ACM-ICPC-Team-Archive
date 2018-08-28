#include<bits/stdc++.h>

const int N = 1010;

struct relation{
    int l, r, diff;

    bool operator < (const relation &x)const{
        return r > x.r;
    }
};

int x[N], y[N], h[N];
char s[N];
relation r[N];

int move(int sit, int cnt){
    for (int i = 0; i < cnt; ++ i){
        if (sit > r[i].r) continue;
        int x = (sit - r[i].l) / r[i].diff;
        sit -= std::max(0, x) * r[i].diff;
    }
    return sit;
}

int main(){
    int n, a, b, q;
    scanf("%d%d%d%d", &n, &a, &b, &q);
    for (int i = 0; i < a; ++ i){
        scanf("%d%s", &x[i], s + i);
    }
    for (int i = 0; i < b; ++ i){
        scanf("%d%d", &y[i], &h[i]);
    }
    int cnt = 0;
    for (int i = 0; i < b; ++ i){
        if (h[i]){
            if (i == b - 1){
                r[cnt ++] = {h[i], n, y[i] - h[i]};
            }
            else{
                r[cnt ++] = {h[i], y[i + 1] - 1, y[i] - h[i]};
            }
        }
    }
    std::sort(r, r + cnt);
    std::unordered_map <int, char> Hash;
    for (int i = 0; i < a; ++ i){
        Hash[move(x[i], cnt)] = s[i];
    }
    while (q --){
        int sit;
        scanf("%d", &sit);
        sit = move(sit, cnt);
        if (Hash.count(sit)){
            putchar(Hash[sit]);
        }
        else{
            putchar('?');
        }
    }
    puts("");
    return 0;
}
