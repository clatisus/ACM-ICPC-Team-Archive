#include <bits/stdc++.h>

const int max_N = 2e6 + 21;

const int mod = 1e9 + 7;

inline int qpow(int x,int k){
	int res=1;
	for(;k;x=1ll*x*x%mod,k>>=1)
		if(k&1){
			res=1ll*res*x%mod;
		}
	return res;
}

int n,k,vis[max_N],mu[max_N],pw[max_N];

std::vector<int>p;

int ans[max_N];

inline void jzp(int n){
	mu[1]=1;
	for(int x=2;x<=n;++x){
		if(!vis[x]){
			vis[x]=x;
			mu[x]=-1; 
			p.push_back(x);
		}
		for(auto&y:p){
			if(1ll*x*y>n)break;
			vis[x*y]=x;
			if(x % y==0){
				mu[y*x]=0;
				break;
			}
			mu[y*x]=-mu[y];
		}
	}
	for(int i=1;i<=n;++i)
		printf("%d\n",mu[i]);
}

int main(){
	scanf("%d%d",&n,&k);
	jzp(k);
	for(int i=0;i<=k;++i){
		pw[i]=qpow(i,n);
//		printf("%d\n",pw[i]);
	}
	for(int i=1;i<=k;++i){
		for(int j=0;j<=k;j+=i){
			int tmp=mu[i]*pw[j/i];
			if(tmp<0)tmp+=mod;
			ans[j]=(ans[j]+tmp)%mod;
			if(j+i<=k){
				ans[j+i]=(ans[j+i]-tmp+mod)%mod;
			}
		}
	}
	for(int i=1;i<=k;++i){
		ans[i]=(ans[i]+ans[i-1])%mod;
//		printf("%d\n",ans[i]);
	}
	int Ans=0;
	for(int i=1;i<=k;++i){
		Ans=(Ans+(ans[i]^i))%mod;
	}
	printf("%d\n",Ans);
	return 0;
}

