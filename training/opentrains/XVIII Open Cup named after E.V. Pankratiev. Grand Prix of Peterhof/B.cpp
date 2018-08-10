#include <bits/stdc++.h>

const int mod = (int) 1e9 + 7;

using ull = unsigned long long;
using map = std::unordered_map<ull, int>;

int n, m, cur, maxs, ans;

map dp[2][1 << 6];

inline void add(int &x, int a) { if ((x += a) >= mod) x -= mod;	}

void trans(ull mask, int col_mask, int cur_col, int pos, int pre, map &dp) {
	if (!pre) return;
	ull res = 0;
	for (int s = 0; s < maxs; ++s) {
		if (!((mask >> s) & 1)) continue;
		if ((s >> pos) & 1) { //if this pos in last row is not filled
			if (cur_col == ((col_mask >> pos) & 1)) continue; //ilegal when putting a domino in grids of same color
			res |= 1ull << (s ^ (1 << pos));
		} else { //if this pos in last row is filled
			res |= 1ull << (s | (1 << pos)); //leave this pos unfilled
			if (pos && ((s >> (pos - 1)) & 1) && cur_col != ((col_mask >> (pos - 1)) & 1)) {
				res |= 1ull << (s ^ (1 << (pos - 1))); //try to fill this pos with prev pos in the same row
			}
		}
	}
	if (res) add(dp[res], pre);
}

int main() {
	scanf("%d%d", &n, &m);
	maxs = (1 << n);
	dp[cur = 0][0][1] = 1;
	for (int i = 1; i <= m; ++i) {
		for (int j = 0; j < n; ++j) {
			cur ^= 1;
			for (int s = 0; s < maxs; ++s) dp[cur][s].clear();
			for (int s = 0; s < maxs; ++s) {
				for (auto pr : dp[cur ^ 1][s]) {
					trans(pr.first, s, 1, j, pr.second, dp[cur][s | (1 << j)]);
					trans(pr.first, s, 0, j, pr.second, dp[cur][s & ~(1 << j)]);
				}
			}
		}
	}
	for (int s = 0; s < maxs; ++s) {
		for (auto pr : dp[cur][s]) { //count all col_mask that can reach mask 0
			if (pr.first & 1) add(ans, pr.second);
		}
	}
	printf("%d\n", ans);
	return 0;
}
