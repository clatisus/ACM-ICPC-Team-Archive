#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 10000010;
const int moder = 998244353;

int min[N], ans[N];
std::vector <int> prime;

int main(){
    for (int i = 2; i < N; ++ i){
        if (!min[i]){
            min[i] = i;
            prime.push_back(i);
        }
        for (auto u : prime){
            int x = i * u;
            if (x >= N) break;
            min[x] = u;
            if (i % u == 0) break;
        }
    }
    for (int i = 1; i < N - 1; ++ i){
        ans[i] = 1;
        int x = i;
        typedef std::pair <int, int> pii;
        std::vector <pii> vec;
        while (x > 1){
            int tmp = min[x], cnt = 0;
            while (x % tmp == 0){
                x /= tmp;
                ++ cnt;
            }
            vec.push_back({tmp, cnt});
        }
        x = i + 1;
        while (x > 1){
            int tmp = min[x], cnt = 0;
            while (x % tmp == 0){
                x /= tmp;
                ++ cnt;
            }
            vec.push_back({tmp, cnt * i});
        }
        std::sort(vec.begin(), vec.end());
        int sum = 0, sz = vec.size();
        for (int j = 0; j < sz; ++ j){
            sum += vec[j].second;
            if (j == sz - 1 || vec[j].first != vec[j + 1].first){
                ans[i] = 1ll * ans[i] * (sum + 1) % moder;
                sum = 0;
            }
        }
        ans[i] += ans[i - 1];
        ans[i] -= ans[i] >= moder ? moder : 0;
    }
    int test;
    scanf("%d", &test);
    for (int i = 1; i <= test; ++ i){
        int x;
        scanf("%d", &x);
        printf("%d\n", ans[x]);
    }
    return 0;
}

