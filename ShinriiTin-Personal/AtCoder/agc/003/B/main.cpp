#include <bits/stdc++.h>

using ll = long long;

const int max_N = 1e5 + 21;

int n,A[max_N];

ll ans;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",A+i);
	for(int i=1,j;i<=n;++i){
		if(A[i]&1){
			for(j=i+1;j<=n&&A[j]>=2&&(~A[j]&1);++j);
			if(A[j]&1){
				ll tmp=0;
				for(int k=i;k<=j;++k)tmp+=A[k];
				ans+=(tmp>>1);
				i=j;
			}
			else ans+=(A[i]>>1);
		}
		else ans+=(A[i]>>1);
	}
	printf("%lld\n",ans);
	return 0;
}

