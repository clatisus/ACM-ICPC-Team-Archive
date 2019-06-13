#include <bits/stdc++.h>

typedef std::vector<int>::iterator it;
const int N = 100;

std::string ans;
int num[N];
std::vector<int> digits;
char s[N];

void dfs(it now, it end, int cnt, int sum) {
    if (now == end) {
        if (sum != 2 * cnt) {
            return;
        }
        std::vector<std::string> vec;
        for (int i = 0; i < cnt; ++i) {
            s[0] = num[i] + '0';
            s[1] = digits[i] + '0';
            vec.push_back(s);
        }
        std::sort(vec.begin(), vec.end());
        std::string tmp;
        for (auto &u : vec) {
            tmp += u;
        }
        for (int i = 0; i < cnt; ++i) {
            int ccnt = 0;
            for (auto &u : tmp) {
                ccnt += u == tmp[2 * i + 1];
            }
            if (ccnt != tmp[2 * i] - '0') {
                return;
            }
        }
        if (ans.empty()) {
            ans = tmp;
        } else {
            ans = std::min(ans, tmp);
        }
        return;
    }
    if (sum > 20) {
        return;
    }
    for (int i = 1; i <= 9; ++i) {
        num[cnt] = i;
        auto u = now;
        dfs(++u, end, cnt + 1, sum + i);
    }
}

class SelfDescFind {
public:
    std::string construct(std::vector<int> digits) {
        ::digits = digits;
        dfs(digits.begin(), digits.end(), 0, 0);
        return ans;
    }
};
