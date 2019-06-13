#include <bits/stdc++.h>

const int N = 60;
const int moder = (int) 1e9 + 7;

std::vector<int> vec[N];
int comb[N][N];
int dp[N];

class LollipopHoney {
public:
    std::vector<int> count(int K, std::vector<int> flavor, std::vector<int> deliciousness) {
        for (int i = 0; i < N; ++i) {
            comb[i][0] = 1;
            for (int j = 1; j <= i; ++j) {
                comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % moder;
            }
        }
        int n = flavor.size();
        for (int i = 0; i < n; ++i) {
            vec[flavor[i]].push_back(deliciousness[i]);
        }
        std::vector<int> last;
        for (int i = 0; i < N; ++i) {
            std::sort(vec[i].begin(), vec[i].end(), std::greater<int>());
            for (int j = 0, sz = vec[i].size(); j < sz && j < K; ++j) {
                last.push_back(vec[i][j]);
            }
        }
        if ((int) last.size() < 2 * K) {
            return {};
        }
        std::sort(last.begin(), last.end(), std::greater<int>());
        std::vector<int> ans(2);
        std::set<int> set;
        int min = INT_MAX;
        for (int i = 0; i < 2 * K; ++i) {
            ans[0] += last[i];
            set.insert(last[i]);
            min = last[i];
        }
        ans[1] = 1;
        for (auto u : set) {
            int cnt2 = 0;
            for (int i = 0; i < 2 * K; ++i) {
                cnt2 += last[i] == u;
            }
            if (u > min) {
                for (int i = 0; i < N; ++i) {
                    int cnt = 0;
                    for (auto v : vec[i]) {
                        cnt += v == u;
                    }
                    ans[1] = 1ll * ans[1] * comb[cnt][std::min(cnt, K)] % moder;
                }
                continue;
            }
            memset(dp, 0, sizeof(dp));
            dp[0] = 1;
            for (int i = 0; i < N; ++i) {
                int cnt = 0;
                for (auto v : vec[i]) {
                    cnt += v == u;
                }
                int max = K;
                for (auto v : vec[i]) {
                    max -= v > min;
                }
                for (int j = N - 1; j >= 0; --j) {
                    for (int k = 1; k <= max && j + k < N; ++k) {
                        dp[j + k] = (dp[j + k] + 1ll * dp[j] * comb[cnt][k]) % moder;
                    }
                }
            }
            ans[1] = 1ll * ans[1] * dp[cnt2] % moder;
        }
        return ans;
    }
};
