#include <bits/stdc++.h>

const int N = 2200;
const int M = 400;
const int K = 200010;
typedef long long ll;

std::vector <int> prime;
int min[N], digit[N];
ll dp[M][N], dpcnt[M][N];
ll dp1[M][N], dpcnt1[M][N];
std::vector <int> stack;
int n;
char s[K];
int len;
ll sit;
ll zzh;
//char answer[] = "[2], [3], [2, 3], [5], [2, 5], [7], ";

void solve1(int sum, ll l, ll r, int prev){
    if (sum == 0){
        s[len ++] = '[';
        int num = stack.size();
        for (int i = 0; i < num; ++ i){
            std::vector <int> vec;
            int u = stack[i];
            while (u){
                vec.push_back(u % 10);
                u /= 10;
            }
            while (!vec.empty()){
                s[len ++] = vec.back() + '0';
                vec.pop_back();
            }
            if (i == num - 1){
                s[len ++] = ']';
            }
            else{
                s[len ++] = ',';
                s[len ++] = ' ';
            }
        }
        s[len ++] = ',';
        s[len ++] = ' ';
        return;
    }
    ll tot = 0;
    for (int i = prev + 1; i < n; ++ i){
        ll left = tot, right = left + dp1[i][sum] + dpcnt1[i][sum] * (2 + zzh) - 1;
        ll l1 = std::max(left, l), r1 = std::min(right, r);
        if (l1 <= r1){
            stack.push_back(prime[i]);
            zzh += digit[prime[i]] + 2;
            solve1(sum - prime[i], l1 - left, r1 - left, i);
            zzh -= digit[prime[i]] + 2;
            stack.pop_back();
        }
        else if (right < l){
            sit += right - left + 1;
        }
        tot = right + 1;
    }
}

void solve(ll a, ll b){
    stack.clear();
    len = sit = zzh = 0;
    -- a, -- b;
    ll sum = 0;
    for (int i = 1; i < N; ++ i){
        ll left = sum, right = sum + dp[0][i] + dpcnt[0][i] * 2 - 1;
        ll l = std::max(left, a), r = std::min(right, b);
        if (l <= r){
            solve1(i, l - left, r - left, -1);
        }
        else if (right < a){
            sit += right - left + 1;
        }
        sum = right + 1;
    }
    for (ll i = a; i <= b; ++ i){
        putchar(s[i - sit]);
        //assert(s[i - sit] == answer[i]);
    }
    puts("");
}

int main(){
    freopen("list.in", "r", stdin);
    freopen("list.out", "w", stdout);
    for (int i = 1; i < N; ++ i){
        int x = i;
        while (x){
            ++ digit[i];
            x /= 10;
        }
    }
    for (int i = 2; i < N; ++ i){
        if (!min[i]){
            min[i] = i;
            prime.push_back(i);
        }
        for (auto u : prime){
            if (i * u >= N){
                break;
            }
            min[i * u] = u;
            if (i % u == 0){
                break;
            }
        }
    }
    n = prime.size();
    dp[n][0] = 0, dpcnt[n][0] = 1;
    for (int i = n - 1; i >= 0; -- i){
        int u = prime[i];
        for (int j = 0; j < N; ++ j){
            dp[i][j] = dp[i + 1][j];
            dpcnt[i][j] = dpcnt[i + 1][j];
        }
        for (int j = N - 1 - u; j >= 0; -- j){
            dpcnt[i][j + u] += dpcnt[i + 1][j];
            dpcnt1[i][j + u] = dpcnt[i + 1][j];
            dp[i][j + u] += dpcnt[i + 1][j] * (digit[u] + 2) + dp[i + 1][j];
            dp1[i][j + u] = dpcnt[i + 1][j] * (digit[u] + 2) + dp[i + 1][j];
        }
    }
    ll sum = 0;
    for (int i = 1; i < N; ++ i){
        sum += dp[0][i];
        assert(sum >= 0);
    }
    //printf("%lld\n", sum);
    //printf("%d\n", (int) prime.size());
    /*ll cnt = strlen(answer);
    for (int i = 0; i < cnt; ++ i){
        for (int j = i; j < cnt; ++ j){
            solve(i + 1, j + 1);
        }
    }*/
    ll a, b;
    scanf("%lld%lld", &a, &b);
    solve(a, b);
    return 0;
}