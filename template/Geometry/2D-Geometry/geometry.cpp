#include<bits/stdc++.h>

/*************************************************************************************************************************/
// Geometry Fundamental
const double eps = 1e-9;
const double PI = acos(-1.0);
const double INF = 1e100;

inline int dcmp(double p) { return (p > eps) - (p < -eps); }

inline double sqr(double p) { return p * p; }

// Point(sometimes also Vector)
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

    P rot90() const { return P(-y, x); }

    // 单位法向量
    P normal() { return rot90().mul(1. / abs()); }

    bool operator<(const P &p) const { return dcmp(x - p.x) ? x < p.x : dcmp(y - p.y) < 0; }

    bool operator==(const P &p) const { return !dcmp(x - p.x) && !dcmp(y - p.y); }
};

struct L {
    P p, v;
    double angle;

    L() {}

    L(P a, P b) : p(a), v(b.sub(a)) { angle = v.angle(); }

    bool operator<(const L &l) const { return angle < l.angle; }

    // 直线上一点，满足方向向量系数为t
    P point(double t) { return p.add(v.mul(t)); }
};

struct C {
    P o;
    double r;

    C() {}

    C(P o, double r) : o(o), r(r) {}

    // 圆上一点，满足x轴正方向到该点圆心连线逆时针角度为angle
    P point(double angle) { return o.add(P(r, 0).rot(angle)); }
};

// 两直线夹角
double rad(P p1, P p2) {
    return std::acos(p1.dot(p2) / (p1.abs() * p2.abs()));
}

/*************************************************************************************************************************/
// 交点与距离相关

// Intersection of Line l1 and Line l2
double isLL(L l1, L l2) {
    return l2.p.sub(l1.p).det(l2.v) / l1.v.det(l2.v); // 返回 t, 交点在 l1.p + l1.v * t, 可以用来判断射线、线段等
}

// 返回点 p 到直线 l 的有向距离, p 在直线逆时针方向为正
double disLP(L l, P p) {
    return l.v.det(p.sub(l.p)) / l.v.abs();
}

// 返回点 q 到线段 p1->p2 的距离
double disSP(P p1, P p2, P q) {
    if (p1 == p2) return q.sub(p1).abs();
    P v1 = p2.sub(p1), v2 = q.sub(p1), v3 = q.sub(p2);
    if (dcmp(v1.dot(v2)) < 0) return v2.abs();
    if (dcmp(v1.dot(v3)) > 0) return v3.abs();
    return std::abs(v1.det(v2)) / v1.abs();
}

// 返回点 p 在直线 l 上的投影坐标
P proj(L l, P p) {
    return l.p.add(l.v.mul(l.v.dot(p.sub(l.p).mul(1. / l.v.abs2()))));
}

// 返回点 p 关于直线 l 对称后的点坐标
P symm(L l, P p) {
    return proj(l, p).mul(2).sub(p);
}

// 判断线段是否严格相交（包括严格重合）, 即交点不仅是端点处
bool crsSS(P p1, P p2, P q1, P q2) {
    double c1 = p2.sub(p1).det(q1.sub(p1));
    double c2 = p2.sub(p1).det(q2.sub(p1));
    if (!dcmp(c1) && !dcmp(c2)) { // 重合的情况
        if (p2 < p1) std::swap(p1, p2);
        if (q2 < q1) std::swap(q1, q2);
        return std::max(p1, q1) < std::min(p2, q2);
    }
    double c3 = q2.sub(q1).det(p1.sub(q1));
    double c4 = q2.sub(q1).det(p2.sub(q1));
    return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}

// 返回点 q 是否在线段 p1->p2 上, 包括是端点的情况
bool onSeg(P p1, P p2, P q) {
    double len = q.sub(p1).abs();
    if (!dcmp(len)) return true;
    p1 = p1.sub(q), p2 = p2.sub(q);
    return !dcmp(p1.det(p2) / len) && dcmp(p1.dot(p2)) <= 0;
}

