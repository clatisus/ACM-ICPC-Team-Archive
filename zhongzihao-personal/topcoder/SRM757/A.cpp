#include <bits/stdc++.h>

typedef std::pair<int, int> pii;

class CentipedeSocks {
public:
    int fewestSocks(int C, int F, std::vector<int> sockCounts) {
        int n = sockCounts.size();
        std::vector<int> now(n);
        std::priority_queue<pii> queue;
        int ans = 0, tot = 0;
        for (int i = 0; i < n; ++i) {
            tot += sockCounts[i];
            now[i] = std::min(F - 1, sockCounts[i]);
            ans += now[i];
            int next = std::min(now[i] + F, sockCounts[i]);
            queue.push({next - now[i], i});
            now[i] = next;
        }
        int cnt = 0;
        while (cnt < C - 1) {
            pii p = queue.top();
            queue.pop();
            ans += p.first;
            ++cnt;
            int i = p.second;
            int next = std::min(now[i] + F, sockCounts[i]);
            queue.push({next - now[i], i});
            now[i] = next;
        }
        if (ans == tot) {
            return -1;
        }
        return ans + 1;
    }
};

int main() {
    CentipedeSocks c;
    printf("%d\n", c.fewestSocks(21, 3,
                                 {2, 3, 4, 2, 2, 4, 2, 2, 1, 2, 5, 3, 5, 4, 1, 3, 4, 1, 1, 4, 1, 3, 1, 3, 1, 2, 2, 5, 4,
                                  2, 4, 5, 4, 5, 5, 1, 1}));
    return 0;
}
