#include <bits/stdc++.h>

const int N = 5010;
const long double eps = 1e-9;
typedef long long ll;

inline int sig(long double p){return (p > eps) - (p < -eps);}
inline long double sqr(long double p){return p * p;}

struct P{
    long double x, y;

    P(long double x = 0, long double y = 0):x(x), y(y){}

    P operator +(const P &p)const{return P(x + p.x, y + p.y);}
    P operator -(const P &p)const{return P(x - p.x, y - p.y);}
    P operator *(const long double &p)const{return P(x * p, y * p);}
    P operator /(const long double &p)const{return P(x / p, y / p);}
    long double operator ^(const P &p)const{return x * p.y - y * p.x;}
    long double operator %(const P &p)const{return x * p.x + y * p.y;}

    long double abs2()const{return *this % *this;}
    long double abs()const{return std::sqrt(abs2());}

    bool operator ==(const P &p)const{
        return !sig(x - p.x) && !sig(y - p.y);
    }
};

struct L{
    P p, v;

    L(P p1, P p2):p(p1), v(p2 - p1){}

    P point(long double t){return p + v * t;}
};

bool para(L l1, L l2){
    return !sig(l1.v ^ l2.v);
}

long double isLL(L l1, L l2){
    P u = l2.p - l1.p;
    return (u ^ l2.v) / (l1.v ^ l2.v);
}

ll getarea(P p1, P p2, P p3){
    return std::abs(std::round((p2 - p1) ^ (p3 - p1)));
}

long double getdbarea(P p1, P p2, P p3){
    return std::abs((p2 - p1) ^ (p3 - p1));
}

long double getsin(P e1, P e2){
    return std::sqrt(1 - sqr(e1 % e2));
}

bool onSeg(P p, L l){
    long double dot = (p - l.p) % l.v;
    return sig(dot) >= 0 && sig(dot - l.v.abs2()) <= 0;
}

bool onLeft(P p, L l){
    return sig(l.v ^ (p - l.p)) > 0;
}

P proj(L l, P p){
    return l.p + l.v * (l.v % (p - l.p) / l.v.abs2());
}

int main(){
    int n;
    scanf("%d", &n);
    std::vector <P> vec(n << 1);
    for (int i = 0; i < n; ++ i){
        scanf("%Lf%Lf", &vec[i].x, &vec[i].y);
        vec[i + n] = vec[i];
    }
    ll area = 0;
    for (int i = 1; i < n - 1; ++ i){
        area += getarea(vec[0], vec[i], vec[i + 1]);
    }
    ll nowarea = 0, tmparea = 0;
    long double min = 1e30, max = 0;
    for (int i = 0, j = 0; i < n; ++ i, j = std::max(j, i)) {
        while (true) {
            tmparea = nowarea + getarea(vec[i], vec[j], vec[j + 1]);
            if (tmparea * 2 > area) {
                break;
            }
            nowarea = tmparea;
            ++j;
        }
        long double t = (area / 2.0 - nowarea) / (tmparea - nowarea);
        P begin = vec[i], end = L(vec[j], vec[j + 1]).point(t);
        long double dis = (end - begin).abs();
        max = std::max(max, dis);
        min = std::min(min, dis);
        L l1(vec[i], vec[i + 1]), l2(vec[j], vec[j + 1]);
        P cross, e1, e2;
        long double len;
        if (para(l1, l2)) {
            cross = proj(l1, vec[j]);
            e1 = P(0, 0) - l1.v, e2 = l2.v;
            e1 = e1 / e1.abs(), e2 = e2 / e2.abs();
            long double basearea = nowarea - getdbarea(vec[i], vec[j], cross);
            long double width = (vec[j] - cross).abs();
            len = (area - 2 * basearea) / (4 * width);
        }
        else {
            cross = l1.point(isLL(l1, l2));
            e1 = (vec[i] == cross ? vec[i + 1] : vec[i]) - cross, e2 = (vec[j] == cross ? vec[j + 1] : vec[j]) - cross;
            e1 = e1 / e1.abs(), e2 = e2 / e2.abs();
            long double basearea;
            if (!onLeft(cross, L(vec[i], vec[j]))) {
                basearea = nowarea - getdbarea(vec[i], vec[j], cross);
            } else {
                basearea = area - nowarea - getdbarea(vec[i], vec[j], cross);
            }
            long double sin = getsin(e1, e2);
            len = std::sqrt((area - 2 * basearea) / (2 * sin));
        }
        P p1 = cross + e1 * len, p2 = (para(l1, l2) ? vec[j] : cross) + e2 * len;
        if (onSeg(p1, l1) && onSeg(p2, l2)) {
            dis = (p1 - p2).abs();
            max = std::max(max, dis);
            min = std::min(min, dis);
        }
        nowarea -= getarea(vec[i], vec[i + 1], vec[j]);
    }
    printf("%.15Lf\n%.15Lf\n", min, max);
    return 0;
}