// 返回点 q 是否在射线 p1->p2 上, 包括是p1的情况
bool onRay(P p1, P p2, P q) {
    double len = q.sub(p1).abs();
    if (!dcmp(len)) return true;
    p1 = q.sub(p1), p2 = q.sub(p2);
    return !dcmp(p1.det(p2) / len) && dcmp(p1.dot(p2.sub(p1))) >= 0;
}

// 返回圆 c1 和直线 l 的交点集合
std::vector<double> isCL(C c1, L l) {
    double a = l.v.x, b = l.p.x - c1.o.x, c = l.v.y, d = l.p.y - c1.o.y;
    double e = sqr(a) + sqr(c), f = 2 * (a * b + c * d);
    double g = sqr(b) + sqr(d) - sqr(c1.r);
    double delta = sqr(f) - 4 * e * g;
    if (dcmp(delta) < 0) return {};
    if (!dcmp(delta)) return {-f / (2 * e)};
    std::vector<double> ret;
    ret.push_back((-f - std::sqrt(delta)) / (2 * e));
    ret.push_back((-f + std::sqrt(delta)) / (2 * e));
    return ret;
}

// 返回圆 c1 和 c2 的位置关系(重合:-1，内含:0，内切:1，相交:2，外切:3，相离:4)和交点集合
std::pair<int, std::vector<P>> isCC(C c1, C c2) {
    double d = c1.o.sub(c2.o).abs2();
    if (!dcmp(d)) {
        if (!dcmp(c1.r - c2.r)) return {-1, {}};
        return {0, {}};
    }
    if (dcmp(c1.r + c2.r - std::sqrt(d)) < 0) return {4, {}};
    if (dcmp(std::abs(c1.r - c2.r) - std::sqrt(d)) > 0) return {0, {}};
    double x = ((sqr(c1.r) - sqr(c2.r)) / d + 1) / 2;
    double y = std::max(sqr(c1.r) / d - sqr(x), 0.0);
    P q1 = c1.o.add(c2.o.sub(c1.o).mul(x));
    P q2 = c2.o.sub(c1.o).mul(std::sqrt(y)).rot90();
    if (!dcmp(y)) {
        return {!dcmp(c1.r + c2.r - std::sqrt(d)) ? 3 : 1, {q1}};
    }
    return {2, {q1.sub(q2), q1.add(q2)}};
}

/*************************************************************************************************************************/
// nlog{A / eps) 判断n个圆交集是否为空

int isCs(std::vector<C> &c, double mid) {
    int n = c.size();
    double left = -INF, right = INF;
    for (int i = 0; i < n; ++i) {
        if (dcmp(mid - c[i].o.x - c[i].r) > 0) return 1;
        if (dcmp(c[i].o.x - c[i].r - mid) > 0) return 2;
        double delta = std::sqrt(std::max(0.0, sqr(c[i].r) - sqr(mid - c[i].o.x)));
        left = std::max(left, c[i].o.y - delta);
        right = std::min(right, c[i].o.y + delta);
        if (dcmp(left - right) > 0) {
            for (int j = 0; j < i; ++j) {
                auto u = isCC(c[i], c[j]);
                auto ps = u.second;
                if (u.first <= 1) continue;
                if (u.first == 4) return 1;
                if (u.first == 3) {
                    if (!dcmp(ps[0].x - mid)) continue;
                    return dcmp(ps[0].x - mid) < 0 ? 1 : 2;
                }
                if (!dcmp(ps[0].x - mid) || dcmp(ps[1].x - mid) != dcmp(ps[0].x - mid)) continue;
                return dcmp(ps[0].x - mid) < 0 ? 1 : 2;
            }
        }
    }
    return 0;
}

bool isCs(std::vector<C> &c) {
    double right = -INF, left = INF;
    for (auto u : c) {
        right = std::max(right, u.o.x + u.r);
        left = std::min(left, u.o.x - u.r);
    }
    for (int i = 0; i < 50; ++i) {
        double mid = (left + right) / 2;
        int x = isCs(c, mid);
        if (!x) return true;
        if (x == 1) right = mid;
        else left = mid;
    }
    return false;
}

