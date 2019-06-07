#include <bits/stdc++.h>

#include<bits/stdc++.h>

typedef long long ll;
const int MAX = 21;
const int moder = 998244353;
const int root = 3;

int w[2][1 << MAX];

int powermod(int a, int exp) {
    int ret = 1;
    for (; exp > 0; exp >>= 1) {
        if (exp & 1) {
            ret = 1ll * a * ret % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

void init() {
    w[0][0] = w[1][0] = 1;
    w[0][1] = powermod(root, (moder - 1) >> MAX);
    for (int i = 2; i < (1 << MAX); ++i) {
        w[0][i] = 1ll * w[0][i - 1] * w[0][1] % moder;
    }
    for (int i = 1; i < (1 << MAX); ++i) {
        w[1][(1 << MAX) - i] = w[0][i];
    }
}

void NTT(std::vector<int> &a, int len, int type) {
    for (int i = 1, j = 0; i < len - 1; ++i) {
        for (int s = len; j ^= (s >>= 1), ~j & s;);
        if (i < j) {
            std::swap(a[i], a[j]);
        }
    }
    for (int i = 2, d = 1; i <= len; i <<= 1, ++d) {
        for (int j = 0; j < len; j += i) {
            auto u = a.begin() + j;
            for (int k = 0; k < i / 2; ++k) {
                int t = 1ll * w[type][k << (MAX - d)] * u[k + i / 2] % moder;
                u[k + i / 2] = u[k] - t + (u[k] - t < 0 ? moder : 0);
                u[k] += t;
                u[k] -= u[k] >= moder ? moder : 0;
            }
        }
    }
    if (type == 0) return;
    int inv = powermod(len, moder - 2);
    for (int i = 0; i < len; ++i) {
        a[i] = 1ll * a[i] * inv % moder;
    }
}

struct poly {
    std::vector<int> a;
    int len;

    poly() : len(-1) {}

    explicit poly(int len) : len(len) { a.resize(len + 1); }

    poly(const poly &p, int len) : len(len) {
        a.resize(len + 1);
        for (int i = 0; i <= len; ++i) {
            a[i] = i > p.len ? 0 : p.a[i];
        }
    }

    int &operator[](int n) {
        assert(n >= 0 && n <= len);
        return a[n];
    }

    poly operator*(const poly &p) const {
        if (!~len || !~p.len) return poly(-1);
        int n = len + p.len;
        int lenret = 1;
        for (; lenret <= n; lenret <<= 1);
        poly ret(*this, lenret);
        std::vector<int> aux(lenret);
        std::copy(p.a.begin(), p.a.begin() + p.len + 1, aux.begin());
        NTT(ret.a, lenret, 0);
        NTT(aux, lenret, 0);
        for (int i = 0; i < lenret; ++i) {
            ret.a[i] = 1ll * ret.a[i] * aux[i] % moder;
        }
        NTT(ret.a, lenret, 1);
        ret.len = n;
        return ret;
    }
};

const int N = 500010;

int p[N], s[N];
int value[N];
bool vis[N];
int n, m, c;

std::bitset<N> solve(const poly &pol) {
    for (int i = 1; i <= c; ++i) {
        value[i] = rand() % (moder - 1) + 1;
    }
    poly p(m - 1);
    for (int i = 0; i < m; ++i) {
        p[i] = value[s[i]];
    }
    p = p * pol;
    std::bitset<N> ret;
    for (int i = n - 1; i < m; ++i) {
        ret[i - n + 1] = !p[i];
    }
    return ret;
}

std::bitset<N> solve1() {
    memset(vis, 0, sizeof(vis));
    poly pol(n - 1);
    for (int i = 0; i < n; ++i) {
        if (vis[i]) continue;
        std::vector<int> vec;
        int x = i;
        while (true) {
            vis[x] = true;
            vec.push_back(x);
            x = p[x];
            if (vis[x]) {
                break;
            }
        }
        if (vec.size() == 1) {
            pol[vec[0]] = 0;
            continue;
        }
        for (auto u : vec) {
            pol[u] = moder / vec.size();
        }
        x = moder % vec.size();
        for (auto u : vec) {
            if (!x) break;
            ++pol[u];
            --x;
        }
    }
    std::reverse(pol.a.begin(), pol.a.begin() + n);
    std::bitset<N> set;
    set.set();
    while (true) {
        std::bitset<N> tmp = solve(pol);
        if ((set & tmp) == set) {
            break;
        }
        set &= tmp;
    }
    return set;
}

int main() {
    srand((unsigned) time(nullptr));
    init();
    scanf("%d%d%d", &n, &m, &c);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &p[i]);
        --p[i];
    }
    for (int i = 0; i < m; ++i) {
        scanf("%d", &s[i]);
    }
    std::bitset<N> set = solve1();
    for (int i = 0; i < m - n + 1; ++i) {
        putchar(set[i] + '0');
    }
    puts("");
}
