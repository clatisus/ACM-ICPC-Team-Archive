#include<bits/stdc++.h>

typedef long long ll;

struct matrix{
    ll a[2][2];

    matrix(){memset(a, 0, sizeof(a));}

    ll *operator [](int n){
        return a[n];
    }

    matrix operator *(const matrix &m)const{
        matrix ret;
        for (int i = 0; i < 2; ++ i){
            for (int j = 0; j < 2; ++ j){
                ret.a[i][j] = LLONG_MIN;
                for (int k = 0; k < 2; ++ k){
                    ret.a[i][j] = std::max(ret.a[i][j], a[i][k] + m.a[k][j]);
                }
            }
        }
        return ret;
    }
};

const int MAX = 1 << 17;

matrix seg[MAX << 1];
int seg2[MAX << 1];

void add(int sit, int value){
    seg[sit += MAX][1][0] = value;
    seg2[sit] = value;
    for (sit >>= 1; sit; sit >>= 1){
        seg[sit] = seg[sit << 1 | 1] * seg[sit << 1];
        seg2[sit] = std::max(seg2[sit << 1], seg2[sit << 1 | 1]);
    }
}

matrix query(int l, int r){
    matrix lret, rret;
    for (l += MAX, r += MAX + 1; l < r; l >>= 1, r >>= 1){
        if (l & 1) lret = seg[l ++] * lret;
        if (r & 1) rret = rret * seg[-- r];
    }
    return rret * lret;
}

int query2(int l, int r){
    int ret = INT_MIN;
    for (l += MAX, r += MAX + 1; l < r; l >>= 1, r >>= 1){
        if (l & 1) ret = std::max(ret, seg2[l ++]);
        if (r & 1) ret = std::max(ret, seg2[-- r]);
    }
    return ret;
}

int main(){
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 0, x; i < n; ++ i){
        scanf("%d", &x);
        add(i, x);
    }
    while (q --){
        int type;
        scanf("%d", &type);
        if (type == 1){
            int sit, value;
            scanf("%d%d", &sit, &value);
            add(sit, value);
        }
        else{
            int l, r;
            scanf("%d%d", &l, &r);
            int max = query2(l, r);
            if (max <= 0){
                printf("%d\n", max);
                continue;
            }
            matrix mat = query(l, r);
            printf("%lld\n", std::max(std::max(mat[0][0], mat[1][0]), std::max(mat[0][1], mat[1][1])));
        }
    }
    return 0;
}
