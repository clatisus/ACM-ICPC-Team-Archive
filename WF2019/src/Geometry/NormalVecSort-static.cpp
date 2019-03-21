struct P {
	int x, y;
} p[max_N], v[max_N][max_N];
int n, Q[max_N], rk[max_N];
LL S;
std::vector<PII> vec;
LL area(int i, int j, int k) { return p[i].sub(p[k]).det(p[j].sub(p[k])); }
struct functor {
	inline bool operator()(const PII &a, const PII &b) const {
		return v[a.first][a.second].det(v[b.first][b.second]) > 0;
	}
};
void binarySearch(int u, int v) {
	int lo = 1, hi = n;
	while (lo <= hi) {
		int mi = (lo + hi) >> 1;
		LL s = area(u, v, Q[mi]);
		if (s == S) {
			puts("Yes");
			printf("%d %d\n", p[u].x, p[u].y);
			printf("%d %d\n", p[v].x, p[v].y);
			printf("%d %d\n", p[Q[mi]].x, p[Q[mi]].y);
			exit(0);
		}
		if (s < S) lo = mi + 1;
		else hi = mi - 1;
	}
}
void solve() {
	std::sort(p + 1, p + 1 + n, [&](P a, P b) { return a.y == b.y ? a.x < b.x : a.y < b.y; });
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j) {
			v[i][j] = p[j].sub(p[i]);
			vec.push_back({i, j});
		}
	std::sort(ALL(vec), functor());
	for (int i = 1; i <= n; ++i) Q[i] = rk[i] = i;
	for (int i = 1; i <= n; ++i) rk[Q[i]] = i;
	for (int i = 0, sz = int(vec.size()); i < sz; ++i) {
		int u = vec[i].first, v = vec[i].second;
		binarySearch(u, v);
		binarySearch(v, u);
		std::swap(Q[rk[u]], Q[rk[v]]);
		std::swap(rk[u], rk[v]);
	}
	puts("No");
}
