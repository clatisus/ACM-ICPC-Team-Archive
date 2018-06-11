#include <vector>
#include <stdio.h>
#include <string.h>

int main(){
	auto testCase = [](){
		static int Case = 0;
		int n, m, k; scanf("%d%d%d", &n, &m, &k);
		std::vector<int> vec[n];
		for(int i=0, u, v;i<m;++i){
			scanf("%d%d", &u, &v);
			vec[u-1].push_back(v-1);
			if(u == v) continue;
			vec[v-1].push_back(u-1);
		}
		printf("Case #%d: ", ++ Case);
		if(n==1 || k==1){ puts("0"); return; }
		if(~k&1){ printf("%lld\n", 1ll*n*(n+1)/2-m); return; }
		int cnt[2] = {0};
		char iro[n]; memset(iro, -1, sizeof(char)*n);
		int q[n], t;
		iro[0] = 0, q[t = 0] = 0;
		for(int i=0;i<=t;++i){
			int x = q[i];
			for(auto&y:vec[x])
				if(iro[y] == -1){
					iro[y] = iro[x]^1;
					q[++ t] = y;
				}
				else if(iro[x] == iro[y]){
					printf("%lld\n", 1ll*n*(n+1)/2-m);
					return;
				}
			++ cnt[(int)iro[x]];
		}
		printf("%lld\n", 1ll*cnt[0]*cnt[1]-m);
	};

	int T; scanf("%d", &T); while(T --) testCase();
	return 0;
} 
