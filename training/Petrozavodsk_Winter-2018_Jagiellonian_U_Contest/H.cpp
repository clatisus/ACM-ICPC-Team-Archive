#include<bits/stdc++.h>

const int N = 100010;
const int moder = (int) 1e9 + 7;

int row[N], column[N];

int solve(){
    int n;
    scanf("%d", &n);
    int sum = 0;
    for (int i = 0; i < n; ++ i){
        scanf("%d", &row[i]);
        sum += row[i];
    }
    for (int i = 0; i < n; ++ i){
        scanf("%d", &column[i]);
        sum -= column[i];
    }
    if (sum){
        return 0;
    }
    int ans = 1;
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    while (x1 != n - 1 || y1 != n - 1 || x2 != n - 1 || y2 != n - 1){
        if (x1 >= n || y1 >= n || x2 >= n || y2 >= n){
            return 0;
        }
        if (!row[x1] || !column[y1]){
            return 0;
        }
        -- row[x1], -- column[y1];
        if (row[x1] == 0){
            ++ x1, ++ x2;
            continue;
        }
        if (column[y1] == 0){
            ++ y1, ++ y2;
            continue;
        }
        int cnt = column[y1];
        for (int i = 0; i < cnt; ++ i){
            ++ x1;
            if (x1 >= n){
                return 0;
            }
            if (row[x1] == 0 || column[y1] == 0){
                return 0;
            }
            -- row[x1], -- column[y1];
        }
        cnt = row[x2];
        for (int i = 0; i < cnt; ++ i){
            ++ y2;
            if (y2 >= n){
                return 0;
            }
            if (row[x2] == 0 || column[y2] == 0){
                return 0;
            }
            -- row[x2], -- column[y2];
        }
        while (x2 < x1 - 1 || y1 < y2 - 1){
            while (x2 < x1 - 1){
                ++ x2;
                -- y2;
                if (x2 >= n){
                    return 0;
                }
                int cnt = row[x2];
                for (int i = 0; i < cnt; ++ i) {
                    ++ y2;
                    if (y2 >= n){
                        return 0;
                    }
                    if (row[x2] == 0 || column[y2] == 0){
                        return 0;
                    }
                    -- row[x2], -- column[y2];
                }
            }
            while (y1 < y2 - 1){
                ++ y1;
                -- x1;
                if (y1 >= n){
                    return 0;
                }
                int cnt = column[y1];
                for (int i = 0; i < cnt; ++ i) {
                    ++ x1;
                    if (x1 >= n){
                        return 0;
                    }
                    if (row[x1] == 0 || column[y1] == 0){
                        return 0;
                    }
                    -- row[x1], -- column[y1];
                }
            }
        }
        ++ x2, ++ y1;
        ans = (ans << 1) % moder;
    }
    if (row[n - 1] != 1 || column[n - 1] != 1){
        return 0;
    }
    return ans;
}

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        printf("%d\n", solve());
    }
    return 0;
}
