#include <bits/stdc++.h>

const int N = 5010;
typedef std::pair <int, int> pii;

std::vector <pii> vec[N];
int a[N], sit[N];

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
        scanf("%d", &a[i]);
    }
    std::sort(a, a + n);
    int ans = 2;
    for (int i = n - 2; i >= 0; -- i){
        for (int j = i + 1; j < n; ++ j){
            int diff = a[j] - a[i];
            while (sit[j] < vec[j].size() && diff > vec[j][sit[j]].first){
                ++ sit[j];
            }
            int x = sit[j] < vec[j].size() && vec[j][sit[j]].first == diff ? vec[j][sit[j]].second + 1 : 2;
            ans = std::max(ans, x);
            vec[i].push_back({diff, x});
        }
    }
    printf("%d\n", ans);
    return 0;
}
