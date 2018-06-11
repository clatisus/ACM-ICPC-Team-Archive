#include<bits/stdc++.h>
const int N = 400100;

struct point
{
	int first;
	bool visited;
};

struct edge
{
	int to, next;
};

int n, m;
edge edges[N];
point points[N];

int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		addedge(a, b);
	}
}
