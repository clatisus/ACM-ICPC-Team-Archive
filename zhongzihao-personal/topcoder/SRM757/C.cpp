#include <bits/stdc++.h>

class Consensus {
public:
    double expectedTime(std::vector<int> opinions) {
        int n = opinions.size();
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += opinions[i];
        }
        double ans = 1.0 * (sum - 1) * (sum - 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j < opinions[i]; ++j) {
                ans -= 1.0 * (sum - 1) * (opinions[i] - j) / (sum - j);
            }
        }
        return ans;
    }
};
