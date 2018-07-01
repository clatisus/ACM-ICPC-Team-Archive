#include<bits/stdc++.h>

const int N = 10010;
typedef std::pair <int, int> pii;

pii p[N];

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        int n, x;
        scanf("%d%d", &n, &x);
        for (int i = 0; i < n; ++ i){
            scanf("%d", &p[i].first);
        }
        for (int i = 0; i < n; ++ i){
            scanf("%d", &p[i].second);
        }
        std::sort(p, p + n, [](pii p1, pii p2){
            return (p1.first - 1) * p2.second > (p2.first - 1) * p1.second;
        });
        int ans = x % 10;
        for (int i = n - 1; i >= 0; -- i){
           ans = (ans * p[i].first + p[i].second) % 10;
        }
        printf("%d\n", ans);
    }
    return 0;
}
