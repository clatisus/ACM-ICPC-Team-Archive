#include <bits/stdc++.h>

using ll = long long;

const int max_N = 1e5 + 21;

int n,q,top;

ll A,st[max_N],t[max_N],ans[max_N];

int main(){
	scanf("%d%d",&n,&q);
	st[++top]=n;
	for(int i=1;i<=q;++i){
		scanf("%lld",&A);
		while(top&&st[top]>=A)--top;
		st[++top]=A;
	}
	t[top]=1;
	for(int i=top;i;--i){
		ll k=st[i];
		while(k>st[1]){
			int j=std::lower_bound(st+1,st+1+top,k)-st-1;
			t[j]+=t[i]*(k/st[j]);
			k%=st[j];
		}
		ans[k]+=t[i];
	}
	for(int i=n;i;--i)ans[i]+=ans[i+1];
	for(int i=1;i<=n;++i)printf("%lld\n",ans[i]);
	return 0;
}
