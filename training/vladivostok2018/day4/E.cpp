#include<bits/stdc++.h>

const int N = 10;

const double eps = 1e-9;
const double PI = acos(-1.0);
const double INF = 1e100;

inline int sig(double p){
    return (p > eps) - (p < -eps);
}

inline double sqr(double p){return p * p;}

class P{
public:
    double x, y;
    explicit P (double x = 0, double y = 0): x(x), y(y){}
    P operator + (const P &p)const{return P (x + p.x, y + p.y);}
    P operator - (const P &p)const{return P (x - p.x, y - p.y);}
    P operator * (const double &p)const{return P (x * p, y * p);}
    friend P operator * (const double &d, const P &p){return P (d * p.x, d * p.y);}
    P operator / (const double &p)const{return P (x / p, y / p);}
    double operator ^ (const P &p)const{return x * p.y - y * p.x;}
    double operator % (const P &p)const{return x * p.x + y * p.y;}
    double abs2()const{return *this % *this;}
    double abs()const{return std::sqrt(abs2());}
    double angle()const{
        double ret = std::atan2(y, x);
        if (ret < 0){
            ret += 2 * PI;
        }
        return ret;
    }

    void read(){
        scanf("%lf%lf", &x, &y);
    }
};

class L{
public:
    P p, v;
    double angle;

    L (){}
    L (P a, P b):p(a), v(b - a){angle = std::atan2(v.y, v.x);}

    bool operator < (const L &l)const{
        return angle < l.angle;
    }

    P point(double t){
        return p + v * t;
    }
};

P proj(L l, P p){
    return l.p + l.v * (l.v % (p - l.p) / l.v.abs2());
}

P symmetry(L l, P p){
    P q = proj(l, p);
    return 2 * q - p;
}

void cross(double &l1, double &r1, double &l2, double &r2, double angle1, double angle2){
    if (angle1 < 0){
        r1 = std::min(r1, angle2);
        l2 = std::max(l2, angle1 + 2 * PI);
    }
    else{
        l1 = std::max(l1, angle1);
        r1 = std::min(r1, angle2);
        l2 = std::max(l2, angle1);
        r2 = std::min(r2, angle2);
    }
}

int n;
P s;
P p[N];
bool vis[N];
int cnt;
int perm[N];

void dfs(int now, std::vector <P> vec, double l1, double r1, double l2, double r2){
    for (int i = 1; i <= n; ++ i){
        if (vis[i]) continue;
        vis[i] = true;
        perm[now] = i;
        P p1 = vec[i], p2 = vec[i % n + 1];
        double angle1 = (p1 - s).angle(), angle2 = (p2 - s).angle();
        L l(p1, p2);
        if (angle1 > angle2){
            std::swap(angle1, angle2);
        }
        if (angle2 - angle1 > PI){
            angle2 -= 2 * PI;
            std::swap(angle1, angle2);
        }
        double tmpl1 = l1, tmpr1 = r1, tmpl2 = l2, tmpr2 = r2;
        cross(tmpl1, tmpr1, tmpl2, tmpr2, angle1, angle2);
        if (sig(tmpr1 - tmpl1) <= 0 && sig(tmpr2 - tmpl2) <= 0){
            vis[i] = false;
            continue;
        }
        if (now + 1 == n){
            ++ cnt;
            //if (sig(tmpr1 - tmpl1) > 0){
            //    assert(check((tmpr1 + tmpl1) / 2));
            //}
            //if (sig(tmpr2 - tmpl2) > 0){
            //    assert(check((tmpr2 + tmpl2) / 2));
            //}
        }
        else{
            std::vector <P> nvec = vec;
            for (int j = 1; j <= n; ++ j){
                nvec[j] = symmetry(l, nvec[j]);
            }
            dfs(now + 1, nvec, tmpl1, tmpr1, tmpl2, tmpr2);
        }
        vis[i] = false;
    }
}

void solve(){
    s.read();
    for (int i = 1; i <= n; ++ i){
        p[i].read();
    }
    cnt = 0;
    memset(vis, 0, sizeof(vis));
    std::vector <P> vec(n + 1);
    for (int i = 1; i <= n; ++ i){
        vec[i] = p[i];
    }
    dfs(0, vec, 0, 2 * PI, 0, 2 * PI);
    printf("%d\n", cnt);
}

int main(){
    int time = clock();
    while (~scanf("%d", &n) && n){
        solve();
    }
    //printf("%f", 1.0 * (clock() - time) / CLOCKS_PER_SEC);
    return 0;
}

/*
4
0 0
-10 -10
10 -10
10 10
-10 10
4
0 0
0 10
-10 0
0 -10
10 0
0
*/

