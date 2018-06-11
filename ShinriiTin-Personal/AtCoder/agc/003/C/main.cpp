#include <bits/stdc++.h>

const int max_N = 1e5 + 21;

int n,ans;

std::pair<int,int>A[max_N];

int main(){
	scanf("%d",&n);
	for(int i=1,a;i<=n;++i){
		scanf("%d",&a);
		A[i]={a,i};
	}
	std::sort(A+1,A+1+n);
	for(int i=1;i<=n;++i)
		if((i^A[i].second)&1)++ans;
	printf("%d\n",ans>>1);
	return 0;
}
