#include<bits/stdc++.h>

const int N = 510;

bool vis[N][N << 1];
std::queue <int> queue1[N], queue2[N];

int main(){
    int r, s, p;
    scanf("%d%d%d", &r, &s, &p);
    //r = 500, s = 500, p = 500000;
    for (int i = 0; i < p; ++ i){
        int x, y;
        scanf("%d%d", &x, &y);
        //x = i / 1000 + 1, y = i % 1000 + 1;
        vis[x][y] = true;
    }
    int ans = 0;
    for (int i = 1; i <= r; ++ i) {
        for (int j = s; j >= 1; --j) {
            if (!vis[i][j]) continue;
            queue1[i].push(s - j);
        }
        for (int j = s + 1; j <= 2 * s; ++j) {
            if (!vis[i][j]) continue;
            queue2[i].push(j - s - 1);
        }
    }
    int offset = 0;
    std::bitset <N> set, notempty;
    int cnt = p;
    for (int i = 1; i <= r; ++ i){
        notempty[i] = !queue1[i].empty() || !queue2[i].empty();
    }
    bool begin = true;
    while (cnt){
        if (!begin){
            set = set << 1;
            if (set[r + 1] == 1) {
                --cnt;
                set[r + 1] = 0;
            }
            ++ offset;
        }
        begin = false;
        ++ ans;
        std::vector <int> todel;
        std::bitset <N> tmp = ~set & notempty;
        int sit = tmp._Find_first();
        while (sit < N){
            if (!queue1[sit].empty() && queue1[sit].front() - offset <= 0){
                queue1[sit].pop();
                if (queue1[sit].empty() && queue2[sit].empty()){
                    notempty[sit] = 0;
                }
                set[sit] = 1;
            }
            else if (!queue2[sit].empty() && queue2[sit].front() - offset <= 0){
                queue2[sit].pop();
                if (queue1[sit].empty() && queue2[sit].empty()){
                    notempty[sit] = 0;
                }
                set[sit] = 1;
            }
            sit = tmp._Find_next(sit);
        }
    }
    printf("%d\n", ans);
    return 0;
}
