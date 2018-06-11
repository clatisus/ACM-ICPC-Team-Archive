#include <bits/stdc++.h>

int main(){
	auto testCase = [&](){
		static int Case = 0;
		
		const int max_L = 4000 + 21;
		
		static char a[max_L];
		
		int n, ans = 0;
		
		scanf("%d", &n);
		
		int st[n<<1|1] = {0}, ed[n<<1] = {0};
		
		std::vector<int> vec[(n<<1)+2], _vec[(n<<1)+2];
		
		auto addEdge = [&](int u, int v){
			vec[u].push_back(v);
			_vec[v].push_back(u);
		};
		
		assert(n<=30);
		
		for(int i=0;i<(n<<1);++i){
			scanf("%s", a+st[i]);
			st[i+1] = ed[i] = st[i]+strlen(a+st[i]);
			
		}
		
		assert(st[n<<1]<=400);
		
		
		
		printf("Case #%d: %d\n", ++ Case, ans);
	};
	
	int T; scanf("%d", &T); while(T --) testCase();

	return 0;
}
