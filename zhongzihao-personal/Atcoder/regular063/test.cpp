#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <queue>
#include <set>
#include <map>
using namespace std;
#define MOD @
#define ADD(X,Y) ((X) = ((X) + (Y)%MOD) % MOD)
typedef long long i64; typedef vector<int> ivec; typedef vector<string> svec;
 
const int INFT = 1000000000;
 
struct segtree
{
	static const int DEPTH = 19;
	static const int N = 1 << DEPTH;
 
	int rmax[2 * N], dadd[2 * N];
 
	void init()
	{
		for (int i = 0; i < 2 * N; ++i) {
			rmax[i] = -INFT;
			dadd[i] = 0;
		}
	}
 
	void add(int qL, int qR, int p, int depth, int v)
	{
		int pL = (p << depth), pR = ((p + 1) << depth);
		if (pR <= qL || qR <= pL) return;
 
		if (qL <= pL && pR <= qR) {
			dadd[p] += v;
			rmax[p] += v;
			return;
		}
 
		add(qL, qR, p * 2, depth - 1, v);
		add(qL, qR, p * 2 + 1, depth - 1, v);
		rmax[p] = dadd[p] + max(rmax[p * 2], rmax[p * 2 + 1]);
	}
 
	void add(int qL, int qR, int v)
	{
	//	printf("[%d, %d] += %d\n", qL, qR, v);
		if (qL >= qR) return;
		add(qL + N, qR + N, 1, DEPTH, v);
	}
 
	int query(int qL, int qR, int p, int depth)
	{
		int pL = (p << depth), pR = ((p + 1) << depth);
		if (pR <= qL || qR <= pL) return -INFT;
 
		if (qL <= pL && pR <= qR) {
			return rmax[p];
		}
 
		dadd[p * 2] += dadd[p];
		rmax[p * 2] += dadd[p];
		dadd[p * 2 + 1] += dadd[p];
		rmax[p * 2 + 1] += dadd[p];
		dadd[p] = 0;
 
		return max(query(qL, qR, p * 2, depth - 1), query(qL, qR, p * 2 + 1, depth - 1));
	}
 
	int query(int qL, int qR)
	{
		return query(qL + N, qR + N, 1, DEPTH);
	}
 
	void set(int p, int v)
	{
		int cv = query(p, p + 1);
		add(p, p + 1, v - cv);
	}
};
 
int W, H, N;
int Xi[303030], Yi[303030];
 
void transpose()
{
	swap(W, H);
	for (int i = 0; i < N; ++i) swap(Xi[i], Yi[i]);
}
 
vector<int> ys;
 
int y_idx(int y)
{
	return lower_bound(ys.begin(), ys.end(), y) - ys.begin();
}
 
segtree seg;
 
int solve()
{
	// split by the line x=W/2
	vector<pair<int, int> > pts;
	for (int i = 0; i < N; ++i) {
		pts.push_back({ Yi[i], Xi[i] });
	}
	sort(pts.begin(), pts.end());
	pts.push_back({ H, 0 });
 
	stack<pair<int, int> > lst, rst; // (y, x)
	lst.push({ 0, W / 2 });
	rst.push({ 0, W / 2 });
 
	ys.clear();
	for (int i = 0; i < N; ++i) ys.push_back(Yi[i]);
	ys.push_back(0);
	ys.push_back(H);
 
	sort(ys.begin(), ys.end());
	ys.erase(unique(ys.begin(), ys.end()), ys.end());
 
	seg.init();
	for (int i = 0; i < ys.size(); ++i) seg.set(i, -ys[i]);
	seg.add(0, ys.size(), W);
 
	int ret = 0;
	for (int i = 0; i < pts.size(); ++i) {
		int y = pts[i].first, x = pts[i].second;
		int yi = y_idx(y);
	//	printf("%d: %d %d\n", i, seg.query(0, yi), y);
		ret = max(ret, seg.query(0, yi) + y);
 
		// update
		if (x <= W / 2) {
			// left
			int lastx = 0, lasty = y;
			while (!lst.empty() && lst.top().second < x) {
				seg.add(y_idx(lst.top().first), y_idx(lasty), lastx - x);
				lastx = lst.top().second;
				lasty = lst.top().first;
				lst.pop();
			}
			seg.add(y_idx(lst.top().first), y_idx(lasty), lastx - x);
			lst.push({ y, x });
		} else {
			// right
			int lastx = W, lasty = y;
			while (!rst.empty() && rst.top().second > x) {
				seg.add(y_idx(rst.top().first), y_idx(lasty), x - lastx);
				lastx = rst.top().second;
				lasty = rst.top().first;
				rst.pop();
			}
			seg.add(y_idx(rst.top().first), y_idx(lasty), x - lastx);
			rst.push({ y, x });
		}
	}
	return ret;
}
 
int main()
{
	scanf("%d%d%d", &W, &H, &N);
	for (int i = 0; i < N; ++i) {
		scanf("%d%d", Xi + i, Yi + i);
		Xi[i] *= 2;
		Yi[i] *= 2;
	}
	W *= 2;
	H *= 2;
 
	int ans = 0;
	ans = solve();
	transpose();
	ans = max(ans, solve());
	printf("%d\n", ans);
	return 0;
}
