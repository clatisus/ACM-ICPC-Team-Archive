#include<bits/stdc++.h>

const int N = 5010;
typedef long long ll;

typedef std::pair <int, int> pii;
typedef std::pair <int, pii> piii;
std::vector <piii> e[N];
ll max[N], min[N];
int cnt[N];
bool inque[N];

void solve(){
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; ++ i){
        e[i].clear();
    }
    for (int i = 0, u, v, a, b; i < m; ++ i){
        scanf("%d%d%d%d", &u, &v, &a, &b);
        e[u].push_back({v, {a, b}});
    }
    std::queue <int> queue;
    for (int i = 1; i <= n; ++ i){
        max[i] = LLONG_MIN;
        min[i] = LLONG_MAX;
    }
    memset(inque, 0, sizeof(inque));
    memset(cnt, 0,sizeof(cnt));
    max[1] = min[1] = 0;
    queue.push(1);
    inque[1] = true;
    cnt[1] = 1;
    int maxcnt = (int) std::max(10.0, n * 1.5);
    int cntn = 0;
    while (!queue.empty()){
        int u = queue.front();
        queue.pop();
        inque[u] = false;
        for (auto w : e[u]){
            int v = w.first;
            int a = w.second.first;
            int b = w.second.second;
            ll tmp1 = a * max[u] + b;
            ll tmp2 = a * min[u] + b;
            ll maxtmp = std::max(tmp1, tmp2);
            ll mintmp = std::min(tmp1, tmp2);
            if (max[v] < maxtmp || min[v] > mintmp){
                if (v == n && max[n] < maxtmp){
                    ++ cntn;
                }
                max[v] = std::max(max[v], maxtmp);
                min[v] = std::min(min[v], mintmp);
                if (!inque[v]){
                    ++ cnt[v];
                    if (cnt[v] >= maxcnt){
                        if (max[n] == LLONG_MIN){
                            puts("No solution");
                        }
                        else if (cntn >= n * 1.3){
                            puts("Infinity");
                        }
                        else{
                            printf("%lld\n", max[n]);
                        }
                        return;
                    }
                    queue.push(v);
                    inque[v] = true;
                }
            }
        }
    }
    if (max[n] == LLONG_MIN){
        puts("No solution");
    }
    else{
        printf("%lld\n", max[n]);
    }
}

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        solve();
    }
    return 0;
}
