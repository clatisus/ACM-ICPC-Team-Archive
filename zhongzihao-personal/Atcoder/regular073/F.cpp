#include<bits/stdc++.h>
#define ll long long

const int MAX = 1 << 18;
const int N = 200010;

ll seg[2][2][MAX << 1];
int n, q, a, b;
int x[N];

void add(int type1, int type2, int sit, ll value){
	sit += MAX;
	seg[type1][type2][sit] = std::min(seg[type1][type2][sit], value);
	for (sit >>= 1 ; sit; sit >>= 1){
		seg[type1][type2][sit] = std::min(seg[type1][type2][sit << 1], seg[type1][type2][(sit << 1) + 1]);
	}
}

ll query(int type1, int type2, int left, int right){
	ll ret = LLONG_MAX;
	for (int l = left + MAX, r = right + MAX + 1; l < r; l >>= 1, r >>= 1){
		if (l & 1){
			ret = std::min(ret, seg[type1][type2][l ++]);
		}
		if (r & 1){
			ret = std::min(ret, seg[type1][type2][-- r]);
		}
	}
	return ret;
}

int main(){
	int x0;
	scanf("%d%d%d%d", &n, &q, &a, &b);
	for (int i = 0; i < q; ++ i){
		scanf("%d", &x[i]);
	}
	memset(seg, 0x3f, sizeof(seg));
	add(0, 0, b, b + std::abs(a - x[0]));
	add(0, 1, b, n - b + std::abs(a - x[0]));
	add(1, 0, a, a + std::abs(b - x[0]));
	add(1, 1, a, n - a + std::abs(b - x[0]));
	ll now = 0;
	for (int i = 1; i < q; ++ i){
		ll x1 = query(0, 0, x[i], n), x2 = query(0, 1, 1, x[i]);
		x1 -= x[i], x2 -= n - x[i];
		ll y1 = std::min(x1, x2) + now;
		x1 = query(1, 0, x[i], n), x2 = query(1, 1, 1, x[i]);
		x1 -= x[i], x2 -= n - x[i];
		ll y2 = std::min(x1, x2) + now;
		now += std::abs(x[i] - x[i - 1]);
		add(1, 0, x[i - 1], y1 - now + x[i - 1]);
		add(1, 1, x[i - 1], y1 - now + n - x[i - 1]);
		add(0, 0, x[i - 1], y2 - now + x[i - 1]);
		add(0, 1, x[i - 1], y2 - now + n - x[i - 1]);
	}
	ll ans = LLONG_MAX;
	for (int i = 1; i <= n; ++ i){
		ans = std::min(ans, seg[0][0][i + MAX] - i + now);
		ans = std::min(ans, seg[1][0][i + MAX] - i + now);
	}
	return printf("%lld\n", ans), 0;
}