/*************************************************************************************************************************/
// 圆相关

// 返回圆 c1 与圆 c2 的交集面积
double areaCC(C c1, C c2) {
    double d = c1.o.sub(c2.o).abs();
    if (dcmp(c1.r + c2.r - d) <= 0) return 0;
    if (dcmp(d - std::abs(c1.r - c2.r)) <= 0) return sqr(std::min(c1.r, c2.r)) * PI;
    double x = (sqr(d) + sqr(c1.r) - sqr(c2.r)) / (2 * d);
    double t1 = std::acos(x / c1.r), t2 = std::acos((d - x) / c2.r);
    return sqr(c1.r) * t1 + sqr(c2.r) * t2 - d * c1.r * sin(t1);
}

// 返回过点 p 的切线与圆 c 的交点集合, p 在圆上时返回 p 点本身, p 在圆内时返回空
std::vector<P> tanCP(C c, P p) {
    P v = p.sub(c.o);
    double d = v.abs2(), x = d - sqr(c.r);
    if (dcmp(x) < 0) return {};
    if (!dcmp(x)) return {p};
    P q1 = v.mul(sqr(c.r) / d);
    P q2 = v.mul(-c.r * std::sqrt(x) / d).rot90();
    P ret = c.o.add(q1);
    return {ret.sub(q2), ret.add(q2)};
}

// 返回圆 c1 与圆 c2 的公切线集合
std::vector<L> tanCC(C c1, C c2) {
    std::vector<L> ret;
    if (!dcmp(c1.r - c2.r)) {
        P dir = c2.o.sub(c1.o);
        dir = dir.mul(c1.r / dir.abs()).rot90();
        ret.push_back(L(c1.o.add(dir), c2.o.add(dir)));
        ret.push_back(L(c1.o.sub(dir), c2.o.sub(dir)));
    } else {
        P p = c1.o.mul(-c2.r).add(c2.o.mul(c1.r)).mul(1. / (c1.r - c2.r));
        std::vector<P> ps = tanCP(c1, p), qs = tanCP(c2, p);
        for (int i = 0; i < ps.size() && i < qs.size(); ++i) {
            ret.push_back(L(ps[i], qs[i]));
        }
    }
    P p = c1.o.mul(c2.r).add(c2.o.mul(c1.r)).mul(1. / (c1.r + c2.r));
    std::vector<P> ps = tanCP(c1, p), qs = tanCP(c2, p);
    for (int i = 0; i < ps.size() && i < qs.size(); ++i) {
        ret.push_back(L(ps[i], qs[i]));
    }
    for (auto &u : ret) {
        if (u.v == P(0, 0)) u.v = u.p.sub(c1.o).rot90();
    }
    return ret;
}

// 返回三角形 p1->p2->p3 的内切圆
C inC(P p1, P p2, P p3) {
    double a = p3.sub(p2).abs(), b = p1.sub(p3).abs(), c = p2.sub(p1).abs();
    P p = p1.mul(a).add(p2.mul(b).add(p3.mul(c))).mul(1. / (a + b + c)); // (a * p1 + b * p2 + c * p3) / (a + b + c)
    return C(p, std::abs(disLP(L(p1, p2), p)));
}

// 返回三角形 p1->p2->p3 的外接圆
C outC(P p1, P p2, P p3) {
    P q1 = p1.add(p2).mul(0.5), v1 = p1.sub(p2).normal();
    P q2 = p2.add(p3).mul(0.5), v2 = p2.sub(p3).normal();
    L l1(q1, q1.add(v1)), l2(q2, q2.add(v2));
    double t = isLL(l1, l2);
    P p = l1.point(t);
    return C(p, p1.sub(p).abs());
}

/*************************************************************************************************************************/
// 多边形, 凸包, 半平面交

