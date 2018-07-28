#include <bits/stdc++.h>

#define ll long long
#define pii std::pair<int, int>

int h, w;
int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
struct node {
    int u, xj, yj, xb, yb;
    ll step;
    bool operator < (const struct node &rhs) const {
        if (u != rhs.u) return u < rhs.u;
        if (step != rhs.step) return step < rhs.step;
        std::pair<pii, pii> a = {{xj, yj}, {xb, yb}};
        std::pair<pii, pii> b = {{rhs.xj, rhs.yj}, {rhs.xb, rhs.yb}};
        return a < b;
    }
};
std::map<struct node, ll> map;

bool in(int i, int b) {
    return 1 <= i && i <= b;
}

// u == 0 means Brus
// u == 1 means John
void update(int u, ll &ret, ll ans) {
    if (!ans) return;
    if (u) {
        if (ret == 0 || ret > 0 && ans < 0) ret = ans;
        else if ((ret > 0 && ans > 0) || (ret < 0 && ans < 0)) ret = std::max(ret, ans);
    } else {
        if (ret == 0 || ret < 0 && ans > 0) ret = ans;
        else if ((ret > 0 && ans > 0) || (ret < 0 && ans < 0)) ret = std::min(ret, ans);
    }
}

// flag = 1 means Brus has chased John to left/right border
// flag = 2 means Brus has chased John to top/bottom border
ll dfs(int u, int xj, int yj, int xb, int yb, ll step, int flag = 0) {
    if (xj == xb && yj == yb) return u ? step : -step;
    if (u && std::abs(xj - xb) + std::abs(yj - yb) == 1) return -(step + 1);
    if (!u && (std::abs(xj - xb) == 0 || std::abs(yj - yb) == 0)) return step + 1;

    if (step >= 6 && u && !flag) {
        if (xj + 1 == xb && yj + 1 == yb) return step + 2ll * (xj + yj - 1);
        if (xj - 1 == xb && yj + 1 == yb) return step + 2ll * (h - xj + yj);
        if (xj + 1 == xb && yj - 1 == yb) return step + 2ll * (xj + w - yj);
        if (xj - 1 == xb && yj - 1 == yb) return step + 2ll * (h - xj + w - yj + 1);
        if (1 < xj && xj + 1 == xb) {
            return dfs(1, 1, yj, 2, yb, step + 2ll * (xj - 1), 1);
        }
        if (xb + 1 == xj && xj < h) {
            return dfs(1, h, yj, h - 1, yb, step + 2ll * (h - xj), 1);
        }
        if (1 < yj && yj + 1 == yb) {
            return dfs(1, xj, 1, xb, 2, step + 2ll * (yj - 1), 2);
        }
        if (yb + 1 == yj && yj < w) {
            return dfs(1, xj, w, xb, w - 1, step + 2ll * (w - yj), 2);
        }
        return 0;
    }

    struct node p = {u, xj, yj, xb, yb, step};
    if (map.count(p)) return map[p];

    ll &ret = map[p];
    ret = 0;
    if (u) {
        for (int i = 0; i < 4; ++ i) {
            int _xj = xj + dir[i][0];
            int _yj = yj + dir[i][1];
            if (!(in(_xj, h) && in(_yj, w))) continue;
            update(1, ret, dfs(0, _xj, _yj, xb, yb, step + 1, flag));
        }
    } else {
        for (int i = -3; i <= 3; ++ i) {
            if (flag != 1) if (in(xj + i, h) && xj + i != xb)
                update(0, ret, dfs(1, xj, yj, xj + i, yb, step + 1));
            if (flag != 2) if (in(yj + i, w) && yj + i != yb)
                update(0, ret, dfs(1, xj, yj, xb, yj + i, step + 1));
        }
    }
    return ret;
}

void testCase() {
    map.clear();
    int xj, yj, xb, yb;
    scanf("%d%d", &h, &w);
    scanf("%d%d%d%d", &xj, &yj, &xb, &yb);
    char name[10];
    scanf("%s", name);
    ll ans = dfs(name[0] == 'B' ? 0 : 1, xj, yj, xb, yb, 0);
    if (ans < 0) {
        printf("John %lld\n", -ans);
    } else {
        printf("Brus %lld\n", ans);
    }
}

int main() {
    int test;
    scanf("%d", &test);
    while (test --) {
        testCase();
    }
    return 0;
}
