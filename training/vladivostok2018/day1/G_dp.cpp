#include<bits/stdc++.h>

typedef long long ll;
const int N = 1010;
const int SMALL = 31;
const int M = 1 << 11;

struct BigInteger{ // 仅支持非负整数
	static const int N = 15;
	static const ll base = 1000000000000000000ll; // 修改它时记得修改输入输出格式
	ll a[N];
	int length;

	BigInteger():length(0){memset(a, 0, sizeof(a));}

	BigInteger(ll p){
		memset(a, 0, sizeof(a));
		length = 0;
		if (!p) return;
		for (ll x = std::abs(p); x; x /= base){
			a[length ++] = x % base;
		}
	}

	ll &operator [](int sit){return a[sit];}

	BigInteger operator + (const BigInteger &p)const{
	    if (length == 0){
            return p;
	    }
	    if (p.length == 0){
            return *this;
	    }
		BigInteger ret;
		ret.length = std::max(length, p.length) + 1;
		for (int i = 0; i < ret.length; ++ i){
			ret.a[i] += a[i] + p.a[i];
			if (ret.a[i] >= base) ret.a[i] -= base, ++ ret.a[i + 1];
		}
		for ( ; ret.length && !ret.a[ret.length - 1]; -- ret.length)
			;
		return ret;
	}

	BigInteger operator - (const BigInteger &p)const{
		BigInteger ret;
		ret.length = length;
		for (int i = 0; i < ret.length; ++ i){
			ret.a[i] += a[i] - p.a[i];
			if (ret.a[i] < 0) ret.a[i] += base, -- ret.a[i + 1];
		}
		for ( ; ret.length && !ret.a[ret.length - 1]; -- ret.length)
			;
		return ret;
	}

	void write(){
		if (!length) return (void) printf("0");
		printf("%lld", a[length - 1]);
		for (int i = length - 2; ~i; -- i){
			printf("%018lld", a[i]);
		}
	}
};

int min[N], a[N];
std::vector <int> prime;
std::vector <int> vec[N];
int bit[N];
bool big[N];
BigInteger dp[2][2][M], dp1[2][M];

ll solve(){
    memset(bit, 0, sizeof(bit));
    memset(big, 0, sizeof(big));
    std::map <int, int> Hash;
    int cnt = 0;
    for (auto u : prime){
        if (u <= SMALL){
            Hash[u] = cnt ++;
        }
    }
    for (int i = 0; i < N; ++ i){
        vec[i].clear();
    }
    int n;
    n = 1000;
    //scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
        //scanf("%d", &a[i]);
        a[i] = i + 1;
    }
    for (int i = 0; i < n; ++ i){
        int x = a[i];
        while (x > 1){
            int tmp = min[x];
            if (tmp <= SMALL){
                while (x % tmp == 0){
                    x /= tmp;
                    bit[i] ^= 1 << Hash[tmp];
                }
            }
            else{
                big[i] = true;
                vec[tmp].push_back(i);
                x /= tmp;
            }
        }
    }
    for (int i = 0; i < 2; ++ i){
        for (int j = 0; j < 2; ++ j){
            for (int k = 0; k < M; ++ k){
                dp[i][j][k] = BigInteger();
            }
        }
    }
    for (int j = 0; j < 2; ++ j){
        for (int k = 0; k < M; ++ k){
            dp1[j][k] = BigInteger();
        }
    }
    dp[0][0][0] = BigInteger(1);
    for (int i = SMALL + 1; i < N; ++ i){
        if (min[i] != i || vec[i].size() <= 1) continue;
        for (auto u : vec[i]){
            for (int j = 0; j < 2; ++ j){
                for (int k = 0; k < M; ++ k){
                    dp[1][j][k] = BigInteger();
                }
            }
            for (int j = 0; j < 2; ++ j){
                for (int k = 0; k < M; ++ k){
                    dp[1][j ^ 1][k ^ bit[u]] = dp[1][j ^ 1][k ^ bit[u]] + dp[0][j][k];
                }
            }
            for (int j = 0; j < 2; ++ j){
                for (int k = 0; k < M; ++ k){
                    dp[0][j][k] = dp[0][j][k] + dp[1][j][k];
                }
            }
        }
        for (int k = 0; k < M; ++ k){
            dp[0][1][k] = BigInteger();
        }
    }
    for (int i = 0; i < M; ++ i){
        dp1[0][i] = dp[0][0][i];
    }
    for (int i = 0; i < n; ++ i){
        if (!big[i]){
            for (int k = 0; k < M; ++ k){
                dp1[1][k] = BigInteger();
            }
            for (int j = 0; j < M; ++ j){
                dp1[1][j ^ bit[i]] = dp1[1][j ^ bit[i]] + dp1[0][j];
            }
            for (int j = 0; j < M; ++ j){
                dp1[0][j] = dp1[0][j] + dp1[1][j];
            }
        }
    }
    (dp1[0][0] - BigInteger(1)).write();
    putchar('\n');
}

int main(){
    for (int i = 2; i < N; ++ i){
        if (!min[i]){
            min[i] = i;
            prime.push_back(i);
        }
        for (int j = 0, sz = prime.size(), k; j < sz && i * prime[j] < N; ++ j){
            min[k = i * prime[j]] = prime[j];
            if (i % prime[j] == 0){
                break;
            }
        }
    }
    int test;
    //scanf("%d", &test);
    test = 1;
    while (test --){
        solve();
    }
    return 0;
}