// 返回点 q 与简单多边形 ps 的位置关系(内部:1, 外部:-1, 边上:0)
int inPolygon(std::vector<P> &ps, P q) {
    int n = ps.size();
    for (int i = 0; i < n; ++i) {
        if (onSeg(ps[i], ps[(i + 1) % n], q)) return 0;
    }
    int ret = -1;
    for (int i = 0; i < n; ++i) {
        P a = ps[i], b = ps[(i + 1) % n];
        if (a.y > b.y) std::swap(a, b);
        if (dcmp(a.sub(q).det(b.sub(q))) < 0 && dcmp(a.y - q.y) < 0 && dcmp(b.y - q.y) >= 0) ret = -ret;
    }
    return ret;
}

// 当返回值大于0时, 点 q 在直线 l 左边
double onLeft(L l, P p) {
    return l.v.det(p.sub(l.p));
}

// 返回点集 ps 的凸包, 返回的凸包为逆时针方向
std::vector<P> convexHull(std::vector<P> &ps) {
    static P stack[100010]; // 抄时记得修改
    std::sort(ps.begin(), ps.end());
    int n = ps.size(), top = 0;
    auto check = [&](int i) {
        return dcmp(onLeft(L(stack[top - 2], stack[top - 1]), ps[i])) <= 0;
    };
    for (int i = 0; i < n; ++i) {
        while (top > 1 && check(i)) --top;
        stack[top++] = ps[i];
    }
    for (int i = n - 2, tmp = top; ~i; --i) {
        while (top > tmp && check(i)) --top;
        stack[top++] = ps[i];
    }
    if (n > 1) --top;
    std::vector<P> ret;
    for (int i = 0; i < top; ++i) ret.push_back(stack[i]);
    return ret;
}

// O(n + m) 求凸包 ps 和 qs 的闵科夫斯基和的凸包
std::vector<P> minkSum(std::vector<P> &ps, std::vector<P> &qs) {
    std::vector<P> ret;
    int n = ps.size(), m = qs.size();
    P cur = ps[0].add(qs[0]);
    for (int i = 0, j = 0; i < n || j < m;) {
        if (i < n && (j == m || dcmp(ps[i + 1].sub(ps[i]).det(qs[j + 1].sub(qs[j]))) >= 0)) {
            cur = cur.add(ps[i + 1].sub(ps[i]));
            ++i;
        } else {
            cur = cur.add(qs[j + 1].sub(qs[j]));
            ++j;
        }
        ret.push_back(cur);
    }
    return ret;
}

// O(logn) 判断点 q 是否在凸包 ps 内部(包括恰在边上)
bool inConvex(std::vector<P> &ps, P q) {
    int n = ps.size();
    if (dcmp(onLeft(L(ps[0], ps[1]), q)) < 0 || dcmp(onLeft(L(ps[0], ps[n - 1]), q) > 0)) return false;
    int lo = 2, hi = n - 1;
    while (lo < hi) {
        int mi = (lo + hi) >> 1;
        if (dcmp(onLeft(L(ps[0], ps[mi]), q)) <= 0) {
            hi = mi;
        } else {
            lo = mi + 1;
        }
    }
    return dcmp(onLeft(L(ps[lo - 1], ps[lo]), q)) >= 0;
}

