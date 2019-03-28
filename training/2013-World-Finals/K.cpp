//
// Created by zzh on 2019/3/7.
//

#include <bits/stdc++.h>

#define In 0
#define Post 1
#define Pre 2

std::vector<std::string> vec = {"In", "Post", "Pre"};

int n, Q[30], cnt[3];

char s[3][30];

struct state {
    int tp, l, r;

    state(int tp = 0, int l = 0, int r = 0) :
        tp(tp), l(l), r(r) {}
};

std::vector<std::string> solve(std::vector<state> sta) {

}

void dfs(int x) {
    if (x == 6) {
        std::vector<state> sta;
        sta.emplace_back(Pre, 0, n - 1);
        sta.emplace_back(In, 0, n - 1);
        sta.emplace_back(Post, 0, n - 1);
        auto ans = solve(sta);
        if (ans.empty()) return;

        return;
    }
}

int main() {
    for (int i = 0; i < 3; ++i) {
        scanf("%s", s[i]);
    }
    n = strlen(s[0]);
    cnt[0] = cnt[1] = cnt[2] = 2;

}