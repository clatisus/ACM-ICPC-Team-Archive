#include<bits/stdc++.h>

typedef long long ll;
typedef std::pair <int, int> pii;
const int moder = 998244353;

const int N = 1000010;

int inv[N], invf[N];

struct poly{
	static const int N = 1000;

	int a[N];
	int len;

	poly():len(-1){memset(a, 0, sizeof(a));}

	int &operator [](int sit){return a[sit];}

	static poly interpolation(std::vector <pii> vec){
		int n = vec.size() - 1;
		poly aux; aux.len = 0; aux.a[0] = 1;
		for (int i = 0; i <= n; ++ i, ++aux.len){
			int coe = moder - vec[i].first;
			coe -= coe >= moder ? moder : 0;
			for (int j = aux.len; j >= 0; --j){
				aux.a[j + 1] += aux.a[j];
				aux.a[j + 1] -= aux.a[j + 1] >= moder ? moder : 0;
				aux.a[j] = 1ll * aux.a[j] * coe % moder;
			}
		}
		poly ret;
		for (int i = 0; i <= n; ++i){
			int coe = moder - vec[i].first;
			coe -= coe >= moder ? moder : 0;
			int x = 1;
			for (int j = 0; j <= n; ++j){
				if (i == j) continue;
				x = 1ll * x * (vec[i].first - vec[j].first) % moder;
				x += x < 0 ? moder : 0;
			}
			x = 1ll * powermod(x, moder - 2) * vec[i].second % moder;
			int left = aux.a[aux.len];
			for (int j = aux.len; j; --j){
				ret.a[j - 1] = (ret.a[j - 1] + 1ll * left * x) % moder;
				left = (aux.a[j - 1] - 1ll * left * coe) % moder;
				left += left < 0 ? moder : 0;
			}
		}
		ret.len = n;
		return ret;
	}

	static int interpolation(std::vector <int> vec, int x){
		int n = vec.size() - 1;
		if (x >= 0 && x <= n) return vec[x];
		std::vector <int> pre(n + 1), suf(n + 1);
		pre[0] = suf[n] = 1;
		for (int i = 1; i <= n; ++ i){
			pre[i] = 1ll * pre[i - 1] * (x - i + 1) % moder;
			pre[i] += pre[i] < 0 ? moder : 0;
		}
		for (int i = n - 1; i >= 0; -- i){
			suf[i] = 1ll * suf[i + 1] * (x - i - 1) % moder;
			suf[i] += suf[i] < 0 ? moder : 0;
		}
		int ans = 0;
		for (int i = 0; i <= n; ++ i){
			ans = (ans + ((n - i) & 1 ? -1ll : 1ll) * vec[i] * pre[i] % moder * suf[i] % moder * invf[i] % moder * invf[n - i]) % moder;
		}
		ans += ans < 0 ? moder : 0;
		return ans;
	}
};

int main(){
}
