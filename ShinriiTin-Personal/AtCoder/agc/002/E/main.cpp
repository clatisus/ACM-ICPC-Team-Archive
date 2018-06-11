#include <bits/stdc++.h>

const int max_N = 1e5 + 21;

int n,a[max_N];

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",a+i);
	std::sort(a+1,a+1+n,[&](int x,int y){return x>y;});
	int i=1;
	while(i<=n&&i<a[i]&&i<a[i+1])++i;
	--i;
	int x=a[i+1]-i-1;
	int r=i; while(r<n&&a[r+1]>i)++r;
	int y=r-i-1;
	if(x&1||y&1)puts("First");
	else puts("Second");
	return 0;
}

