#include <bits/stdc++.h>
 
using ll = long long;
 
const int max_N = 1e5 + 21;

const ll inf = 2e10 + 1;
 
int n,ans;
 
bool vis[max_N];

int pri_tot,pri[max_N];
 
ll Norm[max_N],Pair[max_N];

int N_tot,P_tot,N_siz[max_N],P_siz[max_N];

inline void jzp(int n){
	for(int x=2;x<=n;++x){
		if(!vis[x])pri[++pri_tot]=x;
		for(int i=1;i<=pri_tot;++i){
			int y=pri[i];
			if((ll)x*y>n)break;
			vis[x*y]=1;
			if(!(x%y))break;
		}
	}
}
 
inline ll get_norm(ll x){
	for(int i=1;i<=pri_tot;++i){
		int y=pri[i];
		ll z=1ll*y*y*y;
		if(z>x)break;
		while(!(x%z))x/=z;
	}
	return x;
}
 
inline ll get_pair(ll x){
	ll res=1;
	for(int i=1;i<=pri_tot;++i){
		int y=pri[i];
		ll z=(ll)y*y*y;
		if(z<=x){
			while(!(x%z))x/=z;
			if(!(x%(y*y))){
				res*=y,x/=(y*y);
				if(res>=inf)return inf;
			}
			else if(!(x%y)){
				res*=(y*y),x/=y;
				if(res>=inf)return inf;
			}
		}
		else break;
	}
	ll y=std::sqrt(x);
	if(y*y==x){
		res*=y;
		return res>=inf?inf:res;
	}
	if(inf/x/x<res)return inf;
	return res*x*x;
}
 
int main(){
	jzp(1e5);
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		ll s; scanf("%lld",&s);
		Norm[i]=get_norm(s);
		Pair[i]=get_pair(s);
	}
	std::sort(Norm+1,Norm+1+n);
	std::sort(Pair+1,Pair+1+n);
	for(int i=1;i<=n;++i){
		if(Norm[i]!=Norm[i-1])Norm[++N_tot]=Norm[i];
		++N_siz[N_tot];
		if(Pair[i]!=Pair[i-1])Pair[++P_tot]=Pair[i];
		++P_siz[P_tot];
	}
	int i=1,j=1;
	while(i<=N_tot||j<=P_tot){
		if(i<=N_tot&&j<=P_tot&&Norm[i]==Pair[j]){
			if(Norm[i]!=1)ans+=std::max(N_siz[i],P_siz[j]);
			++i,++j;
		}
		else if(i>N_tot||(j<=P_tot&&Norm[i]>Pair[j]))
			ans+=P_siz[j++];
		else
			ans+=N_siz[i++];
	}
	ans>>=1;
	if(Norm[1]==1)++ans;
	printf("%d\n",ans);
	return 0;
}
