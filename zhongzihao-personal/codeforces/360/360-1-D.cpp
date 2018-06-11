#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
const int N=1<<20;
const int M=1000;
using namespace std;
typedef struct edge
{
	int u,v,length;
};
typedef vector<edge>vec;
typedef struct segment
{
	int left,right;
	vec edges;
};
edge edg[N];
int point[M],color[M],n,m,q;
segment seg[2*N];
bool flag;
bool compare(edge a,edge b)
{
	return a.length>b.length;
}
int find(int i)
{
	int j;
	if (point[i]==i)
		return i;
	j=find(point[i]);
	color[i]^=color[point[i]];
	cout<<"color[ "<<i<<" ]="<<color[i]<<endl;
	return point[i]=j; 
}
int unite(int u,int v)
{
	int i=find(u);
	int j=find(v);
	if (i==j)
	{
		if (color[u]==color[v])
		{
			flag=true;
			cout << "flag=" << flag << endl;
			return 2;
		}
		flag=false;
		return 1;
	}
	color[i]^=color[i]==color[j];
	cout<<"color["<<i<<"]="<<color[i]<<endl;
	point[i]=j;
	flag=false;
	return 0;
}
vec _merge(vec &a,vec &b)
{
	int i,state;
	vec ed,c;
	merge(a.begin(),a.end(),b.begin(),b.end(),back_inserter(c),compare);
	for (i=1;i<=n;i++)
	{
		point[i]=i;
		color[i]=0;
	}
	for (i=0;i<c.size();i++)
	{
		state=unite(c[i].u,c[i].v);
		if (state==2)
		{
			ed.push_back(c[i]);
			return ed;
		}
		if (!state)
			ed.push_back(c[i]);
	}
	return ed;
}
void build()
{
	int i;
	bool flag;
	for (i=(N<<1)-1;i>=N+m;i--)
	{
		seg[i].left=i-N+1;
		seg[i].right=i-N+2;
	}
	for (i=N+m-1;i>=N;i--)
	{
		seg[i].left=i-N+1;
		seg[i].right=i-N+2;
		seg[i].edges.push_back(edg[i-N+1]);
	}
	for (i=N-1;i;i--)
	{
		seg[i].left=seg[2*i].left;
		seg[i].right=seg[2*i+1].right;
		seg[i].edges=_merge(seg[2*i].edges,seg[2*i+1].edges);
	}
}
int solve (int left,int right)
{
	int l,r,i;
	vec ed;
	for (l=left+N-1,r=right+N;l<r;l/=2,r/=2)
	{
		if (l%2)
			ed=_merge(ed,seg[l++].edges);
		if (r%2)
			ed=_merge(ed,seg[--r].edges);
		/*cout << "l=" << l <<" r=" << r << endl;
		for (int j = 0; j < ed.size(); ++j)  
    		cout << "length=" << ed[j].length << endl;
    	cout << "flag=" << flag << endl;*/
	}
	if (flag)
		return ed[ed.size()-1].length;
	return -1;
}
int main()
{
	int i,j,l,r,ans[M],flag;
	scanf("%d%d%d",&n,&m,&q);
	for (i=1;i<=m;i++)
		scanf("%d%d%d",&edg[i].u,&edg[i].v,&edg[i].length);
	build();
	for (i=0;i<q;i++)
	{
		scanf("%d%d",&l,&r);
		ans[i]=solve(l,r);
	}
	for (i=0;i<q;i++)
		printf("%d\n",ans[i]);
	return 0;
}
