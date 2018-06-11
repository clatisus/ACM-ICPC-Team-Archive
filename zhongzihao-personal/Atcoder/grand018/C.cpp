#include<bits/stdc++.h>

const int N = 100010;
typedef std::pair <int, int> pii;
typedef long long ll;

std::pair <pii, pii> p[N];
std::priority_queue <int> pq;
int a, b, c;
ll sumleft[N], sumright[N];

int main(){
	scanf("%d%d%d", &a, &b, &c);
	int n = a + b + c;
	for (int i = 0, a, b, c; i < n; ++ i){
		scanf("%d%d%d", &a, &b, &c);
		p[i] = {{a - b, a}, {b, c}};
	}
	std::sort(p, p + n);
	for (int i = 0; i < n; ++ i){
		sumleft[i] = (i ? sumleft[i - 1] : 0) + p[i].second.first;
		pq.push(p[i].second.second - p[i].second.first);
		if (pq.size() > b){
			sumleft[i] += pq.top();
			pq.pop();
		}
	}
	while (!pq.empty()){
		pq.pop();
	}
	for (int i = n - 1; ~i; -- i){
		sumright[i] = sumright[i + 1] + p[i].first.second;
		pq.push(p[i].second.second - p[i].first.second);
		if (pq.size() > a){
			sumright[i] += pq.top();
			pq.pop();
		}
	}
	ll ans = 0;
	for (int i = 0; i < n; ++ i){
		if (i + 1 >= b && n - i - 1 >= a){
			ans = std::max(ans, sumleft[i] + sumright[i + 1]);
		}
	}
	return printf("%lld\n", ans), 0;
}
