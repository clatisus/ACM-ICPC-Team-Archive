#include<bits/stdc++.h>
const int INF = 1e9; 
const int N = 300010;
const int MAX = 19;
using namespace std;

struct segment{
	int lazy, rmax;
};
	
int w, h, n, x[N], y[N];
segment seg[1 << MAX + 1];
vector <pair <int, int>> p;
vector <int>_y;
stack <pair <int, int>> ls, rs;

int ysit(int y){
	return lower_bound(_y.begin(), _y.end(), y) - _y.begin();
}

void build(){
	for (int i = 1 << MAX; i < (1 << MAX) + _y.size(); i ++)
		seg[i].rmax = w - _y[i - (1 << MAX)];
	for (int i = (1 << MAX) + _y.size(); i < 1 << MAX + 1; i ++)
		seg[i].rmax = -INF;
	for (int i = (1 << MAX) - 1; i; i --)
		seg[i].rmax = max(seg[i << 1].rmax, seg[(i << 1) + 1].rmax);
}

void add(int left, int right, int point, int depth, int v){
	int l = point << depth, r = point + 1 << depth;
	if (depth){
		seg[point << 1].rmax += seg[point].lazy;
		seg[point << 1].lazy += seg[point].lazy;
		seg[(point << 1) + 1].rmax += seg[point].lazy;
		seg[(point << 1) + 1].lazy += seg[point].lazy;
	}
	seg[point].lazy = 0;
	if (l == left && r == right + 1){
		seg[point].rmax += v;
		seg[point].lazy += v;
		return;
	}
	int mid = l + r >> 1;
	if (right < mid)
		add(left, right, point << 1, depth - 1, v);
	else if (left >= mid)
		add(left, right, (point << 1) + 1, depth - 1, v);
	else{
		add(left, mid - 1, point << 1, depth - 1, v);
		add(mid, right, (point << 1) + 1, depth - 1, v);
	}
	seg[point].rmax = max(seg[point << 1].rmax, seg[(point << 1) + 1].rmax);
}

void add(int left, int right, int v){
	if (left > right)
		return;
	add(left + (1 << MAX), right + (1 << MAX), 1, MAX, v);
}

int query(int left, int right, int point, int depth){
	int l = point << depth, r = point + 1 << depth;
	if (depth){
		seg[point << 1].rmax += seg[point].lazy;
		seg[point << 1].lazy += seg[point].lazy;
		seg[(point << 1) + 1].rmax += seg[point].lazy;
		seg[(point << 1) + 1].lazy += seg[point].lazy;
	}
	seg[point].lazy = 0;
	if (l == left && r == right + 1)
		return seg[point].rmax;
	int mid = l + r >> 1, ret = -INF;
	if (right < mid)
		return query(left, right, point << 1, depth - 1);
	if (left >= mid)
		return query(left, right, (point << 1) + 1, depth - 1);
	ret = max(ret, query(left, mid - 1, point << 1, depth - 1));
	ret = max(ret, query(mid, right, (point << 1) + 1, depth - 1));
	return ret;
}

int query(int left, int right){
	if (left > right)
		return -INF;
	return query(left + (1 << MAX), right + (1 << MAX), 1, MAX);
}

int solve(){
	memset(seg, 0, sizeof(seg));
	p.clear();
	_y.clear();
	while (!ls.empty())
		ls.pop();
	while (!rs.empty())
		rs.pop();
	ls.push({0, w / 2});
	rs.push({0, w / 2});
	for (int i = 0; i < n; i ++)
		p.push_back({y[i], x[i]});
	sort(p.begin(), p.end());
	p.push_back({h, 0});
	for (int i = 0; i < n; i ++)
		_y.push_back(y[i]);
	_y.push_back(0);
	_y.push_back(h);
	sort(_y.begin(), _y.end());
	_y.erase(unique(_y.begin(), _y.end()), _y.end());
	build();
	int ret = 0;
	for (int i = 0; i < p.size(); i ++){
		int X = p[i].second, Y = p[i].first;
		ret = max(ret, query(0, ysit(Y) - 1) + Y);
		if (X <= w / 2){
			int lastx = 0, lasty = Y;
			while (!ls.empty() && ls.top().second < X){
				add(ysit(ls.top().first), ysit(lasty) - 1, lastx - X);
				lastx = ls.top().second;
				lasty = ls.top().first;
				ls.pop();
			}
			add(ysit(ls.top().first), ysit(lasty) - 1, lastx - X);
			ls.push({Y, X});
		}
		else{
			int lastx = w, lasty = Y;
			while (!rs.empty() && rs.top().second > X){
				add(ysit(rs.top().first), ysit(lasty) - 1, X - lastx);
				lastx = rs.top().second;
				lasty = rs.top().first;
				rs.pop();
			}
			add(ysit(rs.top().first), ysit(lasty) - 1, X - lastx);
			rs.push({Y, X});
		}
	}
	return ret;
}

int main()
{
	scanf("%d%d%d", &w, &h, &n);
	w *= 2;
	h *= 2;
	for (int i = 0; i < n; i ++){
		scanf("%d%d", &x[i], &y[i]);
		x[i] *= 2;
		y[i] *= 2;
	}
	int ans = solve();
	swap(w, h);
	for (int i = 0; i < n; i ++)
		swap(x[i], y[i]);
	ans = max(ans, solve());
	return printf("%d\n", ans), 0;
}
