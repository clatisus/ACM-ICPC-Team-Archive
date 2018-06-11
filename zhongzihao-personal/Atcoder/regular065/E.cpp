#include<bits/stdc++.h>
#define ll long long

const int N = 100010;

std::map <ll, std::vector <std::pair <int, int>>> add, minus, add2, minus2;
std::queue <ll> q;
ll avai[N], n, a, b, _dis;
std::pair <ll, ll> p[N];

ll dis(std::pair <int, int> p1, std::pair <int, int> p2){
	return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

int find(int fa[], int u){
	return fa[u] == u ? u : fa[u] = find(fa, fa[u]);
}

int unite(int fa[], int u, int v){
	int _u = find(fa, u), _v = find(fa, v);
	fa[_u] = _v;
}

int main(){
	scanf("%lld%lld%lld", &n, &a, &b);
	avai[a] = avai[b] = true;
	q.push(a);
	q.push(b);
	for (int i = 1; i <= n; ++ i){
		scanf("%lld%lld", &p[i].first, &p[i].second);
		add[p[i].first + p[i].second].push_back({p[i].first, i});
		minus[p[i].first - p[i].second].push_back({p[i].first, i});
	}
	for (auto it = add.begin(); it != add.end(); ++ it){
		auto &u = it -> second;
		sort(u.begin(), u.end());
	}
	for (auto it = minus.begin(); it != minus.end(); ++ it){
		auto &u = it -> second;
		sort(u.begin(), u.end());
	}
	add2 = add;
	minus2 = minus;
	_dis = dis(p[a], p[b]);
	ll cnt = 0;
	while (!q.empty()){
		int i = q.front();
		q.pop();
		ll x = p[i].first, y = p[i].second;
		if (add.count(x + y + _dis)){
			auto &u = add[x + y + _dis], &v = add2[x + y + _dis];
			int l = upper_bound(u.begin(), u.end(), std::pair <int, int>{x, INT_MAX}) - u.begin();
			int r = lower_bound(u.begin(), u.end(), std::pair <int, int>{x + _dis, INT_MAX}) - u.begin() - 1;
			if (r >= l){
				cnt += r - l + 1;
			}
			for (auto it = upper_bound(v.begin(), v.end(), std::pair <int, int>{x, INT_MAX}); it -> first <= x + _dis && it != v.end();){
				if (!avai[it -> second]){
					q.push(it -> second);
					avai[it -> second] = true;
				}
				v.erase(it);
				it = upper_bound(v.begin(), v.end(), std::pair <int, int>{x, INT_MAX});
			}
		}
		if (add.count(x + y - _dis)){
			auto &u = add[x + y - _dis], &v = add2[x + y - _dis];
			int l = lower_bound(u.begin(), u.end(), std::pair <int, int>{x - _dis, 0}) - u.begin();
			int r = lower_bound(u.begin(), u.end(), std::pair <int, int>{x - 1, INT_MAX}) - u.begin() - 1;
			if (r >= l){
				cnt += r - l + 1;
			}
			for (auto it = lower_bound(v.begin(), v.end(), std::pair <int, int>{x - _dis, 0}); it -> first < x && it != v.end();){
				if (!avai[it -> second]){
					q.push(it -> second);
					avai[it -> second] = true;
				}
				v.erase(it);
				it = lower_bound(v.begin(), v.end(), std::pair <int, int>{x - _dis, 0});
			}
		}
		if (minus.count(x - y - _dis)){
			auto &u = minus[x - y - _dis], &v = minus2[x - y - _dis];
			int l = upper_bound(u.begin(), u.end(), std::pair <int, int>{x - _dis, INT_MAX}) - u.begin();
			int r = lower_bound(u.begin(), u.end(), std::pair <int, int>{x, INT_MAX}) - u.begin() - 1;
			if (r >= l){
				cnt += r - l + 1;
			}
			for (auto it = upper_bound(v.begin(), v.end(), std::pair <int, int>{x - _dis, INT_MAX}); it -> first <= x && it != v.end();){
				if (!avai[it -> second]){
					q.push(it -> second);
					avai[it -> second] = true;
				}
				v.erase(it);
				it = upper_bound(v.begin(), v.end(), std::pair <int, int>{x - _dis, INT_MAX});
			}
		}
		if (minus.count(x - y + _dis)){
			auto &u = minus[x - y + _dis], &v = minus2[x - y + _dis];
			int l = lower_bound(u.begin(), u.end(), std::pair <int, int>{x, 0}) - u.begin();
			int r = lower_bound(u.begin(), u.end(), std::pair <int, int>{x + _dis - 1, INT_MAX}) - u.begin() - 1;
			if (r >= l){
				cnt += r - l + 1;
			}
			for (auto it = lower_bound(v.begin(), v.end(), std::pair <int, int>{x, 0}); it -> first < x + _dis && it != v.end();){
				if (!avai[it -> second]){
					q.push(it -> second);
					avai[it -> second] = true;
				}
				v.erase(it);
				it = lower_bound(v.begin(), v.end(), std::pair <int, int>{x, 0});
			}
		}
	}
	printf("%lld\n", cnt >> 1);	
	return 0;
}
