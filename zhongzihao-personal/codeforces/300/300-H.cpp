#include<bits/stdc++.h>
using namespace std;
const int N = 100010;
const int NN = N * 20;

struct point
{
	int first;
	bool visited, flag;
};

struct edge
{
	int next, to;
};

struct interval
{
	int l, r;
	vector <int> t;
};

int cnt = 0, num = 0, total, t, T, n, m, code[N], l[N], r[N], type[NN], dfn[NN], low[NN];
bool choice[NN];
point p[NN], p1[NN];
edge e[N * 40], e1[N * 40];
stack <int> s;
vector <int> v;
map <int, int> Hash;

void push(int n)
{
	if (n >= 0 && n <= T)
		v.push_back(n);
}

void addedge(int u, int v, point *_p, edge *_e)
{
	_e[++cnt].next = _p[u].first;
	_e[cnt].to = v;
	_p[u].first = cnt;
}

void addEdge(int u, int v)
{
	addedge(u, v, p, e);
	addedge(v ^ 1, u ^ 1, p, e);
}

void tarjan(int i)
{
	s.push(i);
	p[i].flag = true;
	dfn[i] = low[i] = ++cnt;
	p[i].visited = true; 
	for (int j = p[i].first; j; j = e[j].next)
	{
		if (!p[e[j].to].visited)
			tarjan(e[j].to);
		if (p[e[j].to].flag)
			low[i] = min(low[i], low[e[j].to]);
	}
	if (low[i] == dfn[i])
	{
		total++;
		while (s.top() != i)
		{
			type[s.top()] = total;
			p[s.top()].flag = false;
			s.pop();
		}
		type[s.top()] = total;
		p[s.top()].flag = false;
		s.pop();
	}
}

void dfs(int i)
{
	p[i].visited = false;
	for (int j = p[i].first; j; j = e[j].next)
	{
		if (type[i] != type[e[j].to])
			addedge(type[e[j].to], type[i], p1, e1);
		if (p[e[j].to].visited)
			dfs(e[j].to);
	}
}
		
void toposort(int i)
{
	p1[i].visited = true; 
	for (int j = p1[i].first; j; j = e1[j].next)
		if (!p1[e1[j].to].visited)
			toposort(e1[j].to);
	s.push(i);
}

void dfs1(int i)
{
	if (p1[i].flag && !choice[i])
		return; 
	p1[i].flag = true;
	choice[i]= false;
	for (int j = p1[i].first; j; j = e1[j].next)
		dfs1(e1[j].to);
}

int main_main()
{
	scanf("%d%d", &t, &T);
	scanf("%d%d", &n, &m);
	push(0), push(t), push(T);
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d", &l[i], &r[i]);
		push(l[i]), push(r[i]), push(t - r[i]), push(t - l[i]);// push(T - l[i]), push(T - r[i]);
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	num = v.size();
	for (int i = 0; i < 2 * num - 2; i += 2)
	{
		addEdge(i, i + 2);
		addEdge(i + 2 * num, i + 2 * num + 2);
	}
	int j = num - 1;
	for (int i = 0; i < num; i++)
	{
		while (v[j] + v[i] >= t && j >= 0)
			j--;
		if (j < 0)
			break;
		addEdge(2 * i, 2 * j + 2 * num ^ 1);
		addEdge(2 * num + 2 * i, 2 * j ^ 1);
	}
	j = num - 1;
	for (int i = 0; i < num; i++)
	{
		while (v[j] + v[i] >= T && j >= 0)
			j--;
		if (j < 0)
			break;
		addEdge(2 * i ^ 1, 2 * j + 2 * num);
		addEdge(2 * num + 2 * i ^ 1, 2 * j);
	}
	for (int i = 0; i < num; i++)
		Hash[v[i]] = 2 * i;
	for (int i = 0; i < n; i++)
		if (Hash.count(r[i]))
		{
			addEdge(4 * num + 2 * i, Hash[r[i]]);
			addEdge(4 * num + 2 * i ^ 1, Hash[r[i]] + 2 * num);
		}
	for (int i = 0; i < n; i++)
	{
		if (l[i] > T)
			return printf("IMPOSSIBLE"), 0;
		if (Hash.count(l[i]) && Hash[l[i]])
		{
			addEdge(4 * num + 2 * i, Hash[l[i]] - 2 ^ 1);
			addEdge(4 * num + 2 * i ^ 1, Hash[l[i]] - 2 + 2 * num ^ 1);
		}
	}
	for (int i = 0, u, v; i < m; i++)
	{
		scanf("%d%d", &u, &v);
		addEdge(4 * num + 2 * u - 2, 4 * num + 2 * v - 2 ^ 1);
		addEdge(4 * num + 2 * u - 2 ^ 1, 4 * num + 2 * v - 2);
	}
	total = 0;
	cnt = 0;
	for (int i = 0; i < 4 * num + 2 * n; i++)
		if (!p[i].visited)
			tarjan(i);
	cnt = 0;
	for (int i = 0; i < 4 * num + 2 * n; i++)
		if (p[i].visited)
			dfs(i);
	for (int i = 0; i < 4 * num + 2 * n; i += 2)
		//cout << p[i].type << ' ' << p[i ^ 1].type << endl;
		if (type[i] == type[i ^ 1])
			return printf("IMPOSSIBLE"), 0;
		else
		{
			code[type[i]] = type[i ^ 1];
			code[type[i ^ 1]] = type[i];
		}
	for (int i = 1; i <= total; i++)
		if (!p1[i].visited)
			toposort(i);
	while (!s.empty())
	{
		if (p1[s.top()].flag)
		{
			s.pop();
			continue;
		}
		p1[s.top()].flag = true;
		choice[s.top()] = true;
		dfs1(code[s.top()]);
		s.pop();
	}
	int l1 = 0, r1 = INT_MAX, l2 = 0, r2 = INT_MAX;
	for (int i = 0; i < n; i++)
		if (choice[type[2 * i + 4 * num]])
		{
			l1 = max(l1, l[i]);
			r1 = min(r1, r[i]);
		}
		else
		{
			l2 = max(l2, l[i]);
			r2 = min(r2, r[i]);
		}
	int n1 = l1, n2 = l2;
	if (n1 + n2 < t)
	{
		n1 = min(r1, T - n2);
		if (n1 + n2 < t)
		n2 = t - n1;
	}
	printf("POSSIBLE\n%d %d\n", n1, n2);
	for (int i = 0; i < n; i++)
		choice[type[2 * i + 4 * num]] ? putchar('1') : putchar('2');
	putchar('\n');
	return 0;
}
const int main_stack=16;  
char my_stack[128<<20];  
int main()
{  
  __asm__("movl %%esp, (%%eax);\n"::"a"(my_stack):"memory");  
  __asm__("movl %%eax, %%esp;\n"::"a"(my_stack+sizeof(my_stack)-main_stack):"%esp");  
  main_main();  
  __asm__("movl (%%eax), %%esp;\n"::"a"(my_stack):"%esp");  
  return 0;  
}
