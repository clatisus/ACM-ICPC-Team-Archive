#include <bits/stdc++.h>

const int N = 100010;

int a[N];
int cnt[N];
int x[N];
std::vector <int> vec[N];

int calcup(int a, int sum, int now){
    return (1ll * now * sum + a - 1) / a;
}

int calcdown(int a, int sum, int now){
    return (1ll * now * sum - sum + 1 + a - 1) / a;
}

int main(){
    int m, n;
    scanf("%d%d", &m, &n);
    int sum = 0;
    for (int i = 0; i < m; ++ i){
        scanf("%d", &a[i]);
        sum += a[i];
    }
    for (int i = 0; i < n; ++ i) {
        scanf("%d", &x[i]);
    }
    if (n % sum == 0){
        puts("forever");
        return 0;
    }
    int newn = n % sum;
    for (int i = 0; i < newn; ++ i){
        x[i] = x[i + n - newn];
    }
    n = newn;
    for (int i = 0; i < n; ++ i){
        -- x[i];
        ++ cnt[x[i]];
    }
    if (m == 1){
        puts("forever");
        return 0;
    }
    for (int i = 0; i < m; ++ i){
        for (int j = cnt[i] + 1; j <= a[i]; ++ j) {
            int l = std::max(n + 1, calcdown(a[i], sum, j));
            int r = calcup(a[i], sum, j);
            if (r <= n){
                puts("0");
                return 0;
            }
            vec[l].push_back(r);
        }
    }
    std::priority_queue <int, std::vector <int>, std::greater <int>> pq;
    int beginn = n;
    for (int i = n + 1; i <= sum; ++ i){
        for (auto u : vec[i]){
            pq.push(u);
        }
        if (pq.empty()){
            printf("%d\n", n - beginn);
            return 0;
        }
        pq.pop();
        if (!pq.empty() && pq.top() == i){
            printf("%d\n", n - beginn);
            return 0;
        }
        ++ n;
    }
    puts("forever");
    return 0;
}
