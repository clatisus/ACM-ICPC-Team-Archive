#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <algorithm>

const int max_N = (int)2e5 + 21;

int n, k, a[max_N];

void testCase(){
	static int Case = 0;
	scanf("%d%d", &n, &k);
	for(int i=1;i<=n;++i) scanf("%d", a+i);
	while(k --){
		bool flag = false;
		for(int i=1;i<n;++i) if(flag |= (a[i]>a[i+1])) std::swap(a[i], a[i+1]);
		if(!flag) break;
	}
	printf("Case #%d:\n", ++ Case);
	for(int i=1;i<=n;++i) printf("%d\n", a[i]);
}

int main(){
	int T; scanf("%d", &T); while(T --) testCase();
	return 0;
} 
