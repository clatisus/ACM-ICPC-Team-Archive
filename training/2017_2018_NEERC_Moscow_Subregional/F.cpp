#include <bits/stdc++.h>

const int max_N = 1000 + 21;

struct tri {
    int tp, a, t;
};

int n, m, k, ord[max_N], Q[max_N], rk[max_N];

bool vis[max_N];

struct team {
    std::string name;
    int sol, time, last;
    tri sta[31];
    void Max() {
        for (int i = 0; i < n; ++i) {
            if (sta[i].tp != 1) {
                sta[i].tp = 1;
                sta[i].a++;
                sta[i].t = 240;
            }
        }
    }
    void Calc() {
        sol = time = last = 0;
        for (int i = 0; i < n; ++i) {
            if (sta[i].tp != 1) continue;
            ++sol;
            time += sta[i].t;
            time += 20 * (sta[i].a - 1);
            last = std::max(last, sta[i].t);
        }
    }
} p[max_N];

std::map<std::string, int> map;

char s[233];

team inputT() {
    team p;
    scanf("%s", s);
    p.name = s;
    for (int j = 0, a, t; j < n; ++j) {
        scanf("%s%d%d", s, &a, &t);
        p.sta[j] = (tri) {((*s == '.') ? 0 : ((*s == '+') ? 1 : -1)), a, t};
    }
    return p;
}

bool check() {
    for (int i = 1; i <= m; ++i) {
        p[i].Calc();
        Q[i] = i;
    }
    std::sort(Q + 1, Q + 1 + m, [&](int x, int y) {
        if (p[x].sol != p[y].sol) return p[x].sol > p[y].sol;
        if (p[x].time != p[y].time) return p[x].time < p[y].time;
        if (p[x].last != p[y].last) return p[x].last < p[y].last;
        return p[x].name < p[y].name;
    });
    for (int i = 1; i <= m; ++i) rk[Q[i]] = i;
    for (int i = 1; i < k; ++i)
        for (int j = i + 1; j <= k; ++j) {
            if (rk[ord[i]] > rk[ord[j]]) return false;
        }
    for (int i = 1; i <= m; ++i) {
        if (vis[i]) continue;
        if (rk[i] < rk[ord[1]]) vis[i] = true;
        if (rk[i] > rk[ord[k]]) vis[i] = true;
    }
    return true;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; ++i) {
        p[i] = inputT();
        map[p[i].name] = i;
    }
    for (int i = 1; i <= k; ++i) {
        auto tmp = inputT();
        ord[i] = map[tmp.name];
        p[ord[i]] = tmp;
        vis[ord[i]] = true;
    }
    if (!check()) return puts("Fake"), 0;
    for (int i = 1; i <= m; ++i) {
        if (vis[i]) continue;
        p[i].Max();
    }
    if (!check()) return puts("Fake"), 0;
    for (int i = 1; i <= m; ++i) {
        if (!vis[i]) return puts("Fake"), 0;
    }
    return puts("Leaked"), 0;
}
