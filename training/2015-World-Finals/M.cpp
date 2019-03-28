//
// Created by zzh on 2019/3/16.
//

#include <bits/stdc++.h>

const int inf = 0x3f3f3f3f;

int xmax, ymax;

struct window {
    int x, y, w, h;

    window(int x = 0, int y = 0, int w = 0, int h = 0) :
        x(x), y(y), w(w), h(h) {}

    inline bool out() const {
        return x < 0 || x >= xmax || y < 0 || y >= ymax;
    }

    inline bool overlap(const window &o) const {
        if (x > o.x + o.w || x + w < o.x) return false;
        if (y > o.y + o.h || y + h < o.y) return false;
        return true;
    }

    inline bool contains(int a, int b) const {
        return x <= a && a <= x + w && y <= b && b <= y + h;
    }

    inline void resize(int &a, int &b) {
        std::swap(a, w);
        std::swap(b, h);
    }

    inline int corner_dis(int dx, int dy) const {
        if (!dx) {
            if (dy > 0) {
                return ymax - y - h - 1;
            } else {
                return y;
            }
        } else {
            if (dx > 0) {
                return xmax - x - w - 1;
            } else {
                return x;
            }
        }
    }

    inline int get_dis(const window &o, int dx, int dy) const {
        if (!dx) {
            if (x + w < o.x || x > o.x + o.w) return inf;
            if (dy > 0) {
                if (y > o.y) return inf;
                return o.y - y - h;
            } else {
                if (y < o.y) return inf;
                return y - o.y - o.h;
            }
        } else {
            if (y + h < o.y || y > o.y + o.h) return inf;
            if (dx > 0) {
                if (x > o.x) return inf;
                return o.x - x - w;
            } else {
                if (x < o.x) return inf;
                return x - o.x - o.w;
            }
        }
    }

    inline void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    inline void display() {
        printf("%d %d %d %d\n", x, y, w, h);
    }
};

std::vector<window> windows;

std::vector<int> dis;

std::vector<int> vec;

char opt[21];

bool fit(const window &w, std::vector<int> &vec) {
    if (w.out()) return false;
    for (auto &i : vec) {
        if (w.overlap(windows[i])) {
            return false;
        }
    }
    return true;
}

int cmd;

inline void fit_err(const std::string &command) {
    printf("Command %d: %s - window does not fit\n", cmd, command.c_str());
}

inline void pos_err(const std::string &command) {
    printf("Command %d: %s - no window at given position\n", cmd, command.c_str());
}

void open(int x, int y, int w, int h) {
    window nw(x, y, w, h);
    if (fit(nw, vec)) {
        vec.push_back(windows.size());
        windows.push_back(nw);
    } else {
        fit_err("OPEN");
    }
}

int find(int x, int y) {
    for (int i = 0; i < vec.size(); ++i) {
        if (windows[vec[i]].contains(x, y)) {
            return i;
        }
    }
    return -1;
}

void close(int x, int y) {
    int id = find(x, y);
    if (id == -1) {
        return pos_err("CLOSE");
    }
    std::swap(vec[id], vec.back());
    vec.pop_back();
}

void resize(int x, int y, int w, int h) {
    int id = find(x, y);
    if (id == -1) {
        return pos_err("RESIZE");
    }
    int u = vec[id];
    windows[u].resize(w, h);
    std::swap(vec[id], vec.back());
    vec.pop_back();
    if (!fit(windows[u], vec)) {
        fit_err("RESIZE");
        windows[u].resize(w, h);
    }
    vec.push_back(u);
}

void move(int x, int y, int dx, int dy) {
    int id = find(x, y);
    if (id == -1) {
        return pos_err("MOVE");
    }

    dis.resize(windows.size());
    for (auto &it : dis) {
        it = inf;
    }

    int d = std::abs(dx + dy), dd = 0;
    std::vector<int> Q[2];
    for (auto &it : vec) {
        if (it != vec[id]) {
            Q[1].push_back(it);
        } else {
            Q[0].push_back(it);
        }
    }

    auto updt = [&] (int i) {
        for (auto &j : Q[1]) {
            dis[j] = std::min(dis[j], windows[i].get_dis(windows[j], dx, dy));
        }
    };

    updt(Q[0][0]);

    while (true) {
        if (!dx && !dy) break;
        int tmp = std::abs(dx + dy);
        for (auto &i : Q[0]) {
            tmp = std::min(tmp, windows[i].corner_dis(dx, dy));
        }
        if (!tmp) break;
        for (auto &j : Q[1]) {
            tmp = std::min(tmp, dis[j]);
        }
        dd += tmp;
        int ddx = 0, ddy = 0;

        if (dx > 0) {
            ddx = tmp;
            dx -= tmp;
        } else if (dx < 0) {
            ddx = -tmp;
            dx += tmp;
        }

        if (dy > 0) {
            ddy = tmp;
            dy -= tmp;
        } else if (dy < 0) {
            ddy = -tmp;
            dy += tmp;
        }
        for (auto &j : Q[0]) {
            windows[j].move(ddx, ddy);
        }
        std::vector<int> nQ[2];
        for (auto &j : Q[1]) {
            if (dis[j] == inf) continue;
            dis[j] -= tmp;
            if (!dis[j]) {
                nQ[0].push_back(j);
            } else {
                nQ[1].push_back(j);
            }
        }
        Q[1] = nQ[1];
        for (auto &j : nQ[0]) {
            updt(j);
            Q[0].push_back(j);
        }
    }

    if (dd < d) {
        printf("Command %d: MOVE - moved %d instead of %d\n", cmd, dd, d);
    }
}

int main() {
    scanf("%d%d", &xmax, &ymax);
    int x, y, w, h, dx, dy;
    while (~scanf("%s%d%d", opt, &x, &y)) {
        ++cmd;
        if (*opt == 'O') {
            scanf("%d%d", &w, &h);
            open(x, y, w, h);
        } else if (*opt == 'C') {
            close(x, y);
        } else if (*opt == 'R') {
            scanf("%d%d", &w, &h);
            resize(x, y, w, h);
        } else {
            scanf("%d%d", &dx, &dy);
            move(x, y, dx, dy);
        }
    }
    printf("%d window(s):\n", int(vec.size()));
    std::sort(vec.begin(), vec.end());
    for (auto &i : vec) {
        windows[i].display();
    }
}

/*
320 200
OPEN 50 50 10 10
OPEN 70 55 10 10
OPEN 90 50 10 10
RESIZE 55 55 40 40
RESIZE 55 55 15 15
MOVE 55 55 40 0
CLOSE 55 55
CLOSE 110 60
MOVE 95 55 0 -100
 */