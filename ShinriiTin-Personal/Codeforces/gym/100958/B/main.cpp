#include <bits/stdc++.h>

const int max_N = 55;

const int mod = 1e9 + 7;

int n,m,a[max_N][max_N];

char s[max_N];

int f[max_N][max_N][max_N];

int g[max_N][29];

int main(){
	scanf("%d", &n);
	for(int i=1;i<=n;++i){
		scanf("%s", s + 1);
		int len = strlen(s + 1);
		for(int j=1;j<=len;++j)
			if(s[j] == '?')
				a[i][j] = -1;
			else
				a[i][j] = s[j] - 'a' + 1;	
		m = std::max(m, len);
	}
	for(int i=1;i<=n;++i)f[m+1][i][i]=1;
	for(int len=m;len;--len)
		for(int l=1;l<=n;++l){
			memset(g,0,sizeof(g));
			for(int i=0;i<=27;++i)g[l-1][i]=1;
			for(int r=l;r<=n;++r){
				int lo,hi;
				if(~a[r][len])lo=hi=a[r][len]+1;
				else lo=2,hi=27;
				for(int k=lo;k<=hi;++k)
					for(int i=r;i>=l;--i){
						if(~a[i][len]&&a[i][len]!=k-1)break;
						g[r][k]=(g[r][k]+1ll*g[i-1][k-1]*f[len+1][i][r])%mod;
					}
				for(int i=1;i<=27;++i)g[r][i]=(g[r][i]+g[r][i-1])%mod;
				f[len][l][r]=g[r][27];
			}
		}
	printf("%d\n", f[1][1][n]);
	return 0;
}
