#include<bits/stdc++.h>

const int N = 60;
const double eps = 1e-9;
const double INF = 1e100;
inline int sig(double x){return (x > eps) - (x < -eps);}

struct P{
    double x, y;

    P (double x = 0, double y = 0):x(x), y(y){}
};

struct Rec{
    double l, r, u, d;
};

struct Event{
    double y, t;
    int v;

    bool operator < (const Event &e)const{
        return y < e.y;
    }
};

P v[N];
Rec rec[N];
int n;
double W, H, e;

void add(std::vector <double> &vec, double k1, double b1, double k2, double b2){
    if (!sig(k1 - k2)) return;
    double x = (b2 - b1) / (k1 - k2);
    if (x >= 0 && x <= e){
        vec.push_back(x);
    }
}

double calc(double x){
    std::vector <double> vec = {0, e};
    std::vector <Event> evec;
    for (int i = 0; i < n; ++ i){
        double l = std::max(rec[i].l + x * v[i].x, 0.0);
        double r = std::min(rec[i].r + x * v[i].x, W);
        double u = std::min(rec[i].u + x * v[i].y, H);
        double d = std::max(rec[i].d + x * v[i].y, 0.0);
        if (sig(r - l) <= 0 || sig(u - d) <= 0) continue;
        evec.push_back({d, l, 1});
        evec.push_back({u, l, -1});
        evec.push_back({d, r, -1});
        evec.push_back({u, r, 1});
        vec.push_back(l);
        vec.push_back(r);
    }
    std::sort(vec.begin(), vec.end());
    std::sort(evec.begin(), evec.end());
    double ans = 0;
    for (int i = 0, sz = vec.size(); i < sz - 1; ++ i){
        int now = 0;
        double sum = 0;
        for (int j = 0, szj = evec.size(); j < szj - 1; ++ j){
            now += evec[j].v * (vec[i] >= evec[j].t);
            if (now){
                sum += evec[j + 1].y - evec[j].y;
            }
        }
        ans += sum * (vec[i + 1] - vec[i]);
    }
    return ans;
}

int main(){
    scanf("%d%lf%lf%lf", &n, &W, &H, &e);
    for (int i = 0; i < n; ++ i){
        double w, h, x, y;
        scanf("%lf%lf%lf%lf%lf%lf", &w, &h, &x, &y, &v[i].x, &v[i].y);
        rec[i] = {x, x + w, y + h, y};
    }
    rec[n] = {0, W, H, 0};
    std::vector <double> Time = {0, e};
    for (int i = 0; i <= n; ++ i){
        for (int j = i + 1; j <= n; ++ j){
            add(Time, rec[i].l, ::v[i].x, rec[j].l, ::v[j].x);
            add(Time, rec[i].l, ::v[i].x, rec[j].r, ::v[j].x);
            add(Time, rec[i].r, ::v[i].x, rec[j].l, ::v[j].x);
            add(Time, rec[i].r, ::v[i].x, rec[j].r, ::v[j].x);
            add(Time, rec[i].u, ::v[i].y, rec[j].u, ::v[j].y);
            add(Time, rec[i].u, ::v[i].y, rec[j].d, ::v[j].y);
            add(Time, rec[i].d, ::v[i].y, rec[j].u, ::v[j].y);
            add(Time, rec[i].d, ::v[i].y, rec[j].d, ::v[j].y);
        }
    }
    std::sort(Time.begin(), Time.end());
    double min = INF;
    for (auto u : Time){
        min = std::min(min, calc(u));
    }
    for (int i = 0, sz = Time.size(); i < sz - 1; ++ i){
        if (Time[i + 1] - Time[i] < 1e-4) continue;
        double left = Time[i], right = Time[i + 1];
        for (int i = 0; right - left > 1e-7; ++ i){
            double mid1 = (2 * left + right) / 3, mid2 = (left + 2 * right) / 3;
            if (calc(mid1) < calc(mid2)){
                right = mid2;
            }
            else{
                left = mid1;
            }
        }
        min = std::min(min, calc(left));
    }
    printf("%.10f\n", min);
    return 0;
}
