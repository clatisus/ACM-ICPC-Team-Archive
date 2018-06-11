#include<bits/stdc++.h>
using namespace std;
const int N = 100010;
int n, m;
pair <int, int> h[N];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		h[i].first = x;
		h[i].second = y;
	}
	int ans = h[0].first + h[0].second - 1;
	ans = max(ans, n - h[m - 1].first + h[m - 1].second);
	for (int i = 1; i < m; i++)
	{
		if (h[i].first - h[i - 1].first < abs(h[i].second - h[i - 1].second))
			return printf("IMPOSSIBLE"), 0;
		if (h[i].first - h[i - 1].first == 1)
		{
			ans = max(h[i].second, ans);
			ans = max(h[i - 1].second, ans);
		}
		else
			ans = max(ans, (abs(h[i].first - h[i - 1].first) + h[i].second + h[i - 1].second) / 2);
	}
	printf("%d", ans);
	return 0;
}
