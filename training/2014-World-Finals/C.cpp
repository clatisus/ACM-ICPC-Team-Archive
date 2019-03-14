#include<bits/stdc++.h>

const int N = 110;
typedef std::pair <int, int> P;
typedef long long ll;

P p[N];

int det(P p1, P p2){
    return p1.first * p2.second - p1.second * p2.first;
}

P operator +(const P &p1, const P &p2){
    return {p1.first + p2.first, p1.second + p2.second};
}

P operator -(const P &p1, const P &p2){
    return {p1.first - p2.first, p1.second - p2.second};
}

ll divdown(ll a, ll b){
    return a / b - (a % b && (a < 0 ^ b < 0));
}

ll divup(ll a, ll b){
    if (b < 0){
        a = -a, b = -b;
    }
    return divdown(a + b - 1, b);
}

int main(){
    int n;
    scanf("%d", &n);
    int left = INT_MAX, right = INT_MIN;
    for (int i = 0; i < n; ++ i){
        scanf("%d%d", &p[i].first, &p[i].second);
        if (p[i].second == 0){
            left = std::min(left, p[i].first);
            right = std::max(right, p[i].first);
        }
    }
    ll area = 0, xsum = 0;
    for (int i = 1; i < n - 1; ++ i){
        int tarea = det(p[i] - p[0], p[i + 1] - p[0]);
        xsum += 1ll * tarea * (p[0].first + p[i].first + p[i + 1].first);
        area += tarea;
    }
    if (area < 0){
        area = -area, xsum = -xsum;
    }
    if (xsum == 3 * area * p[0].first) {
        if (xsum < 3 * area * left || xsum > 3 * area * right) {
            puts("unstable");
            return 0;
        }
        puts("0 .. inf");
        return 0;
    }
    ll l = 0, r = -1;
    if (xsum > 3 * area * p[0].first){
        if (p[0].first >= right){
            puts("unstable");
            return 0;
        }
        if (xsum < 3 * area * left){
            puts("unstable");
            return 0;
        }
        if (p[0].first < left){
            r = divup(xsum - 3 * area * left, 6 * (left - p[0].first));
        }
        if (xsum > 3 * area * right) {
            l = divdown(xsum - 3 * area * right, 6 * (right - p[0].first));
        }
    }
    else{
        if (p[0].first <= left){
            puts("unstable");
            return 0;
        }
        if (xsum > 3 * area * right){
            puts("unstable");
            return 0;
        }
        if (p[0].first > right){
            r = divup(xsum - 3 * area * right, 6 * (right - p[0].first));
        }
        if (xsum < 3 * area * left) {
            l = divdown(xsum - 3 * area * left, 6 * (left - p[0].first));
        }
    }
    if (r == -1){
        printf("%lld .. inf\n", l);
    }
    else {
        printf("%lld .. %lld\n", l, r);
    }
    return 0;
}

/*
7
-50 50
-0 50
-0 0
-30 0
-30 30
-40 40
-50 40

7
-50 50
-0 50
-0 0
-10 0
-10 30
-20 40
-50 40
 */