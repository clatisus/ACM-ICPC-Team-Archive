#include <bits/stdc++.h>

const int max_N = 700 + 21;
const int max_M = 2000 + 21;

const double eps = 1e-9;
const double PI = acos(-1.0);
const double INF = 1e100;

inline int dcmp(double p) { return (p > eps) - (p < -eps); }

inline double sqr(double p) { return p * p; }

struct P {
    double x, y;

    explicit P(double x = 0, double y = 0) : x(x), y(y) {}

    P add(const P &p) const { return P(x + p.x, y + p.y); }

    P sub(const P &p) const { return P(x - p.x, y - p.y); }

    P mul(const double &t) const { return P(x * t, y * t); }

    double dot(const P &p) const { return x * p.x + y * p.y; }

    double det(const P &p) const { return x * p.y - y * p.x; }

    double abs2() const { return dot(*this); }

    double abs() const { return std::sqrt(abs2()); }

    double angle() const { return std::atan2(y, x); }

    // 逆时针旋转 rad 弧度
    P rot(const double &rad) const {
        double sin = std::sin(rad), cos = std::cos(rad);
        return P(x * cos - y * sin, x * sin + y * cos);
    }

    bool operator<(const P &p) const { return dcmp(x - p.x) ? x < p.x : dcmp(y - p.y) < 0; }

    bool operator==(const P &p) const { return !dcmp(x - p.x) && !dcmp(y - p.y); }
};

int n, m, rt;

std::vector<P> polygon, ans;

P centriod;

struct C {
    P o;
    double r;

    C() {}

    C(P o, double r) : o(o), r(r) {}

    // 圆上一点，满足x轴正方向到该点圆心连线逆时针角度为angle
    P point(double angle) { return o.add(P(r, 0).rot(angle)); }
};

std::vector<C> circleS;

// O(n^2logn) 求圆集合 cs 的并集面积与中心，被卡时间时可预先去掉被其它圆包含的圆
std::pair<double, P> areaCs(std::vector<C> &cs) {
    double ret = 0;
    P pret;
    int n = cs.size();
    for (int i = 0; i < n; ++i) {
        std::vector<std::pair<double, int>> vec = {{0,      0},
                                                   {PI * 2, 0}};
        int cnt = 1;
        for (int j = 0; j < n; ++j) {
            double dis = cs[i].o.sub(cs[j].o).abs();
            if (!dcmp(dis) && !dcmp(cs[i].r - cs[j].r)) {
                if (i < j) ++cnt;
                continue;
            }
            if (dcmp(dis - cs[j].r - cs[i].r) >= 0 || dcmp(dis + cs[j].r - cs[i].r) <= 0) continue;
            if (dcmp(dis + cs[i].r - cs[j].r) <= 0) {
                ++cnt;
                continue;
            }
            double angle = cs[j].o.sub(cs[i].o).angle();
            double p = (sqr(cs[i].r) + sqr(dis) - sqr(cs[j].r)) / (2 * cs[i].r * dis);
            p = std::acos(std::max(-1.0, std::min(1.0, p)));
            double left = angle - p, right = angle + p;
            if (left < 0) left += PI * 2;
            if (right < 0) right += PI * 2;
            if (left >= 2 * PI) left -= PI * 2;
            if (right >= 2 * PI) right -= PI * 2;
            vec.push_back({left, 1}), vec.push_back({right, -1});
            if (left >= right) ++cnt;
        }
        std::sort(vec.begin(), vec.end());
        for (int j = 0, sz = vec.size(); j + 1 < sz; ++j) {
            cnt += vec[j].second;
            if (cnt == 1) {
                double delta = vec[j + 1].first - vec[j].first;
                if (dcmp(delta) <= 0) continue;
                double sin = std::sin(delta / 2);
                P cen(4 * cs[i].r * sin * sin * sin / (3 * (delta - std::sin(delta))), 0);
                cen = cen.rot((vec[j].first + vec[j + 1].first) / 2).add(cs[i].o);
                double area = sqr(cs[i].r) * (delta - std::sin(delta));
                pret = pret.add(cen.mul(area));
                ret += area;
                P p1 = cs[i].point(vec[j].first), p2 = cs[i].point(vec[j + 1].first);
                area = p1.det(p2);
                pret = pret.add(p1.add(p2).mul(area / 3));
                ret += area;
            }
        }
    }
    return {ret, pret};
}

int main() {
    scanf("%d%d%d", &n, &m, &rt);
    --rt;
    polygon.resize(n);
    for (int i = 0, x, y; i < n; ++i) {
        scanf("%d%d", &x, &y);
        polygon[i] = P(x, y);
    }
    double sum = 0;
    for (int i = 1; i + 1 < n; ++i) {
        P tmp = polygon[0].add(polygon[i].add(polygon[i + 1]));
        P v1 = polygon[i].sub(polygon[0]);
        P v2 = polygon[i + 1].sub(polygon[0]);
        double area = v1.det(v2);
        centriod = centriod.add(tmp.mul(area / 3));
        sum += area;
    }
    circleS.resize(m);
    for (int i = 0, x, y, r; i < m; ++i) {
        scanf("%d%d%d", &x, &y, &r);
        circleS[i] = C(P(x, y), r);
    }
    auto pair = areaCs(circleS);
    centriod = centriod.sub(pair.second);
    sum -= pair.first;
    centriod = centriod.mul(1. / sum);
    ans = polygon;
    double angle = -PI / 2 - centriod.sub(polygon[rt]).angle();
    P v1 = centriod.sub(polygon[rt]), v2 = P(0, -1);
    double tmp = 1. / (v1.abs() * v2.abs());
    double cosA = v1.dot(v2) * tmp, sinA = v1.det(v2) * tmp;
    for (auto &p : ans) {
        P v = p.sub(polygon[rt]);
        v = P(v.x * cosA - v.y * sinA, v.x * sinA + v.y * cosA);
        p = polygon[rt].add(v);
        printf("%.10f %.10f\n", p.x, p.y);
    }
    return 0;
}
