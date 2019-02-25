#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

typedef long long ll;
const int N = 5010;

int s[N];

void solve(){
    int n, sigma;
    ll k;
    scanf("%d%d%lld", &n, &sigma, &k);
    for (int i = 0; i < n; ++ i){
        scanf("%d", &s[i]);
    }
    std::vector <std::vector <int>> vec;
    for (int i = 1; i < 1 << n; ++ i){
        std::vector <int> vvec;
        for (int j = 0; j < n; ++ j){
            if (i >> j & 1){
                vvec.push_back(s[j]);
            }
        }
        vec.push_back(vvec);
    }
    std::sort(vec.begin(), vec.end());
    std::vector <int> output = vec[k - 1];
    for (int i = 0, sz = output.size(); i < sz; ++ i){
        printf("%d%c", output[i], " \n"[i == sz - 1]);
    }
}

int main() {
    int test;
    scanf("%d", &test);
    while (test --){
        solve();
    }
    return 0;
}
