#include <bits/stdc++.h>

const int N = 10010;
const double eps = 1e-9;
typedef std::pair <double, int> pdi;
typedef long long ll;

inline int sig(double p){return (p > eps) - (p < -eps);}

ll dp[N];
char s[N];
pdi p[N];

struct item{
    bool type;
    int w, t, dt;

    void read(){
        scanf("%s", s);
        if (s[0] == 'C'){
            type = false;
            w = 0;
            scanf("%d%d", &t, &dt);
        }
        else{
            type = true;
            scanf("%d%d%d", &w, &t, &dt);
        }
    }
};

item it[N];
std::priority_queue <int> queue[N];

int main(){
    bool hasc = false;
    int d, w;
    scanf("%d%d", &d, &w);
    for (int i = 0; i < d; ++ i){
        it[i].read();
    }
    for (int i = 0; i < d; ++ i){
        item item1 = it[i];
        if (!item1.type){
            hasc = true;
            continue;
        }
        for (int j = 0; j < w; ++ j){
            queue[item1.w].push(-(item1.t - j * item1.dt));
            if (queue[item1.w].size() > w / item1.w){
                queue[item1.w].pop();
            }
        }
    }
    for (int i = 0; i < N; ++ i){
        dp[i] = LLONG_MIN;
    }
    dp[0] = 0;
    for (int i = 1; i <= w; ++ i){
        while (!queue[i].empty()){
            int u = -queue[i].top();
            queue[i].pop();
            for (int j = w - i; j >= 0; -- j){
                if (dp[j] == LLONG_MIN) continue;
                dp[j + i] = std::max(dp[j + i], dp[j] + u);
            }
        }
    }
    if (!hasc){
        if (dp[w] == LLONG_MIN) {
            puts("impossible");
        }
        else{
            printf("%lld\n", dp[w]);
        }
        return 0;
    }
    int dcnt = 0;
    for (int i = 0; i < d; ++ i){
        if (!it[i].type){
            p[dcnt ++] = {it[i].t, it[i].dt};
        }
    }
    std::sort(p, p + dcnt, std::greater <pdi>());
    double dsum = 0;
    double ans = -1e100, dans = 0;
    for (int i = w; i >= 0; -- i){
        if (dp[i] == LLONG_MIN){
            continue;
        }
        while (sig(dsum + i - w) < 0){
            int sit = 1;
            while (sit < dcnt){
                if (sig(p[sit].first - p[0].first) < 0){
                    break;
                }
                ++ sit;
            }
            bool flag = true;
            double sum = 0;
            for (int j = 0; j < sit; ++ j){
                if (!p[j].second){
                    double weight = w - (dsum + i);
                    dans += weight * p[j].first;
                    dsum += weight;
                    flag = false;
                    break;
                }
                sum += 1.0 / p[j].second;
            }
            if (flag){
                double limit = (w - (dsum + i)) / sum;
                if (sit < dcnt){
                    limit = std::min(limit, p[0].first - p[sit].first);
                }
                for (int j = 0; j < sit; ++ j){
                    double weight = limit / p[j].second;
                    dans += weight * p[j].first - 0.5 * weight * weight * p[j].second;
                    p[j].first -= limit;
                    dsum += weight;
                }
            }
        }
        ans = std::max(ans, dp[i] + dans);
    }
    printf("%.9f\n", ans);
    return 0;
}
