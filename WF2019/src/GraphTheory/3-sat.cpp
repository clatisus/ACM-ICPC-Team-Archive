/* press init -1, found init false
 * x and !x should be re-indexed to 2x+1 and 2x
 * &(W[0][u] | W[1][u] | W[2][u]) where u in [0, C)
 */
int C, W[3][MAXN], press[26];
bool found;
bool sat(int h) { return press[h >> 1] == (h & 1); }
void dfs(int u) {
	while (u < C && (sat(W[0][u]) || sat(W[1][u]) || sat(W[2][u]))) ++u;
	if (u == C) {
		found = true;
		return;
	}
	int tmp[3];
	for (int i = 0; i < 3; ++i) tmp[i] = press[W[i][u] >> 1];
	for (int i = 0; i < 3; ++i)
		if (press[W[i][u] >> 1] == -1) {
			press[W[i][u] >> 1] = W[i][u] & 1;
			dfs(u + 1);
			if (found) return;
			press[W[i][u] >> 1] = 1 - press[W[i][u] >> 1];
		} else if (sat(W[i][u])) {
			dfs(u + 1);
			if (found) return;
		}
	for (int i = 0; i < 3; ++i) press[W[i][u] >> 1] = tmp[i];
}
