#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cassert>
#include <cstdio>
#include <queue>
#include <set>
#include <map>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>
#include <numeric>

#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define for1(i, n) for (int i = 1; i <= (int)(n); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define fore(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)

using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long i64;
typedef vector<i64> vi64;
typedef vector<vi64> vvi64;

template<class T>
bool uin(T &a, T b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

template<class T>
bool uax(T &a, T b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

const int MAXN = 110000;
int l[MAXN], r[MAXN];
const int MAXT = 2000000;
int vis[MAXT], comp[MAXT];
vi e[MAXT], re[MAXT];

void addEdge(int v, int u) {
    e[v].pb(u);
    e[u ^ 1].pb(v ^ 1);
    re[u].pb(v);
    re[v ^ 1].pb(u ^ 1);
}

vi ord;

void dfs_ord(int v) {
    if (vis[v]) return;
    vis[v] = 1;
    for (int u: e[v]) dfs_ord(u);
    ord.pb(v);
}

void dfs_mark(int v, int c) {
    if (vis[v]) return;
    vis[v] = 1;
    comp[v] = c;
    for (int u: re[v]) dfs_mark(u, c);
}

int val(int v) {
    return comp[v] > comp[v + 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);
    cout << fixed;
#ifdef LOCAL_DEFINE
    freopen("input.txt", "rt", stdin);
#endif

    int t, T;
    cin >> t >> T;
    int N, M;
    cin >> N >> M;
    forn(i, N) cin >> l[i] >> r[i];
    vector<pii> conf(M);
    forn(i, M) {
        cin >> conf[i].fi >> conf[i].se;
        --conf[i].fi; --conf[i].se;
    }

    bool ok = true;

    vi v;
    v.pb(0);
    v.pb(t);
    v.pb(T);
    forn(i, N) {
        v.pb(l[i]);
        if (l[i] <= t) v.pb(t - l[i]);
        v.pb(r[i]);
        if (r[i] <= t) v.pb(t - r[i]);
    }
    sort(all(v));
    v.erase(unique(all(v)), v.end());
    while (v.back() > T) v.pop_back();
//    for (int u: v) cerr << u << ' ';
//    cerr << '\n';
    int K = v.size();
    int off1 = 0, off2 = 2 * K, off3 = 4 * K;
    int V = off3 + 2 * N;
    assert(V <= MAXT);
    int j = K - 1;
    forn(i, K - 1) {
        addEdge(off1 + 2 * i, off1 + 2 * (i + 1));
        addEdge(off2 + 2 * i, off2 + 2 * (i + 1));
    }
    forn(i, K - 1) {
        while (j >= 0 && v[i + 1] + v[j] > T) --j;
        if (j < 0) break;
        addEdge(off1 + 2 * i + 1, off2 + 2 * j);
        addEdge(off2 + 2 * i + 1, off1 + 2 * j);
    }
    addEdge(off1 + 2 * K - 1, off1 + 2 * K - 2);
    addEdge(off2 + 2 * K - 1, off2 + 2 * K - 2);
    j = K - 1;
    forn(i, K) {
        while (j >= 0 && v[i] + v[j] >= t) --j;
        if (j < 0) break;
//        cerr << v[i] << " => !" << v[j] << '\n';
        addEdge(off1 + 2 * i, off2 + 2 * j + 1);
        addEdge(off2 + 2 * i, off1 + 2 * j + 1);
    }
    forn(i, N) {
        int j = (upper_bound(all(v), r[i]) - v.begin()) - 1;
        assert(j >= 0);
//        cerr << "p" << i << " => " << v[j] << '\n';
        addEdge(off3 + 2 * i, off1 + 2 * j);
        addEdge(off3 + 2 * i + 1, off2 + 2 * j);

        j = (lower_bound(all(v), l[i]) - v.begin()) - 1;
        if (j < 0) continue;
//        cerr << "!p" << i << " => !" << v[j] << '\n';
        addEdge(off3 + 2 * i, off1 + 2 * j + 1);
        addEdge(off3 + 2 * i + 1, off2 + 2 * j + 1);
    }
    forn(i, M) {
        int x = conf[i].fi, y = conf[i].se;
        addEdge(off3 + 2 * x, off3 + 2 * y + 1);
        addEdge(off3 + 2 * x + 1, off3 + 2 * y);
    }

    forn(i, V) dfs_ord(i);
    reverse(all(ord));
    forn(i, V) vis[i] = 0;
    int cc = 0;
    for (int v: ord) {
        if (vis[v]) continue;
        dfs_mark(v, cc++);
    }

    forn(i, V / 2) ok &= comp[2 * i] != comp[2 * i + 1];

    if (!ok) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    cout << "POSSIBLE\n";
    int A = 0, B = 0;
    forn(i, K) if (val(off1 + 2 * i) == 1) {
        A = v[i]; break;
    }
    forn(i, K) if (val(off2 + 2 * i) == 1) {
        B = v[i]; break;
    }
    cout << A << ' ' << B << '\n';
    forn(i, N) cout << (val(off3 + 2 * i) ? '1' : '2');
    cout << '\n';

#ifdef LOCAL_DEFINE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