// O(logn) 求过凸包 ps 外一点 q 与凸包的切线交点, 右边的一个
int tanConPR(std::vector<P> &ps, P q) {
    int ret = 0, n = ps.size();
    int lo = 1, hi = n - 1;
    while (lo <= hi) {
        bool dnl = onLeft(L(q, ps[lo + 1]), ps[lo]) > 0;
        int mid = (lo + hi) >> 1;
        bool dnm = onLeft(L(q, ps[mid + 1]), ps[mid]) > 0;
        if (dnm) {
            if (onLeft(L(q, ps[ret]), ps[mid]) > 0) {
                ret = mid;
            }
        }
        if (dnl) {
            if (onLeft(L(q, ps[ret]), ps[lo]) > 0) {
                ret = lo;
            }
            if (dnm && onLeft(L(q, ps[lo]), ps[mid]) > 0) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        } else {
            if (!dnm && onLeft(L(q, ps[lo]), ps[mid]) > 0) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
    }
    return ret;
}

// O(logn) 求过凸包 ps 外一点 q 与凸包的切线交点, 左边的一个
int tanConPL(std::vector<P> &ps, P q) {
    int ret = 0, n = ps.size();
    int lo = 1, hi = n - 1;
    while (lo <= hi) {
        bool dnl = onLeft(L(q, ps[lo - 1]), ps[lo]) < 0;
        int mid = (lo + hi + 1) >> 1;
        bool dnm = onLeft(L(q, ps[mid - 1]), ps[mid]) < 0;
        if (dnm) {
            if (onLeft(L(q, ps[ret]), ps[mid]) < 0) {
                ret = mid;
            }
        }
        if (dnl) {
            if (onLeft(L(q, ps[ret]), ps[lo]) < 0) {
                ret = lo;
            }
            if (dnm && onLeft(L(q, ps[lo]), ps[mid]) < 0) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        } else {
            if (!dnm && onLeft(L(q, ps[lo]), ps[mid]) > 0) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
    }
    return ret;
}

// 求凸包 ps 与直线 p->q 的交点集合, 要求凸包为逆时针方向
std::vector<P> isConL(std::vector<P> &ps, P p, P q) {
    std::vector<double> arc;
    int n = ps.size();
    for (int i = 0; i < n; ++i) {
        ps.push_back(ps[i]);
    }
    ps.push_back(ps[0]);
    for (int i = 0; i < n; ++i) {
        arc.push_back(L(ps[i], ps[i + 1]).angle);
        if (i && arc[i] < arc[i - 1]) {
            arc[i] += 2 * PI;
        }
    }
    auto getseg = [&ps](L l, int left, int right) {
        --left;
        while (left < right) {
            int mid = (left + right + 1) >> 1;
            if (dcmp(l.v.det(ps[mid].sub(l.p))) < 0) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }
        return left;
    };
    if (q < p) std::swap(p, q);
    L l1(p, q), l2(q, p);
    double al = l1.angle;
    if (al < arc[0]) al += 2 * PI;
    int left = (std::lower_bound(arc.begin(), arc.end(), al) - arc.begin()) % n;
    double ar = l2.angle;
    if (ar < arc[0]) ar += 2 * PI;
    int right = std::lower_bound(arc.begin(), arc.end(), ar) - arc.begin();
    int down = getseg(l1, left, right);
    int up = getseg(l2, right, left + n);
    std::vector<P> ret;
    if (down >= left && up >= right) {
        double t = isLL(l1, L(ps[down], ps[down + 1]));
        ret.push_back(l1.point(t));
        t = isLL(l2, L(ps[up], ps[up + 1]));
        ret.push_back(l2.point(t));
    }
    ps.erase(ps.begin() + n, ps.end());
    return ret;
}

// 用直线 p->q 切割凸包 ps, 保留左半平面部分, O(n)
std::vector<P> cutCon(std::vector<P> &ps, P p, P q) {
    std::vector<P> ret;
    int n = ps.size();
    for (int i = 0; i < n; ++i) {
        P a = ps[i], b = ps[(i + 1) % n];
        if (dcmp(q.sub(p).det(a.sub(p))) >= 0) ret.push_back(a);
        if (!dcmp(q.sub(p).det(b.sub(a)))) {
            double t = isLL(L(a, b), L(p, q));
            if (dcmp(t) > 0 && dcmp(t - 1) < 0) {
                ret.push_back(a.add(b.sub(a).mul(t)));
            }
        }
    }
    return ret;
}

// 返回直线集合 ls 的半平面交
std::vector<P> isHalfPlane(std::vector<L> &ls) {
    std::sort(ls.begin(), ls.end());
    std::deque<L> dq;
    std::deque<P> ps;
    dq.push_back(ls[0]);
    int n = ls.size();
    auto isLLP = [](L l1, L l2) { return l1.point(isLL(l1, l2)); };
    for (int i = 1; i < n; ++i) {
        while (!ps.empty() && dcmp(onLeft(ls[i], ps.back())) <= 0) ps.pop_back(), dq.pop_back();
        while (!ps.empty() && dcmp(onLeft(ls[i], ps.front())) <= 0) ps.pop_front(), dq.pop_front();
        L l = dq.back();
        if (dcmp(ls[i].v.det(l.v))) {
            dq.push_back(ls[i]);
            ps.push_back(isLLP(l, ls[i]));
        } else {
            if (dcmp(onLeft(l, ls[i].p)) > 0) {
                dq.pop_back();
                if (!dq.empty()) {
                    ps.pop_back();
                    ps.push_back(isLLP(dq.back(), ls[i]));
                }
                dq.push_back(ls[i]);
            }
        }
    }
    while (!ps.empty() && dcmp(onLeft(dq.front(), ps.back())) <= 0) ps.pop_back(), dq.pop_back();
    if (dq.size() <= 2) return {};
    ps.push_back(isLLP(dq.front(), dq.back()));
    std::vector<P> ret;
    while (!ps.empty()) {
        ret.push_back(ps.front());
        ps.pop_front();
    }
    return ret;
}

// 返回圆 c 与简单多边形 ps 的交集面积
double areaCPol(C c, std::vector<P> &ps) {
    auto area = [c](P p, P q) {
        double theta = p.sub(c.o).angle() - q.sub(c.o).angle();
        if (theta < 0) theta += PI * 2;
        if (theta >= 2 * PI) theta -= PI * 2;
        theta = std::min(theta, 2 * PI - theta);
        return sqr(c.r) * theta;
    };
    double ret = 0;
    int n = ps.size();
    for (int i = 0; i < n; ++i) {
        P p1 = ps[i], p2 = ps[(i + 1) % n];
        L l(p1, p2);
        std::vector<double> vec = isCL(c, l);
        double tmp = 0;
        P v1 = p1.sub(c.o), v2 = p2.sub(c.o);
        bool flag1 = dcmp(v1.abs2() - sqr(c.r)) <= 0, flag2 = dcmp(v2.abs2() - sqr(c.r)) <= 0;
        if (flag1 && flag2) {
            tmp = std::abs(v1.det(v2));
        } else if (flag1 || flag2) {
            if (!flag1) {
                P p = l.point(vec[0]);
                tmp = area(p1, p) + std::abs(p.sub(c.o).det(v2));
            } else {
                P p = l.point(*(--vec.end()));
                tmp = area(p, p2) + std::abs(v1.det(p.sub(c.o)));
            }
        } else {
            if (vec.size() == 2 && dcmp(vec[0]) > 0 && dcmp(vec[0] - 1) < 0) {
                P p3 = l.point(vec[0]), p4 = l.point(vec[1]);
                tmp = area(p1, p3) + area(p4, p2) + std::abs(p3.sub(c.o).det(p4.sub(c.o)));
            } else {
                tmp = area(p1, p2);
            }
        }
        ret += tmp * dcmp(v1.det(v2));
    }
    return std::abs(ret) / 2;
}

/*************************************************************************************************************************/
// 圆并与圆交

// O(n^2logn) 求圆集合 cs 的并集面积与重心，被卡时间时可预先去掉被其它圆包含的圆
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
            double angle = L(cs[i].o, cs[j].o).angle;
            double p = (sqr(cs[i].r) + sqr(dis) - sqr(cs[j].r)) / (2 * cs[i].r * dis);
            p = std::acos(std::max(-1.0, std::min(1.0, p)));
            double left = angle - p, right = angle + p;
            if (left < 0) left += PI * 2;
            if (right < 0) right += PI * 2;
            if (left >= 2 * PI) left -= PI * 2;
            if (right >= 2 * PI) right -= PI * 2;
            vec.push_back({left, 1});
            vec.push_back({right, -1});
            if (left >= right) {
                ++cnt;
            }
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
    return {ret / 2, pret.mul(1. / ret)};
}

// O(n^2logn) 求圆集合 ccs 的交集面积
double areaisCs(std::vector<C> &ccs) {
    std::vector<C> cs;
    for (int i = 0, sz = ccs.size(); i < sz; ++i) {
        bool flag = true;
        for (int j = 0; j < sz; ++j) {
            if (i == j) continue;
            double dis = ccs[i].o.sub(ccs[j].o).abs();
            if (dcmp(dis - ccs[i].r - ccs[j].r) >= 0) return 0.0;
            if (!dcmp(dis) && !dcmp(ccs[i].r - ccs[j].r)) {
                if (i < j) {
                    flag = false;
                    break;
                }
            } else {
                if (dcmp(dis + ccs[i].r - ccs[j].r) <= 0) {
                    flag = false;
                    break;
                }
            }
        }
        if (flag) cs.push_back(ccs[i]);
    }
    int n = cs.size();
    typedef std::pair<double, double> pdd;
    auto inter = [](const pdd &p1, const pdd &p2, std::vector<pdd> &vec) {
        pdd p = {std::max(p1.first, p2.first), std::min(p1.second, p2.second)};
        if (p.first <= p.second) vec.push_back(p);
    };
    double ret = 0;
    for (int i = 0; i < n; ++i) {
        std::vector<pdd> vec = {{0, 2 * PI}};
        for (int j = 0; j < n; ++j) {
            double angle = L(cs[i].o, cs[j].o).angle;
            double dis = cs[i].o.sub(cs[j].o).abs();
            double p = (sqr(cs[i].r) + sqr(dis) - sqr(cs[j].r)) / (2 * cs[i].r * dis);
            p = std::acos(std::max(-1.0, std::min(1.0, p)));
            double left = angle - p, right = angle + p;
            if (left < 0) left += PI * 2;
            if (right < 0) right += PI * 2;
            if (left >= 2 * PI) left -= PI * 2;
            if (right >= 2 * PI) right -= PI * 2;
            std::vector<pdd> tmp;
            for (auto u : vec) {
                if (left >= right) {
                    inter({left, 2 * PI}, u, tmp);
                    inter({0, right}, u, tmp);
                } else {
                    inter({left, right}, u, tmp);
                }
            }
            vec = tmp;
        }
        for (auto u : vec) {
            P p1 = cs[i].point(u.first), p2 = cs[i].point(u.second);
            double delta = u.second - u.first;
            ret += sqr(cs[i].r) * (delta - std::sin(delta));
            ret += p1.det(p2);
        }
    }
    return ret / 2;
}

/*************************************************************************************************************************/

// 求点 q 到凸多边形 ps 的距离，ps 必须是逆时针的，p 必须在 ps 外部
double disConvexP(std::vector<P> &ps, P q) {
    int n = ps.size();
    int left = 0, right = n;
    auto pin = [](P p1, P p2, P q) {
        return dcmp(p1.det(q)) >= 0 && dcmp(p2.det(q)) <= 0;
    };
    auto in = [pin](P p1, P p2, P p3, P p4, P q) {
        P o12 = p1.sub(p2).rot90();
        P o23 = p2.sub(p3).rot90();
        P o34 = p3.sub(p4).rot90();
        return pin(o12, o23, q.sub(p2)) || pin(o23, o34, q.sub(p3))
               || (pin(o23, p3.sub(p2), q.sub(p2)) && pin(p2.sub(p3), o23, q.sub(p3)));
    };
    while (right - left > 1) {
        int mid = (left + right) >> 1;
        if (in(ps[(left + n - 1) % n], ps[left], ps[mid], ps[(mid + 1) % n], q)) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return disSP(ps[left], ps[right % n], q);
}

// 求凸多边形 ps 的直径
double convexDiameter(std::vector<P> &ps) {
    int n = ps.size();
    int is = 0, js = 0;
    for (int i = 1; i < n; ++i) {
        if (ps[i].x > ps[is].x) {
            is = i;
        }
        if (ps[i].x < ps[js].x) {
            js = i;
        }
    }
    double maxd = ps[is].sub(ps[js]).abs();
    int i = is, j = js;
    do {
        if (dcmp((ps[(i + 1) % n].sub(ps[i])).det((ps[(j + 1) % n].sub(ps[j])))) >= 0) {
            j = (j + 1) % n;
        } else {
            i = (i + 1) % n;
        }
        maxd = std::max(maxd, ps[i].sub(ps[j]).abs());
    } while (i != is || j != js);
    return maxd;
}

// 求 ps 中的点的最小包围圆
C minCoverC(std::vector<P> &ps) {
    int n = ps.size();
    std::random_shuffle(ps.begin(), ps.end());
    C ret(ps[0], 0);
    for (int i = 1; i < n; ++i) {
        if (dcmp(ps[i].sub(ret.o).abs() - ret.r) > 0) {
            ret = C(ps[i], 0);
            for (int j = 0; j < i; ++j) {
                if (dcmp(ps[j].sub(ret.o).abs() - ret.r) > 0) {
                    ret = C(ps[i].add(ps[j]).mul(0.5), ps[i].sub(ps[j]).abs() / 2);
                    for (int k = 0; k < j; ++k) {
                        if (dcmp(ps[k].sub(ret.o).abs() - ret.r) > 0) {
                            ret = outC(ps[i], ps[j], ps[k]);
                        }
                    }
                }
            }
        }
    }
    return ret;
}

/*
namespace plane {
    void work() {
        scanf("%d" , &n);
        for (int i = 0 ; i < n ; ++ i) {
            L[i].input();
            P[i] = L[i];
        }
        int m = n;
        for (int i = 0 ; i + 1 < n ; ++ i)
            for (int j = i + 1 ; j + 1 < n ; ++ j) {
                if (dcmp((P[i + 1] - P[i]) ^ (P[j + 1] - P[j])) != 0)
                    P[m ++] = GetLineIntersection(P[i] , P[i + 1] - P[i] , P[j] , P[j + 1] - P[j]);
            }
        sort(P , P + m);
        m = unique(P , P + m) - P;
        memset(pre , -1 , sizeof(pre));
        set< pair<int , int> > Hash;
        for (int i = 0 ; i + 1 < n ; ++ i) {
            vector< pair <Point , int> > V;
            for (int j = 0 ; j < m ; ++ j)
                if (OnSegment(P[j] , L[i] , L[i + 1]))
                    V.push_back(make_pair(P[j] , j));
            sort(V.begin() , V.end());
            for (int j = 0 ; j + 1 < V.size() ; ++ j) {
                int x = V[j].second , y = V[j + 1].second;
                if (!Hash.count(make_pair(x , y))) {
                    Hash.insert(make_pair(x , y));
                    e[mcnt] = (edge) {y , pre[x]} , pre[x] = mcnt ++;
                }
                if (!Hash.count(make_pair(y , x))) {
                    Hash.insert(make_pair(y , x));
                    e[mcnt] = (edge) {x , pre[y]} , pre[y] = mcnt ++;
                }
            }
        }
        for (int x = 0 ; x < m ; ++ x) {
            vector< pair<double , int> > V;
            for (int i = pre[x] ; ~i ; i = e[i].next) {
                int y = e[i].x;
                V.push_back(make_pair((P[y] - P[x]).arg() , i));
            }
            sort(V.begin() , V.end());
            for (int i = 0 ; i < V.size() ; ++ i) {
                int j = (i + 1) % V.size();
                Next[V[j].second ^ 1] = V[i].second;
            }
        }
        double res = 0;
        for (int i = 0 ; i < mcnt ; ++ i) {
            if (!vis[i]) {
                int x = i;
                double area = 0;
                while (!vis[x]) {
                    vis[x] = 1;
                    area += (P[e[x ^ 1].x] ^ P[e[x].x]);
                    x = Next[x];
                }
                if (x == i && dcmp(area) > 0)
                    res += area;
            }
        }
        printf("%.8f\n" , res / 2);
    }
};
*/


int main() {
    srand((unsigned) time(NULL));
    return 0;
}
