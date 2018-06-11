#include<bits/stdc++.h>
#define ll long long

std::deque <std::pair <int, double>> dq;

int n, l;

int main(){
	scanf("%d%d", &n, &l);
	double sum = 0;
	for (int i = 0, v, t; i < n; ++ i){
		scanf("%d%d", &t, &v);
		int now = l;
		while (dq.size() && now - dq.back().first + v >= l){
			now -= dq.back().first;
			sum -= dq.back().second;
			dq.pop_back();
		}
		if (!dq.size()){
			dq.push_front({v, 1ll * t * v});
			sum = 1ll * t * v;
			printf("%.10lf\n", 1.0 * t);
			continue;
		}
		int x = dq.back().first;
		double y = dq.back().second;
		std::pair <int, double> p = {l - v - now + x, y / x * (l - v) + y - y * now / x};
		sum += p.second - y + 1ll * t * v;
		dq.pop_back();
		dq.push_back(p);
		printf("%.10lf\n", sum / l);
		p = {v, 1ll * t * v};
		while (dq.size() && p.first * dq.front().second >= p.second * dq.front().first){
			p = {p.first + dq.front().first, p.second + dq.front().second};
			dq.pop_front();
		}
		dq.push_front(p);
	}
	return 0;
}
