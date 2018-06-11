#include<bits/stdc++.h>

const int N = 200010;
const double PI = std::acos(-1);
typedef std::pair <int, int> pii;

std::vector <pii> fount;
int c[N];

bool in(int x1, int x2, int x){
	return x1 <= x && x <= x2 || x1 >= x && x >= x2;
}

const int MAX = 1 << 18;

int seg[MAX << 1];

void add(int sit, int value){
	seg[sit += MAX] = value;
	for (sit >>= 1; sit; sit >>= 1){
		seg[sit] = std::max(seg[sit << 1], seg[sit << 1 | 1]);
	}
}

int query(int l, int r){
	int ret = 0;
	for (l += MAX, r += MAX + 1; l < r; l >>= 1, r >>= 1){
		if (l & 1) ret = std::max(ret, seg[l ++]);
		if (r & 1) ret = std::max(ret, seg[-- r]);
	}
	return ret;
}

int main(){
	int x1, y1, x2, y2;
	int n;
	scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
	if (x1 > x2){
		std::swap(x1, x2);
		std::swap(y1, y2);
	}
	else if (x1 == x2 && y1 > y2){
		std::swap(y1, y2);
	}
	scanf("%d", &n);
	for (int i = 0, x, y; i < n; ++ i){
		scanf("%d%d", &x, &y);
		if (in(x1, x2, x) && in(y1, y2, y)){
			fount.push_back({x, y});
		}
	}
	std::sort(fount.begin(), fount.end());
	int cnt = 0;
	for (auto u : fount){
		c[cnt ++] = u.second;
	}
	std::sort(c, c + cnt);
	for (auto u : fount){
		int sit = std::lower_bound(c, c + cnt, u.second) - c;
		int x = y1 < y2 ? query(0, sit) : query(sit, MAX - 1);
		add(sit, x + 1);
	}
	int x = query(0, MAX - 1);
	double ans = 100ll * (std::abs(x2 - x1) + std::abs(y2 - y1));
	if (x == std::min(std::abs(x2 - x1), std::abs(y2 - y1)) + 1){
		-- x;
		ans += (PI - 2) * 10;
	}
	ans -= (2 - PI / 2) * x * 10;
	printf("%.15lf\n", ans);
	return 0;
}
