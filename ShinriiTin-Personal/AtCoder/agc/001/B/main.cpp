#include <bits/stdc++.h>

using ll = long long;

ll f(ll a,ll b){
	if(a>b)std::swap(a,b);
	return !a?-b:2*a*(b/a)+f(b%a,a);	
}

int main(){
	ll n,k;
	scanf("%lld%lld",&n,&k);
	ll ans=n+f(n-k,k);
	printf("%lld\n",ans);
	return 0;
}
