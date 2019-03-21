namespace KM {
	int n, w[MAXN][MAXN];
	int slack[MAXN], lv[MAXN], rv[MAXN], pre[MAXN], mat[MAXN];
	bool vis[MAXN];
	void aug(int s) {
		for (int i = 0; i <= n; ++i) {
			slack[i] = INT_MAX;
			vis[i] = false;
			pre[i] = 0;
		}
		int u = 0; mat[u] = s;
		do {
			int now = mat[u], d = INT_MAX, nxt;
			vis[u] = true;
			for (int v = 1; v <= n; ++v)
				if (!vis[v]) {
					if (lv[now] + rv[v] - w[now][v] < slack[v]) {
						slack[v] = lv[now] + rv[v] - w[now][v];
						pre[v] = u;
					}
					if (d > slack[v]) {
						d = slack[v];
						nxt = v;
					}
				}
			for (int i = 0; i <= n; ++i)
				if (vis[i]) lv[mat[i]] -= d, rv[i] += d;
				else slack[i] -= d;
			u = nxt;
		} while (mat[u]);
		while (u) mat[u] = mat[pre[u]], u = pre[u];
	}
	void solve() {
		for (int i = 1; i <= n; ++i) {
			lv[i] = INT_MIN;
			rv[i] = 0;
			mat[i] = 0;
			for (int j = 1; j <= n; ++j)
				lv[i] = std::max(lv[i], w[i][j]);
		}
		for (int i = 1; i <= n; ++i) aug(i);
	}
}
