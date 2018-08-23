#include <bits/stdc++.h>

#define ll long long

const double eps = 1e-6;

int dcmp(double p) { return (p > eps) - (p < -eps); }

double lm, lg;
struct P {
    double x, y;
    explicit P(double x = 0, double y = 0) : x(x), y(y) {}

    P add(const P &p) const { return P(x + p.x, y + p.y); }
    P sub(const P &p) const { return P(x - p.x, y - p.y); }
    P mul(const double &t) const { return P(x * t, y * t); }
    double det(const P &p) const { return x * p.y - y * p.x; }
    double dot(const P &p) const { return x * p.x + y * p.y; }
    double abs2() const { return dot(*this); }
    double abs() const { return std::sqrt(abs2()); }
}p[3];
struct L {
    P p, v;
    L() {}
    L(P a, P b) : p(a), v(b.sub(a)) {}
};

P proj(L l, P p) {
    return l.p.add(l.v.mul(l.v.dot(p.sub(l.p).mul(1. / l.v.abs2()))));
}

double disLP(L l, P p) {
    double ret = std::abs(l.v.det(p.sub(l.p)) / l.v.abs());
   // printf("dis = %f\n", ret);
    return ret;
}

bool check(P p, P a, P b) {
    P t = proj(L(a, b), p);
    if (dcmp(disLP(L(a, b), p) - lm) <= 0) {
        double tmp = t.sub(a).abs();
        double tmp2 = t.sub(b).abs();
        if (dcmp(tmp - lg) <= 0 && dcmp(tmp2 - lg) <= 0) return true;
    }
    if (dcmp(disLP(L(a, b), p) - lg) <= 0) {
        double max = 0.0;
        if (dcmp(a.sub(t).dot(b.sub(t))) < 0) return false;
        max = std::max(t.sub(b).abs(), t.sub(a).abs());
        if (dcmp(max - lm) <= 0) return true;
    }
    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T --) {
        scanf("%lf%lf", &lm, &lg);
        for (int i = 0; i < 3; ++i) {
            scanf("%lf%lf", &p[i].x, &p[i].y);
        }
        if (dcmp(p[0].sub(p[1]).det(p[2].sub(p[1]))) == 0) {
            double len = 0;
            for (int i = 0; i < 3; ++i) {
                for (int j = i + 1; j < 3; ++j) {
                    len = std::max(len, p[i].sub(p[j]).abs());
                }
            }
            if (dcmp(len - lm) <= 0 || dcmp(len - lg - lg) <= 0) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
            continue;
        }
        bool ans = false;
        ans |= check(p[0], p[1], p[2]);
        ans |= check(p[1], p[0], p[2]);
        ans |= check(p[2], p[0], p[1]);
        printf(ans ? "YES\n" : "NO\n");
    }
    return 0;
}

