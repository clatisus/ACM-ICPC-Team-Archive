#include <bits/stdc++.h>

const int max_N = 100 + 21;

int n,a[max_N<<1],ans;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=2*n;++i)
		scanf("%d",a+i);
	std::sort(a+1,a+1+2*n);
	for(int i=1;i<=2*n;i+=2)
		ans+=a[i];
	printf("%d\n",ans);
	return 0;
}
