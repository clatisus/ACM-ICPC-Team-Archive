#include<bits/stdc++.h>
using namespace std;
const int N = 100010;

struct point
{
	int num, first, left, right;
	bool visited, odd;
};

struct edge
{
	int next, to;
};

int cnt = 1, n, k;
edge e[N << 1];
point p[N];

void addedge(int u, int v)
{
	e[++ cnt].next = p[u].first;
	p[u].first = cnt;
	e[cnt].to = v;
	e[++ cnt].next = p[v].first;
	p[v].first = cnt;
	e[cnt].to = u;
}

void dfs1(int i)
{
	p[i].visited = true;
	if (~p[i].num && p[i].odd != (p[i].num & 1))
	{
		printf("No\n");
		exit(0);
	}
	for (int j = p[i].first; j; j = e[j].next)
	{
		int x = e[j].to;
		if (p[x].visited)
			continue;
		p[x].odd = !p[i].odd;
		dfs1(x);
		p[i].left = max(p[i].left, p[x].left - 1);
		p[i].right = min(p[i].right, p[x].right + 1);
	}
	if (p[i].left > p[i].right)
	{
		printf("No\n");
		exit(0);
	}
}

void dfs2(int i)
{
	p[i].visited = true;
	for (int j = p[i].first; j; j = e[j].next)
	{
		int x = e[j].to;
		if (p[x].visited)
			continue;
		if (p[i].num - 1 >= p[x].left && p[i].num - 1 <= p[x].right)
			p[x].num = p[i].num - 1;
		else
			p[x].num = p[i].num + 1;
		dfs2(x);
	}
}
		
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++)
	{
		p[i].num = -1;
		p[i].left = -1e9;
		p[i].right = 1e9;
	}
	for (int i = 0, u, v; i < n - 1; i ++)
	{
		scanf("%d%d", &u, &v);
		addedge(u, v);
	}
	scanf("%d", &k);
	int root;
	for (int i = 0, x, num; i < k; i ++)	
	{
		scanf("%d%d", &x, &num);
		p[x].num = num;
		p[x].left = num;
		p[x].right = num;
		root = x;
	}
	p[root].odd = p[root].num & 1;
	dfs1(root);
	for (int i = 1; i <= n; i ++)
		p[i].visited = false;
	dfs2(root);
	printf("Yes\n");
	for (int i = 1; i <= n; i ++)
		printf("%d\n", p[i].num);
	return 0;
}
