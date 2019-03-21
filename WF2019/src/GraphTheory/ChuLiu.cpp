namespace ChuLiu {
	const int max_N = 1000 + 21;
	const int max_M = (int) 2e4 + 21;
	using LL = long long;
	const LL inf = (int) 1e9;
	LL val[max_M], tag[max_M];
	int n, m, u[max_M], v[max_M], ls[max_M], rs[max_M];
	int st[max_N], top, rt[max_N];
	struct dsu {
		int f[max_N];
		int find(int x) {
			return x == f[x] ? x : f[x] = find(f[x]);
		}
		void merge(int x, int y) {
			f[find(x)] = find(y);
		}
		bool check(int x, int y) {
			return find(x) == find(y);
		}
	} F[2];
	inline void down(int x) {
		if (tag[x]) {
			val[x] += tag[x];
			tag[ls[x]] += tag[x];
			tag[rs[x]] += tag[x];
			tag[x] = 0;
		}
	}
	int merge(int x, int y) {
		down(x), down(y);
		if (!x || !y)
			return x + y;
		if (val[x] > val[y]) {
			std::swap(x, y);
		}
		rs[x] = merge(rs[x], y);
		std::swap(ls[x], rs[x]);
		return x;
	}
	void solve() {
		scanf("%d%d", &n, &m);
		for (int i = 0; i <= n; ++i) {
			rt[i] = 0;
			F[0].f[i] = F[1].f[i] = i;
		}
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d%lld", u + i, v + i, val + i);
			val[i] *= 1000;
			tag[i] = ls[i] = rs[i] = 0;
			rt[v[i]] = merge(rt[v[i]], i);
		}
		for (int i = 0; i < n; ++i) {
			int id = i + m + 1;
			val[id] = inf * 1000 + i;
			tag[id] = ls[id] = rs[id] = 0;
			u[id] = n, v[id] = i;
			rt[i] = merge(rt[i], id);
		}
		LL ans = 0;
		int root = n;
		for (int i = 0; i < n; ++i) {
			if (F[1].f[i] != i) continue;
			st[top = 1] = i;
			while (!F[0].check(st[top], root)) {
				int x = st[top], y;
				LL w;
				do {
					y = F[1].find(u[rt[x]]);
					w = val[rt[x]];
					rt[x] = merge(ls[rt[x]], rs[rt[x]]);
				} while (x == y);
				ans += w;
				tag[rt[x]] -= w;
				if (F[0].check(x, y)) {
					while (st[top] != y) {
						x = st[top--];
						rt[y] = merge(rt[x], rt[y]);
						F[1].merge(x, y);
					}
				} else {
					F[0].merge(x, y);
					st[++top] = y;
				}
			}
		}
		if (ans > 2 * inf * 1000) {
			puts("impossible");
		} else {
			LL ans1 = ans / 1000 - inf;
			LL ans2 = ans % 1000;
			printf("%lld %lld\n", ans1, ans2);
		}
		puts("");
	}
}