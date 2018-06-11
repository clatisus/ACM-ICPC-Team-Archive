#include<cstdio>
#include<cstring>
#include<algorithm>

char s[1000][1010],t[1010];

int dp[1010][1001],a[1000],p[1000],f[1000],c[20],n;
bool b[1001];int len[1000],l;

inline int cost(int i,int j,int x){ return x||j<l?c[x]:0; }
inline void umax(int&m,int u){ u>m&&(m=u); }

void sort(int d)
{
	static int b[10][1000],c[1000],l[10];
	int i,j,k=0;
	for(i=0;i<10;i++)l[i]=0;
	for(i=0;i<n;i++)
		j=s[a[i]][d]-'0',
			b[j][l[j]++]=i;
	for(i=9;i>=0;i--)
		for(j=0;j<l[i];j++)
			c[k++]=b[i][j];
	for(i=0;i<n;i++)
		p[i]=a[i];
	for(i=0;i<n;i++)
		a[i]=p[c[i]];
	for(i=0;i<n;i++)
		f[a[i]]=i;
}

int main()
{
	int i,j,k,m,x,sum,cnt;
	scanf("%s%d",t,&n);
	l=(m=strlen(t))-1;
	std::reverse(t,t+m);
	while(m<=1001)t[m++]='0';
	for(i=0;i<n;i++)
	{
		scanf("%s",s[i]);
		len[i]=j=strlen(s[i]);
		std::reverse(s[i],s[i]+j);
		while(j<=1001)
			s[i][j++]='0';
		a[i]=i;
	}

	for(i=0;i<10;i++)scanf("%d",c+i);
	for(i=0;i<10;i++)c[i+10]=c[i];

	for(i=0;i<m;i++)
	{
		sort(i);
		for(j=0;j<=n;j++)dp[i][j]=-1.1e9;
		for(x=i==l?1:0;x<10;x++)
		{
			if(t[i]!='?'&&t[i]!=x+'0')continue;
			sum=cnt=k=0;
			for(j=0;j<n;j++)
			{
				sum+=cost(a[j],i,s[a[j]][i]-'0'+x);
				if(s[a[j]][i]-'0'+x>9)
					k=j+1,b[f[a[j]]]=true,cnt++;
				else b[f[a[j]]]=false;
			}
			if(!i)umax(dp[i][k],sum);
			else{
				if(k==cnt)umax(dp[i][k],sum+dp[i-1][0]);
				else return 1;
				for(j=0;j<n;j++)
				{
					if(s[p[j]][i]-'0'+x==9)
					{
						b[f[p[j]]]=true;
						cnt++;
					}
					sum-=cost(p[j],i,s[p[j]][i]-'0'+x);
					sum+=cost(p[j],i,s[p[j]][i]-'0'+x+1);
					while(b[k])k++;
					if(k==cnt)
						umax(dp[i][k],sum+dp[i-1][j+1]);
					else return 1;
				}
			}
		}
	}

	printf("%d\n",dp[m-1][0]);
}
