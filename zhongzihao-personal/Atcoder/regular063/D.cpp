#include<bits/stdc++.h>
const int N = 100010;

int n, t, a[N], max[N];

int main()
{
	scanf("%d%d", &n, &t);
	for (int i = 1; i <= n; i ++)
		scanf("%d", &a[i]);
	for (int i = n; i; i --)
	{
		max[i] = max[i + 1];
		if (a[i] > max[i])
			max[i] = a[i];
	}
	for (int i = 1; i <= n; i ++)
		a[i] = max[i] - a[i];
	int ans = 0;
	for (int i = 1; i <= n; i ++)
		if (ans < a[i])
			ans = a[i];
	int cnt = 0;
	for (int i = 1; i <= n; i ++)
		if (a[i] == ans)
			cnt ++;
	return printf("%d\n", cnt), 0;
}
