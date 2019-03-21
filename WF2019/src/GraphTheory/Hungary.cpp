// O(VE)
namespace Hungary {
	int n;
	// edge only from left to right
	// vec[left].push_back(right)
	std::vector<int> vec[MAXN], left;
	int match[MAXN];
	bool check[MAXN];
	bool dfs(int u) {
		for (auto v : vec[u])
			if (!check[v]) {
				check[v] = true;
				if (match[v] == -1 || dfs(match[v])) {
					match[v] = u;
					match[u] = v;
					return true;
				}
			}
		return false;
	}
	int hungary() {
		memset(match, -1, sizeof(match));
		int ret = 0;
		for (auto u : left)
			if (match[u] == -1) {
				memset(check, 0, sizeof(check));
				if (dfs(u)) ++ret;
			}
		return ret;
	}
}
