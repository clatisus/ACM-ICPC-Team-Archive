#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
const int N = 9;
const int M = 3010;
const int MAX = 20;
inline int lowbit(int n){return n & -n;}

int lcm[1 << N], bitcnt[1 << N];
ll dp[60][MAX][M], powermod[MAX], ans[1 << N];
ull power[MAX];
int digit[MAX];
int moder[M], modercnt;

ll calc(ll n){
	++ n;
	for (int i = 1; i < 1 << N; ++ i){
		ans[i] = 0;
		power[0] = powermod[0] = 1 % lcm[i];
		for (int j = 1; j < MAX; ++ j){
			power[j] = power[j - 1] * 10;
			powermod[j] = powermod[j - 1] * 10 % lcm[i];
		}
		std::vector <int> vec = {0};
		for (int j = 0; j < N; ++ j){
			if (i >> j & 1){
				vec.push_back(j + 1);
			}
		}
		int cnt = 0;
		ll nn = n;
		for ( ; nn; digit[cnt ++] = nn % 10, nn /= 10);
		std::reverse(digit, digit + cnt);
		for (int j = 0, now = 0; j < cnt; ++ j){
			for (int k = 0; k < digit[j]; ++ k){
				if (k && !(i >> k - 1 & 1)) continue;
				int pre = (now + k * powermod[cnt - 1 - j]) % lcm[i];
				ans[i] += dp[cnt - 1 - j][(lcm[i] - pre) % lcm[i]];
			}
			if (digit[j] && !(i >> digit[j] - 1 & 1)) break;
			now = (now + digit[j] * powermod[cnt - 1 - j]) % lcm[i];
		}
	}
	ans[0] = 1;
	ll ret = 0;
	for (int i = 0; i < 1 << N; ++ i){
		for (int j = 0; j < i; ++ j){
			if ((i & j) == j){
				ans[i] += (bitcnt[i ^ j] & 1 ? -1 : 1) * ans[j];
			}
		}
		ret += ans[i];
	}
	return ret;
}

int main(){
	int test;
	scanf("%d", &test);
	lcm[0] = 1;
	for (int i = 1; i < 1 << N; ++ i){
		int x = lowbit(i);
		bitcnt[i] = bitcnt[i ^ x] + 1;
		int y = lcm[i ^ x];
		int cnt = 0;
		for ( ; x; x >>= 1, ++ cnt);
		lcm[i] = y * cnt / std::__gcd(y, cnt);
		moder[modercnt ++] = lcm[i];
	}
	std::sort(moder, moder + modercnt);
	modercnt = std::unique(moder, moder + modercnt) - moder;
	for (int i = 0; i < modercnt; ++ i){
		dp[i][0][0] = 1;
		for (int j = 0, now = 1; j < MAX - 1; ++ j){
			for (int k = 0; k < moder[i]; ++ k){
				dp[i][j + 1][(k + now * )];
			}
			now = now * 10 % moder[i];
		}
	}
	while (test --){
		ll l, r;
		scanf("%I64d%I64d", &l, &r);
		printf("%I64d\n", calc(r) - calc(l - 1));
	}
	return 0;
}
