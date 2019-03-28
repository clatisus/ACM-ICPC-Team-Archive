#include<bits/stdc++.h>

const int N = 310;
typedef std::vector <std::bitset <N>> vb;

char s[N][N];

vb calc(vb vec){
    vb tmp = vec, ret(N);
    int invalid = -1;
    for (int i = 1; i < N - 2; ++ i){
        int cnt[3] = {};
        for (int j = 0; j < N; ++ j){
            cnt[j % 3] ^= tmp[i][j];
        }
        if (cnt[0] != cnt[1] || cnt[0] != cnt[2]){
            invalid = i;
            break;
        }
        for (int j = 0; j < N; ++ j){
            if (tmp[i][j]){
                ret[i + 1][j + 1].flip();
                for (int u = 0; u < 3; ++ u){
                    for (int v = 0; v < 3; ++ v){
                        tmp[i + u][j + v].flip();
                    }
                }
            }
        }
    }
    if (invalid == -1){
        if (tmp[N - 1].any()){
            return vec;
        }
        return ret;
    }
    for (int i = N - 1; i > invalid; -- i){
        int cnt[3] = {};
        for (int j = 0; j < N; ++ j){
            cnt[j % 3] ^= tmp[i][j];
        }
        if (cnt[0] != cnt[1] || cnt[0] != cnt[2]){
            return vec;
        }
        for (int j = 0; j < N; ++ j){
            if (tmp[i][j]){
                ret[i - 1][j + 1].flip();
                for (int u = 0; u < 3; ++ u){
                    for (int v = 0; v < 3; ++ v){
                        tmp[i - u][j + v].flip();
                    }
                }
            }
        }
    }
    for (int i = 0; i < N; ++ i){
        if (i == invalid){
            if (tmp[i].count() > 1){
                return vec;
            }
        }
        else {
            if (tmp[i].any()){
                return vec;
            }
        }
    }
    return ret;
}

int get(vb &vec){
    int left = INT_MAX, right = INT_MIN, up = INT_MAX, down = INT_MIN;
    for (int i = 0; i < N; ++ i){
        for (int j = 0; j < N; ++ j){
            if (vec[i][j]){
                left = std::min(left, j);
                right = std::max(right, j);
                up = std::min(up, i);
                down = std::max(down, i);
            }
        }
    }
    if (left == INT_MAX){
        return 0;
    }
    return (right - left + 1) * (down - up + 1);
}

int main(){
    int w, h;
    scanf("%d%d", &h, &w);
    vb vec(N);
    for (int i = 0; i < w; ++ i){
        scanf("%s", s[i]);
        for (int j = 0; j < h; ++ j){
            if (s[i][j] == '#'){
                vec[i + 1].set(j);
            }
        }
    }
    vb ans = vec;
    while (true){
        vb tmp = calc(vec);
        if (tmp == vec){
            break;
        }
        if (get(tmp) < get(ans) && get(tmp) > 0){
            ans = tmp;
        }
        vec = tmp;
    }
    int left = INT_MAX, right = INT_MIN, up = INT_MAX, down = INT_MIN;
    for (int i = 0; i < N; ++ i){
        for (int j = 0; j < N; ++ j){
            if (ans[i][j]){
                left = std::min(left, j);
                right = std::max(right, j);
                up = std::min(up, i);
                down = std::max(down, i);
            }
        }
    }
    for (int i = up; i <= down; ++ i){
        for (int j = left; j <= right; ++ j){
            putchar(ans[i][j] ? '#' : '.');
        }
        puts("");
    }
    return 0;
}
