#include<bits/stdc++.h>

const int N = 6;
const int M = 100010;
const int MAX = 1 << 17;

int seg[N][N][MAX << 1];

void add(int sit1, int sit2, int sit, int value){
    seg[sit1][sit2][sit += MAX] = value;
    for (sit >>= 1; sit; sit >>= 1){
        seg[sit1][sit2][sit] = std::min(seg[sit1][sit2][sit << 1], seg[sit1][sit2][sit << 1 | 1]);
    }
}

int query(int sit1, int sit2, int l, int r){
    int ret = INT_MAX;
    for (l += MAX, r += MAX + 1; l < r; l >>= 1, r >>= 1){
        if (l & 1) ret = std::min(ret, seg[sit1][sit2][l ++]);
        if (r & 1) ret = std::min(ret, seg[sit1][sit2][-- r]);
    }
    return ret;
}

char s[M], t[M];
bool vis[M][N];

void update(int i){
    for (int j = 0; j < N; ++ j){
        if (vis[i][j]){
            add(s[i] - 'a', j, i, i);
        }
        else{
            add(s[i] - 'a', j, i, INT_MAX);
        }
    }
    for (int j = 0; j < N; ++ j){
        if (j == s[i] - 'a') continue;
        for (int k = 0; k < N; ++ k){
            add(j, k, i, INT_MAX);
        }
    }
}

int main(){
    int n, m;
    scanf("%s%d", s, &m);
    n = strlen(s);
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < N; ++ j){
            vis[i][j] = true;
        }
    }
    for (int i = 0, sit; i < m; ++ i){
        scanf("%d%s", &sit, t);
        -- sit;
        int len = strlen(t);
        for (int j = 0; j < N; ++ j){
            vis[sit][j] = false;
        }
        for (int j = 0; j < len; ++ j){
            vis[sit][t[j] - 'a'] = true;
        }
    }
    for (int i = 0; i < n; ++ i){
        update(i);
    }
    for (int i = 0; i < n; ++ i){
        bool flag = false;
        for (int j = 0; j < N; ++ j){
            if (!vis[i][j]) continue;
            if (j == s[i] - 'a'){
                flag = true;
                break;
            }
            int sit = query(j, s[i] - 'a', i + 1, n - 1);
            if (sit == INT_MAX) continue;
            std::swap(s[i], s[sit]);
            update(i);
            update(sit);
            flag = true;
            break;
        }
        if (!flag){
            puts("Impossible");
            return 0;
        }
    }
    puts(s);
    return 0;
}
