/**
 * Author: Shinrii Tin
 * Description: Divide and Conquer a tree.
 * Time: $O(Cost(N)\log{N})$
 */
namespace centroid {
	const int max_N = (int) 2e5 + 21;
	int p[max_N], sz[max_N], mx[max_N];
	bool vis[max_N];
	std::vector<int> vec[max_N];
	inline int find(int u) {
		static int Q[max_N], tot;
		Q[tot = 1] = u, p[u] = 0;
		for (int i = 1; i <= tot; ++i) {
			u = Q[i];
			sz[u] = 1, mx[u] = 0;
			for (auto v : vec[u]) {
				if (vis[v] || v == p[u]) continue;
				p[Q[++tot] = v] = u;
			}
		}
		for (int i = tot; i; --i) {
			u = Q[i];
			mx[u] = std::max(mx[u], tot - sz[u]);
			if (mx[u] * 2 <= tot) return u;
			sz[p[u]] += sz[u];
			mx[p[u]] = std::max(mx[p[u]], sz[u]);
		}
		return 0;
	}
	void solve(int u) {
		u = find(u);
		//do something with time Cost(siz[u])
		vis[u] = true;
		for (auto v : vec[u]) if (!vis[v]) solve(v);
	}
	void init(int n) {
		memset(vis + 1, 0, n * sizeof(bool));
		for (int i = 1; i <= n; ++i) {
			std::vector<int>().swap(vec[i]);
		}
	}
};