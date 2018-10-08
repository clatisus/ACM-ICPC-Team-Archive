#include<bits/stdc++.h>

const int N = 50010;
typedef std::pair <int, int> pii;

int a[N], b[N];
pii p[N];
int left[N], right[N];

double value(pii p){
    return std::log(2) * p.first + std::log(3) * p.second;
}

void max(pii &p1, pii p2){
    if (value(p1) < value(p2)){
        p1 = p2;
    }
}

pii solve(pii *p, int n){
    std::sort(p, p + n);
    left[0] = INT_MAX;
    for (int i = 0; i < n; ++ i){
        left[i + 1] = std::min(left[i], p[i].second);
    }
    right[n] = INT_MIN;
    for (int i = n - 1; i >= 0; -- i){
        right[i] = std::max(right[i + 1], p[i].second);
    }
    pii ans = {INT_MIN, INT_MIN};
    for (int i = 0; i < n; ++ i){
        max(ans, {p[i].first, std::max(left[i] == INT_MAX ? INT_MIN : left[i], right[i])});
    }
    return ans;
}

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
        scanf("%d%d", &a[i], &b[i]);
        p[i] = {a[i], b[i]};
    }
    pii ans1 = solve(p, n);
    for (int i = 0; i < n; ++ i){
        p[i] = {-p[i].first, -p[i].second};
    }
    pii ans2 = solve(p, n);
    int maxa = 0, maxb = 0, mina = INT_MAX, minb = INT_MAX;
    for (int i = 0; i < n; ++ i){
        maxa = std::max(maxa, a[i]);
        maxb = std::max(maxb, b[i]);
        mina = std::min(mina, a[i]);
        minb = std::min(minb, b[i]);
    }
    for (int i = 0; i < n; ++ i){
        if (i == n - 1){
            printf("%d %d ", mina, minb);
        }
        else if (i == n - 2){
            printf("%d %d ", ans1.first, ans1.second);
        }
        else{
            printf("%d %d ", maxa, maxb);
        }
        if (i == 0){
            printf("%d %d\n", maxa, maxb);
        }
        else if (i == 1){
            printf("%d %d\n", -ans2.first, -ans2.second);
        }
        else{
            printf("%d %d\n", mina, minb);
        }
    }
    return 0;
}

