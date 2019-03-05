#include<bits/stdc++.h>

const int N = 2010;

std::bitset <N> set[N];
char s[N][N];
int rank[N][N];
int isfirst[N];
bool hassecond[N];

int getrank(int n, int m){
    int rank = 0;
    for (int i = 0; i < m; ++ i){
        for (int j = rank; j < n; ++ j){
            if (set[j][i]){
                std::swap(set[rank], set[j]);
            }
        }
        if (!set[rank][i]) continue;
        for (int j = 0; j < n; ++ j){
            if (j == rank) continue;
            if (set[j][i]){
                set[j] ^= set[rank];
            }
        }
        ++ rank;
    }
    return rank;
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i){
        scanf("%s", s[i]);
    }
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < m; ++ j){
            set[i][j] = s[i][j] - '0';
        }
    }
    int begin = getrank(n, m);
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < m; ++ j){
            set[i][j] = s[i][j] - '0';
        }
    }
    for (int i = 0; i < n; ++ i){
        set[i][i + m] = 1;
    }
    int baserank = getrank(n, m);
    assert(baserank == begin);
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < m; ++ j){
            rank[i][j] = baserank;
        }
    }
    for (int i = 0; i < n; ++ i){
        bool flag = false;
        for (int j = begin; j < n; ++ j){
            if (set[j][i + m]){
                flag = true;
                break;
            }
        }
        if (flag){
            for (int j = 0; j < m; ++ j){
                ++ rank[i][j];
            }
        }
    }
    memset(isfirst, -1, sizeof(isfirst));
    for (int i = 0; i < begin; ++ i){
        int sit = set[i]._Find_first();
        isfirst[sit] = i;
        int beginsit = sit;
        sit = set[i]._Find_next(sit);
        if (sit < m){
            hassecond[beginsit] = true;
        }
    }
    for (int j = 0; j < m; ++ j){
        if (isfirst[j] != -1 && !hassecond[j]){
            for (int i = 0; i < n; ++ i){
                if (set[isfirst[j]][i + m] || rank[i][j] > begin){
                    -- rank[i][j];
                }
            }
        }
    }
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < m; ++ j){
            putchar(rank[i][j] < begin ? '-' : rank[i][j] == begin ? '0' : '+');
        }
        puts("");
    }
    return 0;
}
