#include<bits/stdc++.h>

typedef long long ll;
const int N = 1010;
const int M = 200;

struct BigInteger{ // 仅支持非负整数
	static const int N = 40;
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
BigInteger power[N];
std::bitset <M> set[N];

void solve(){
    for (int i = 0; i < N; ++ i){
        set[i].reset();
    }
    int n;
//#define DEBUG
#ifdef DEBUG
    n = 1000;
#else
    scanf("%d", &n);
#endif
    for (int i = 0; i < n; ++ i){
#ifdef DEBUG
        a[i] = i + 1;
#else
        scanf("%d", &a[i]);
#endif
    }
    for (int i = 0; i < n; ++ i){
        int x = a[i];
        while (x > 1){
            int tmp = min[x];
            int sit = std::lower_bound(prime.begin(), prime.end(), tmp) - prime.begin();
            while (x % tmp == 0){
                set[i][sit] = set[i][sit] ^ 1;
                x /= tmp;
            }
        }
    }
    int now = 0;
    for (int i = 0; i < M; ++ i){
        int sit = -1;
        for (int j = now; j < n; ++ j){
            if (set[j][i]){
                sit = j;
                break;
            }
        }
        if (sit == -1){
            continue;
        }
        std::swap(set[now], set[sit]);
        for (int j = now + 1; j < n; ++ j){
            if (set[j][i]){
                set[j] ^= set[now];
            }
        }
        ++ now;
    }
    power[n - now].write();
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
    power[0] = BigInteger(0);
    for (int i = 1; i < N; ++ i){
        power[i] = power[i - 1] + power[i - 1] + BigInteger(1);
    }
    int test;
#ifdef DEBUG
    test = 1;
#else
    scanf("%d", &test);
#endif
    while (test --){
        solve();
    }
    return 0;
}
