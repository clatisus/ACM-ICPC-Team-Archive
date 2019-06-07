#include <bits/stdc++.h>

const int N = 25;
typedef std::pair<int, std::vector<int>> piv;
typedef std::pair<int, int> pii;
typedef long long ll;

int moder;
std::map<piv, int> state;
std::map<piv, bool> vis;
int fa[N];

int powermod(int a, int exp) {
    int ret = 1;
    for (; exp > 0; exp >>= 1) {
        if (exp & 1) {
            ret = 1ll * ret * a % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

namespace BM {
    const int N = 5010;
    ll res[N], base[N], _c[N], _md[N];
    std::vector<int> Md;

    void mul(ll *a, ll *b, int k) {
        memset(_c, 0, sizeof(ll) * k * 2);
        for (int i = 0; i < k; ++i)
            if (a[i])
                for (int j = 0; j < k; ++j)
                    _c[i + j] = (_c[i + j] + a[i] * b[j]) % moder;
        for (int i = 2 * k - 2; i >= k; --i)
            if (_c[i])
                for (int j = 0; j < Md.size(); ++j)
                    (_c[i - k + Md[j]] -= _c[i] * _md[Md[j]]) %= moder;
        for (int i = 0; i < k; ++i) a[i] = _c[i];
    }

    int solve(ll n, std::vector<int> a, std::vector<int> b) {
        ll ans = 0, pnt = 0;
        int k = a.size() - 1;
        assert(a.size() - 1 == b.size());
        for (int i = 0; i <= k; ++i) _md[k - i] = a[i];
        Md.clear();
        for (int i = 0; i < k; ++i) if (_md[i]) Md.push_back(i);
        for (int i = 0; i < k; ++i) res[i] = base[i] = 0;
        res[0] = 1;
        while ((1ll << pnt) <= n) ++pnt;
        for (int p = pnt; p >= 0; --p) {
            mul(res, res, k);
            if ((n >> p) & 1) {
                for (int i = k - 1; i >= 0; --i) res[i + 1] = res[i];
                res[0] = 0;
                for (int j = 0; j < Md.size(); ++j) {
                    res[Md[j]] = (res[Md[j]] - res[k] * _md[Md[j]]) % moder;
                }
            }
        }
        for (int i = 0; i < k; ++i) {
            ans = (ans + res[i] * b[i]) % moder;
        }
        ans += ans < 0 ? moder : 0;
        return ans;
    }

    std::vector<int> BM(std::vector<int> s) {
        std::vector<int> C(1, 1), B(1, 1);
        int l = 0, m = 1, b = 1;
        for (int n = 0; n < s.size(); ++n) {
            ll d = 0;
            for (int i = 0; i <= l; ++i) {
                d = (d + 1ll * C[i] * s[n - i]) % moder;
            }
            if (!d) ++m;
            else {
                std::vector<int> T = C;
                ll c = moder - d * powermod(b, moder - 2) % moder;
                while (C.size() < B.size() + m) C.push_back(0);
                for (int i = 0; i < B.size(); ++i) {
                    C[i + m] = (C[i + m] + c * B[i]) % moder;
                }
                if (l * 2 <= n) {
                    l = n + 1 - l, B = T, b = d, m = 1;
                } else {
                    ++m;
                }
            }
        }
        return C;
    }
}

int find(int u) {
    return u == fa[u] ? u : (fa[u] = find(fa[u]));
}

void unite(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) {
        return;
    }
    fa[u] = v;
}

int getid(piv p) {
    auto u = state.find(p);
    if (u != state.end()) {
        return u->second;
    }
    int sz = state.size();
    return state[p] = sz;
}

int main() {
    int n, m;
    scanf("%d%d%d", &n, &m, &moder);
    int init = 0;
    for (int i = 0; i < 1 << n; ++i) {
        if (i & i << 1) {
            continue;
        }
        std::vector<int> whites;
        int pre = 0;
        for (int j = 0; j <= n; ++j) {
            if ((j == n || i >> j & 1)) {
                if (pre) {
                    whites.push_back(pre);
                }
                pre = 0;
            } else {
                pre |= 1 << j;
            }
        }
        std::sort(whites.begin(), whites.end());
        getid({i, whites});
        ++init;
    }
    std::vector<pii> trans;
    std::queue<piv> queue;
    for (auto u : state) {
        queue.push(u.first);
        vis[u.first] = true;
    }
    while (!queue.empty()) {
        piv u = queue.front();
        queue.pop();
        for (int i = 0; i < 1 << n; ++i) {
            if (i & i << 1 || i & u.first) {
                continue;
            }
            bool flag = true;
            for (auto v : u.second) {
                if ((v & i) == v) {
                    flag = false;
                    break;
                }
            }
            if (!flag) {
                continue;
            }
            for (int j = 0; j < N; ++j) {
                fa[j] = j;
            }
            for (int j = 0; j < n - 1; ++j) {
                if ((i >> j & 3) == 0) {
                    unite(j, j + 1);
                }
            }
            for (auto v : u.second) {
                for (int j = 0; j < n; ++j) {
                    for (int k = j + 1; k < n; ++k) {
                        if ((v >> j & 1) && (v >> k & 1)) {
                            unite(j + n, k + n);
                        }
                    }
                }
            }
            for (int j = 0; j < n; ++j) {
                if (!(u.first >> j & 1) && !(i >> j & 1)) {
                    unite(j, j + n);
                }
            }
            std::vector<int> bits;
            for (int j = 0; j < n; ++j) {
                if (!(i >> j & 1)) {
                    int bit = 0;
                    for (int k = 0; k < n; ++k) {
                        if (!(i >> k & 1) && find(k) == find(j)) {
                            bit |= 1 << k;
                        }
                    }
                    bits.push_back(bit);
                }
            }
            std::sort(bits.begin(), bits.end());
            bits.erase(std::unique(bits.begin(), bits.end()), bits.end());
            trans.push_back({getid(u), getid({i, bits})});
            if (!vis.count({i, bits})) {
                vis[{i, bits}] = true;
                queue.push({i, bits});
            }
        }
    }
    std::vector<int> end;
    for (auto u : state) {
        if ((int) u.first.second.size() == 1) {
            end.push_back(u.second);
        }
    }
    std::vector<int> now(state.size());
    for (int i = 0; i < init; ++i) {
        now[i] = 1;
    }
    std::vector<int> b(2 * state.size() + 5);
    for (int i = 0; i < b.size(); ++i) {
        for (auto u : end) {
            b[i] = (b[i] + now[u]) % moder;
        }
        std::vector<int> tmp(now.size());
        for (auto u : trans) {
            tmp[u.second] = (tmp[u.second] + now[u.first]) % moder;
        }
        now = tmp;
    }
    std::vector<int> a = BM::BM(b);
    b.erase(b.begin() + a.size() - 1, b.end());
    printf("%d\n", BM::solve(m - 1, a, b));
    return 0;
}