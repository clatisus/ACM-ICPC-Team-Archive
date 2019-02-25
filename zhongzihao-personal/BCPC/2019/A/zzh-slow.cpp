#include <cstdio>
#include <vector>

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
        std::vector <pii> vec1, vec2;
        while (x > 1){
            int tmp = min[x], cnt = 0;
            while (x % tmp == 0){
                x /= tmp;
                ++ cnt;
            }
            vec1.push_back({tmp, cnt});
        }
        x = i + 1;
        while (x > 1){
            int tmp = min[x], cnt = 0;
            while (x % tmp == 0){
                x /= tmp;
                ++ cnt;
            }
            vec2.push_back({tmp, cnt * i});
        }
        for (int j = 0, k = 0; j < vec1.size() || k < vec2.size(); ){
            if (j < vec1.size() && k < vec2.size() && vec1[j].first == vec2[k].first){
                ans[i] = 1ll * ans[i] * (vec1[j].second + vec2[k].second + 1) % moder;
                ++ j, ++ k;
            }
            else if (k < vec2.size() && (j == vec1.size() || vec1[j].first > vec2[k].first)){
                ans[i] = 1ll * ans[i] * (vec2[k].second + 1) % moder;
                ++ k;
            }
            else{
                ans[i] = 1ll * ans[i] * (vec1[j].second + 1) % moder;
                ++ j;
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

