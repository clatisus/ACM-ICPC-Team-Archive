#include <bits/stdc++.h>

const int MAXN = 100010;

int n;
struct event {
    // type = -1, delete
    // type = 0, query
    // type = 1, add
    int type, x, y1, y2;

    bool operator < (const event &rhs) {
        if (x != rhs.x) return x < rhs.x;
        if (type != rhs.type) return type < rhs.type;
        return y1 == rhs.y1 ? y2 < rhs.y2 : y1 < rhs.y1;
    }
};
std::vector<event> vec;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        vec.push_back({0, x1, y1, y2});
        vec.push_back({0, x2, y1, y2});
        vec.push_back({1, x1, y1, y2});
        vec.push_back({-1, x2, y1, y2});
    }
    std::set<int> set;
    std::sort(vec.begin(), vec.end());
    bool ans = false;
    for (auto p : vec) {
        if (p.type == -1) {
            set.erase(p.y1);
            set.erase(p.y2);
        } else if (p.type == 1) {
            set.insert(p.y1);
            set.insert(p.y2);
        } else {
            auto it = set.upper_bound(p.y1);
            if (it != set.end() && *it <= p.y2) {
                ans = true;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
