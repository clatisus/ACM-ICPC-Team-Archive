namespace zxa {
const int max_N = 23333;
int n;
std::vector<int> vec[max_N];
int S[max_N], Q[max_N], *Top, idx;
int f[max_N], pre[max_N], nxt[max_N], vis[max_N];
void add_edge(int u, int v) {
  vec[u].push_back(v);
  vec[v].push_back(u);
}
int find(int x) {
  return x == f[x] ? x : f[x] = find(f[x]);
}
int lca(int x, int y) {
  ++idx;
  x = find(x);
  y = find(y);
  while (true) {
    if (x) {
      if (vis[x] == idx) return x;
      vis[x] = idx;
      x = find(pre[nxt[x]]);
    }
    std::swap(x, y);
  }
}
void blossom(int x, int y, int z) {
  while (find(x) != z) {
    pre[x] = y;
    if (S[nxt[x]] == 1) {
      S[*++Top = nxt[x]] = 0;
    }
    f[x] = f[nxt[x]] = z;
    y = nxt[x];
    x = pre[y];
  }
}
void match(int x) {
  for (int i = 1; i <= n; ++i) f[i] = i;
  memset(S, -1, sizeof(S));
  memset(Q, 0, sizeof(Q));
  S[*(Top = Q + 1) = x] = 0;
  for (int *i = Q + 1; *i; ++i) {
    for (auto &g : vec[*i]) {
      if (S[g] == -1) {
        pre[g] = *i, S[g] = 1;
        if (!nxt[g]) {
          int u = g, v = *i, lst;
          while (v) {
            lst = nxt[v], nxt[v] = u, nxt[u] = v;
            v = pre[u = lst];
          }
          return;
        }
        S[*++Top = nxt[g]] = 0;
      } else if (!S[g] && find(g) != find(*i)) {
        int z = lca(g, *i);
        blossom(g, *i, z);
        blossom(*i, g, z);
      }
    }
  }
}
void solve() {
  memset(nxt, 0, sizeof(nxt));
  memset(pre, 0, sizeof(pre));
  for (int i = 1; i <= n; ++i) {
    if (nxt[i]) continue;
    match(i);
  }
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    if (nxt[i]) ++ans;
  ans >>= 1;
  printf("%d\n", ans);
  for (int i = 1; i <= n; ++i) {
    printf("%d%c", nxt[i], " \n"[i == n]);
  }
}
}