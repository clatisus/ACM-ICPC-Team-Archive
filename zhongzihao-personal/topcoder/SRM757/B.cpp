#include <bits/stdc++.h>

const int N = 10;
typedef std::pair<int, int> pii;

std::vector<int> vec[N][N];
int cnt = 0;

struct MatchNim {
public:
    std::map<pii, bool> map;

    int encode(std::vector<int> vec) {
        int ret = 0;
        for (int i = 0; i < vec.size(); ++i) {
            ret |= vec[i] << (i * 3);
        }
        return ret;
    }

    std::vector<int> decode(int code, int len) {
        std::vector<int> ret(len);
        for (int i = 0; i < len; ++i) {
            ret[i] = code >> (i * 3) & 7;
        }
        return ret;
    }

    int dfs(std::vector<int> piles) {
        ++cnt;
        if (cnt % 100000 == 0) {
            printf("%d\n", cnt);
            fflush(stdout);
        }
        if (piles.empty()) {
            return 1;
        }
        pii code = {encode(piles), piles.size()};
        if (map.count(code)) {
            return map[code];
        }
        int n = piles.size();
        for (auto u : piles) {
            if (u >= n - 1) {
                return map[code] = 0;
            }
        }
        int ans = 1;
        for (int i = 0; i < n; ++i) {
            if (i && piles[i] == piles[i - 1]) {
                continue;
            }
            for (int j = 1; j <= piles[i]; ++j) {
                std::vector<int> npiles = piles;
                npiles[i] -= j;
                if (!npiles[i]) {
                    std::swap(npiles[i], npiles.back());
                    npiles.pop_back();
                }
                std::sort(npiles.begin(), npiles.end());
                int nn = npiles.size();
                for (auto k : vec[nn][j]) {
                    std::vector<int> nnpiles;
                    for (int u = 0; u < nn; ++u) {
                        if (!(k >> u & 1)) {
                            nnpiles.push_back(npiles[u]);
                        }
                    }
                    if (dfs(nnpiles)) {
                        ans = 0;
                        break;
                    }
                }
                if (!ans) {
                    break;
                }
            }
            if (!ans) {
                break;
            }
        }
        return map[code] = ans;
    }

    std::string getName(int id) {
        return id == 0 ? "Yvonne" : "Zara";
    }

    std::string whoWins(std::vector<int> piles) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = (1 << i) - 1; k >= 0; --k) {
                    if (__builtin_popcount(k) <= j) {
                        vec[i][j].push_back(k);
                    }
                }
            }
        }
        std::sort(piles.begin(), piles.end());
        return getName(dfs(piles));
    }
};

int main() {
    int begin = clock();
    MatchNim m;
    std::cout << m.whoWins({7, 7, 7, 7, 7, 7, 7, 7, 7});
    printf("%.3f\n", 1.0 * (clock() - begin) / CLOCKS_PER_SEC);
    return 0;
}
