/*
首先任意两个串的编辑距离就是长度之和减去两倍的最长公共子序列长度
 
要满足题中的性质，首先要是按照kruscal算法求最小生成树中的某个时刻的局面，但这个条件还不充分

如果某个时刻。连通块a中的所有边都被枚举了， 那么它一定是一个合法的最终局面中可能存在的集合，否则可能必须以更大的连通块的形式出现

对所有边排序做kruscal，顺便用并查集维护连通块大小和块中已经枚举过的边数，合并两个集合时分别判断其是否可以独立出现，是则方案加一

时间复杂度O(n^2)加上排序复杂度O(n^2logn) 
*/ 

#include <bits/stdc++.h>

const int max_N = 400 + 21;
const int max_L = 20 + 21;
const int mod = (int)1e9 + 7;

int n, dp[max_L][max_L], tot;

std::pair<int, int> edge[max_N*max_N];

char s[max_N][max_L];

int f[max_N], ans[max_N];

int siz[max_N], edges[max_N];

std::vector<int> vec;

bool vis[max_N], ok[max_N];

int find(int x){
	int r = x;
	while(f[r]!=r) r = f[r];
	for(int p;x!=r;x=p){
		p = f[x];
		f[x] = r;
	}
	return r;
}

bool merge(int a, int b){
	a = find(a), b = find(b);
	if(a == b){
		++ edges[a];
		if(!vis[a]){
			vis[a] = true;
			vec.push_back(a);
		}
		return false;
	}
	
	if(ok[a]) ++ ans[a];
	if(ok[b]) ++ ans[b];
	ans[b] = 1ll*ans[a]*ans[b]%mod;
	
	f[a] = b;
	siz[b] += siz[a];
	edges[b] = edges[a]+edges[b]+1;
	ok[b] = false;
	if(!vis[b]){
		vis[b] = true; 
		vec.push_back(b);
	} 
	
	return true;
}

int getDis(char* a, char* b){
	int n = strlen(a), m = strlen(b);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(a[i-1]==b[j-1]){
				dp[i][j] = dp[i-1][j-1] + 1;	
			}
			else{
				dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
			}
	return n + m - 2*dp[n][m];
}

void testCase(){
	scanf("%d", &n);
	for(int i=1;i<=n;++i) scanf("%s", s[i]);
	tot = 0;
	for(int i=1;i<=n;++i)
		for(int j=i+1;j<=n;++j){
			edge[++ tot] = {getDis(s[i], s[j]), i*max_N+j};
		}
	std::sort(edge+1, edge+1+tot);
	for(int i=1;i<=n;++i){
		f[i] = i;
		ans[i] = edges[i] = 0;
		siz[i] = 1;
		vis[i] = true;
		vec.push_back(i);
	}
	for(int i=1,cnt=0;i<=tot;++i){
		if(edge[i].first>edge[i-1].first){
			for(auto&x:vec){
				vis[x] = false;
				if(find(x)!=x) continue;
				if(siz[x]*(siz[x]-1)/2==edges[x]){
					ok[x] = true;
				}
			}
			vec.clear();
		}
		int u = edge[i].second/max_N;
		int v = edge[i].second%max_N;
		if(merge(u, v) && ++ cnt == n-1) break;
	}
	printf("%d\n", (ans[find(1)]+1)%mod);
}

int main(){
	int T; scanf("%d", &T); while(T --) testCase();
	return 0;
}
