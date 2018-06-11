#include<bits/stdc++.h>
using namespace std;
const int N = 100010;
typedef vector <int> Tetra;
typedef struct point
{
	int degree, first;
	Tetra a,b;
};
typedef struct edge
{
	int next, to;
};
int cnt = 0, e = 1;
map <Tetra, int> m;
point points[N];
edge edges[N];
int search(Tetra t)
{
	if (m.count(t))
		return m[t];
	else
		return m[t] = cnt++;
}
void addedge(int u, int v)
{
	edges[++e].to = v;
	edges[e].next = points[u].first;
	points[u].first = e;
	edges[++e].to = u;
	edges[e].next = points[u].first;
	points[v].first = e;
}
void bfs(int i)

int main()
{
	int n, u, v;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d", &u, &v);
		addedge(u, v);
		points[u].degree++;
		points[v].degree++;
	}
}
