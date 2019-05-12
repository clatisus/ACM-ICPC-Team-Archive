#include <bits/stdc++.h>

const int N = 10010;
typedef long long ll;
typedef std::pair <int, int> pii;

int left[N], right[N];
std::bitset <N> set[N];
ll sumx[N], sumy[N], cnt[N];
int n, w;
int h, m;

pii get(int l, int k){
    if (l & 1){
        return {n, 2 * k + 1};
    }
    else{
        return {2 * k + 1, n};
    }
}

int main(){
    freopen("jenga.in", "r", stdin);
    freopen("jenga.out", "w", stdout);
    scanf("%d%d", &n, &w);
    scanf("%d%d", &h, &m);
    for (int i = 0; i < h; ++ i){
        left[i] = 0, right[i] = n - 1;
        for (int j = 0; j < n; ++ j){
            set[i][j] = 1;
            pii p = get(i, j);
            sumx[i] += p.first, sumy[i] += p.second;
            cnt[i] += 2;
        }
    }
    for (int i = h - 2; i >= 0; -- i){
        sumx[i] += sumx[i + 1];
        sumy[i] += sumy[i + 1];
        cnt[i] += cnt[i + 1];
    }
    for (int TEST = 1; TEST <= m; ++ TEST){
        int l, k;
        scanf("%d%d", &l, &k);
        -- l, -- k;
        set[l][k] = 0;
        left[l] = right[l] = -1;
        for (int i = 0; i < n; ++ i){
            if (set[l][i]){
                left[l] = i;
                break;
            }
        }
        for (int i = n - 1; i >= 0; -- i){
            if (set[l][i]){
                right[l] = i;
                break;
            }
        }
        pii p = get(l, k);
        for (int i = 0; i <= l; ++ i){
            sumx[i] -= p.first;
            sumy[i] -= p.second;
            cnt[i] -= 2;
        }
        for (int i = 1; i < h; ++ i){
            if (!cnt[i]){
                break;
            }
            if (left[i - 1] == -1){
                printf("yes\n%d\n", TEST);
                return 0;
            }
            if (i & 1){
                if (sumx[i] <= cnt[i] * left[i - 1] || sumx[i] >= cnt[i] * (right[i - 1] + 1)){
                    printf("yes\n%d\n", TEST);
                    return 0;
                }
            }
            else{
                if (sumy[i] <= cnt[i] * left[i - 1] || sumy[i] >= cnt[i] * (right[i - 1] + 1)){
                    printf("yes\n%d\n", TEST);
                    return 0;
                }
            }
        }
    }
    puts("no");
    return 0;
}
