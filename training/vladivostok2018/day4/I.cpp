#include <bits/stdc++.h>

const int max_N = 300 + 21;

int n, m, tot, s[6][6], t[6][6];

char str[10];

std::unordered_map<int, int> map;
std::vector<int> state;

int myHash(int x, int y) {
    return (x - 1) * m + (y - 1);
}

long double a[max_N][max_N];

int vec[6];

void dfs(int x, int last) {
    if (!x) {
        int hash = 0;
        for (int i = 1; i <= n; ++i) {
            if (vec[i]) {
                hash |= (1 << myHash(i, vec[i]));
            }
        }
        if (!map.count(hash)) {
            map[hash] = ++tot;
            state.push_back(hash);
        }
        return;
    }
    vec[x] = 0;
    dfs(x - 1, last);
    for (int a = last + 1; a <= m; ++a) {
        vec[x] = a;
        dfs(x - 1, a);
    }
}

void getState() {
    map[0] = ++tot;
    state.push_back(0);
    dfs(n, 0);
    /*
    printf("tot = %d\n", tot);
    for (auto &set : state) {
        printf("set = %d\n", set);
    }
     */
}

using pair = std::pair<int, int>;
using vector = std::vector<pair>;

void getTrans() {
    static long double tmp = (n * m * 2);

    for (auto &set : state) {
        if (!set) {
            a[1][1] = 1;
            continue;
        }

        int id = map[set];

        int vec[6];
        for (int i = 1; i <= n; ++i) {
            vec[i] = 0;
            for (int j = 1; j <= m; ++j) {
                if ((set >> myHash(i, j)) & 1) {
                    vec[i] = j;
                    break;
                }
            }
        }

        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                for (int c = 0; c <= 1; ++c) {
                    int _vec[6];
                    for (int a = 1; a <= n; ++a) {
                        _vec[a] = vec[a];
                    }
                    for (int a = 1; a <= i; ++a) {
                        if (_vec[a] <= j) {
                            _vec[a] = 0;
                            for (int b = j; b; --b)
                                if (t[a][b] != c) {
                                    _vec[a] = b;
                                    break;
                                }
                        }
                    }

                    int last = 0, hash = 0;
                    for (int a = n; a; --a)
                        if (_vec[a] <= last) {
                            _vec[a] = 0;
                        } else {
                            hash |= (1 << myHash(a, _vec[a]));
                            last = _vec[a];
                        }

                    assert(map.count(hash));
                    // printf("set = %d, (%d, %d, %d) : %d\n", set, i, j, c, hash);
                    a[id][tot + 1] += i * j;
                    --a[id][map[hash]];
                }

        a[id][id] += tmp;
    }
/*
    for (int i = 1; i <= tot; ++i) {
        for (int j = 1; j <= tot; ++j) {
            printf("(%.10f * e[%d]) %c ", a[i][j], j, "+ "[j == tot]);
        }
        printf("= %.10f\n", a[i][tot + 1]);
    }
*/
}

#define eps (1e-20)

long double gauss(int s) {
    for (int i = 1, j, k; i <= tot; ++i) {
        j = i;
        for (k = i; k <= tot; ++k) {
            if (std::abs(a[k][i]) > std::abs(a[j][i])) {
                j = k;
            }
        }
        if (i != j) {
            for (k = i; k <= tot + 1; ++k) {
                std::swap(a[i][k], a[j][k]);
            }
        }
        long double tmp = a[i][i];
        a[i][i] = 1.;
        for (k = i + 1; k <= tot + 1; ++k) {
            a[i][k] /= tmp;
        }
        for (j = 1; j <= tot; ++j) {
            if (j == i || std::abs(a[j][i]) < eps) continue;
            tmp = a[j][i];
            a[j][i] = 0;
            for (k = i + 1; k <= tot + 1; ++k) {
                a[j][k] -= a[i][k] * tmp;
            }
        }
    }
    return a[s][tot + 1];
}

int main() {
    scanf("%d%d", &n, &m);

    getState();

    for (int i = 1; i <= n; ++i) {
        scanf("%s", str);
        for (int j = 1; j <= m; ++j) {
            s[i][j] = str[j - 1] == 'B';
        }
    }

    for (int i = 1; i <= n; ++i) {
        scanf("%s", str);
        for (int j = 1; j <= m; ++j) {
            t[i][j] = str[j - 1] == 'B';
        }
    }

    int last = 0, hash = 0;
    for (int i = n; i; --i) {
        vec[i] = 0;
        for (int j = m; j; --j)
            if (s[i][j] != t[i][j]) {
                vec[i] = j;
                break;
            }
        if (vec[i] <= last) {
            vec[i] = 0;
        } else {
            hash |= (1 << myHash(i, vec[i]));
            last = vec[i];
        }
    }

    getTrans();

    printf("%.10f\n", (double) gauss(map[hash]));

    return 0;
}

/*
5 5
BBBBB
BBBBB
BBBBB
BBBBB
BBBBB

BBBBB
BBBWB
BBBBB
BWBBB
BBBBB
 */
