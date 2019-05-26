#include <bits/stdc++.h>

const int moder = (int) 1e9 + 7;
const int N = 100;
const int M = 1010;

int powermod(int a, int exp){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * ret * a % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

int p[N];
int inv[N];
int mat[M][M];
int add[M];
std::map <std::vector <int>, int> map;

int dfs(std::vector <int> vec){
    if (map.count(vec)){
        return map[vec];
    }
    int tmp = map.size();
    map[vec] = tmp;
    int n = vec.size();
    for (int i = 0; i < n; ++ i){
        std::vector <int> nvec(n);
        for (int j = 0; j < n; ++ j){
            for (int k = -1; k <= 1; ++ k){
                if (0 <= j + k && j + k < n){
                    nvec[j] = std::max(nvec[j], vec[j + k]);
                }
            }
        }
        ++ nvec[i];
        int prob = 1ll * p[i] * inv[10] % moder;
        int max1 = 0, max2 = 0, min = INT_MAX;
        for (int j = 0; j < n; ++ j){
            max1 = std::max(max1, vec[j]);
            max2 = std::max(max2, nvec[j]);
            min = std::min(min, nvec[j]);
        }
        add[tmp] = (add[tmp] + 1ll * (max2 - max1) * prob) % moder;
        for (auto &u : nvec){
            u -= min;
        }
        int &u = mat[dfs(nvec)][tmp];
        u += prob;
        u -= u >= moder ? moder : 0;
    }
    return tmp;
}

int main(){
    inv[1] = 1;
    for (int i = 2; i < N; ++ i){
        inv[i] = moder - 1ll * (moder / i) * inv[moder % i] % moder;
    }
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
        double x;
        scanf("%lf", &x);
        p[i] = std::round(x * 10);
    }
    dfs(std::vector <int>(n));
    int m = map.size();
    for (int i = 0; i < m; ++ i){
        mat[i][i] -= 1;
        mat[i][i] += mat[i][i] < 0 ? moder : 0;
    }
    for (int i = 0; i <= m; ++ i){
        mat[m - 1][i] = 1;
    }
    for (int i = 0; i < m; ++ i){
        for (int j = i; j < m; ++ j){
            if (mat[j][i]){
                for (int k = i; k <= m; ++ k){
                    std::swap(mat[i][k], mat[j][k]);
                }
                break;
            }
        }
        int inv = powermod(mat[i][i], moder - 2);
        for (int j = i; j <= m; ++ j){
            mat[i][j] = 1ll * mat[i][j] * inv % moder;
        }
        for (int j = 0; j < m; ++ j){
            if (i == j){
                continue;
            }
            for (int k = m; k >= i; -- k){
                mat[j][k] = (mat[j][k] - 1ll * mat[j][i] * mat[i][k]) % moder;
                mat[j][k] += mat[j][k] < 0 ? moder : 0;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < m; ++ i){
        ans = (ans + 1ll * add[i] * mat[i][m]) % moder;
    }
    printf("%d\n", ans);
    return 0;
}
