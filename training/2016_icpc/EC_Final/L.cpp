#include<bits/stdc++.h>

int a, b, c, d;
int cnt;

int score[4];

void dfs(int x, int y){
    if (x == 3){
        if (a == score[0] && b == score[1] && c == score[2] && d == score[3]){
            ++ cnt;
        }
        return;
    }
    if (y == 4){
        dfs(x + 1, x + 2);
        return;
    }
    score[x] += 3;
    dfs(x, y + 1);
    score[x] -= 3;
    score[x] += 1, score[y] += 1;
    dfs(x, y + 1);
    score[x] -= 1, score[y] -= 1;
    score[y] += 3;
    dfs(x, y + 1);
    score[y] -= 3;
}

void solve(){
    scanf("%d%d%d%d", &a, &b, &c, &d);
    cnt = 0;
    dfs(0, 1);
    puts(cnt == 1 ? "Yes" : cnt == 0 ? "Wrong Scoreboard" : "No");
}

int main(){
    int test;
    scanf("%d", &test);
    for (int i = 1; i <= test; ++ i){
        printf("Case #%d: ", i);
        solve();
    }
}

