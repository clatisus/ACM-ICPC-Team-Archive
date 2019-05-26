#include <bits/stdc++.h>

using ll = long long;

int r, c;
int dp[1 << 20][23];
int cost[23][23];
int a[23][23];
std::bitset<1 << 20> vis;
//int vis[1 << 20], wjj;

bool check(std::vector<int> &vec, int j) {
    if (vec.size() <= 2) return true;
    for (int k = 2, sz = (int)vec.size(); k < sz; ++k) {
        if ((a[vec[k]][j] - a[vec[k - 1]][j]) * (a[vec[1]][j] - a[vec[0]][j]) < 0) {
            return false;
        }
    }
    return true;
}

int main() {
    scanf("%d%d", &r, &c);
    //auto t = clock();
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            scanf("%d", a[i] + j);
            //a[i][j] = i * c + j + 1;
        }
    }

    for (int i = 1; i < c; ++i) {
        for (int j = 0; j < i; ++j) {
            for (int k = 0; k < r; ++k) {
                cost[i][j] |= (1 << k) * (a[k][i] > a[k][j]);
            }
        }
    }

    ll ans = 0;
    for (int s = 1; s < (1 << r); ++s) {
        std::vector<int> vec;

        std::vector<int> pos;
        for (int j = 0; j < r; ++j) {
            if ((s >> j) & 1) {
                pos.push_back(j);
            }
        }
        for (int j = 0; j < c; ++j) {
            if (check(pos, j)) {
                vec.push_back(j);
            }
        }
        if (vec.empty()) continue;

        int n = (int) vec.size();
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                // j < i
                int c = cost[vec[i]][vec[j]] & s;
                dp[c][i] = 1;
                dp[c][j] = 1;
            }
        }

        ans += n;
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                int c = cost[vec[i]][vec[j]] & s;
                dp[c][i] += dp[c][j];
                ans += dp[c][j];
            }
        }
        //printf("ans = %d\n", ans);
    }
    printf("%lld\n", ans);
    //printf("%.10f\n", 1.0 * (clock() - t) / CLOCKS_PER_SEC);
    return 0;
}
/*
3 3
 1 2 5
 7 6 4
 9 8 3

 4 3
 8 2 5
 12 9 6
 3 1 10
 11 7 4
 */