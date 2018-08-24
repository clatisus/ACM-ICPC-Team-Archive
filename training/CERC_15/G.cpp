#include <bits/stdc++.h>

#define MAXN (600010)

int n, m, tot, rt, ti;
char s[MAXN];
int cnt[MAXN][4];
bool vis[MAXN];

struct node {
    int l, r, h, t, mask, nxt, pre;
}seg[MAXN];
std::vector<std::pair<int, int>> event[MAXN][4];

int gethight(int x) { return seg[x].h + cnt[ti][seg[x].mask] - cnt[seg[x].t][seg[x].mask]; }
int affectbyA(int x) { return seg[x].pre && gethight(seg[x].pre) > gethight(x); }
int affectbyB(int x) { return seg[x].nxt && gethight(x) < gethight(seg[x].nxt); }
void getmask(int x) { seg[x].mask = affectbyB(x) << 1 | affectbyA(x); }

void merge(int, int);

void getevent(int l, int r) {
    int delta = std::abs(gethight(l) - gethight(r));
    int mask = seg[l].mask ^ seg[r].mask;
    if (!delta) {
        merge(l, r);
    } else if (mask && ti + delta <= m) {
        event[cnt[ti][mask] + delta][mask].push_back({l, r});
    }
}

void merge(int l, int r) {
    if (vis[l] || vis[r]) return;
    assert(gethight(l) == gethight(r));

    vis[l] = vis[r] = true;
    ++tot;
    if (l == rt) rt = tot;

    seg[tot].l = seg[l].l;
    seg[tot].r = seg[r].r;
    seg[tot].h = gethight(l);
    seg[tot].t = ti;
    seg[tot].pre = seg[l].pre;
    seg[tot].nxt = seg[r].nxt;
    getmask(tot);

    if (seg[tot].pre) seg[seg[tot].pre].nxt = tot, getevent(seg[tot].pre, tot);
    if (seg[tot].nxt) seg[seg[tot].nxt].pre = tot, getevent(tot, seg[tot].nxt);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        int h;
        scanf("%d", &h);
        if (tot && h == seg[tot].h) {
            seg[tot].r = i;
        } else {
            ++tot;
            seg[tot].h = h;
            seg[tot].l = seg[tot].r = i;
            seg[tot - 1].nxt = tot;
            seg[tot].pre = tot - 1;
        }
    }
    rt = 1;
    for (int i = 1; i <= tot; ++i) getmask(i);
    for (int i = 1; i < tot; ++i) {
        getevent(i, i + 1);
    }

    scanf("%s", s + 1);
    for (ti = 1; ti <= m; ++ti) {
        for (int i = 1; i < 4; ++i) cnt[ti][i] = cnt[ti - 1][i];

        if (s[ti] == 'A') ++ cnt[ti][1];
        else ++ cnt[ti][2];
        ++ cnt[ti][3];

        for (int i = 1; i < 4; ++i) {
            for (auto u : event[cnt[ti][i]][i])
                merge(u.first, u.second);
            std::vector<std::pair<int, int>>().swap(event[cnt[ti][i]][i]);
        }
    }

    ti = m;
    for (; rt; rt = seg[rt].nxt) {
        for (int i = seg[rt].l; i <= seg[rt].r; ++i) {
            printf("%d%c", gethight(rt), " \n"[i == n]);
        }
    }
    return 0;
}
