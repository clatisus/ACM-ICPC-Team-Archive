#include <bits/stdc++.h>

const int max_N = (1<<16) + 21;

std::vector<int> prime;

bool vis[max_N];

void init(){
	for(int x=2;x<max_N;++x){
		if(!vis[x]) prime.push_back(x);
		for(auto&y:prime){
			if(1ll*x*y>=max_N) break;
			vis[x*y] = true;
			if(!(x%y)) break;
		}
	}
}

int calc(int x){
	int ans = 1;
	for(auto&y:prime){
		if(1ll*y*y>x) break;
		if(!(x%y)){
			ans = y;
			while(!(x%y)) x /= y;
		}
	}
	if(x>1) return x;
	return ans;
}

int main(){
	init();
//	printf("%d\n", (int)prime.size()); 
	
	int n;
	while(true){
		scanf("%d", &n);
		if(!n) break;
		printf("%d\n", INT_MAX/calc(n));
	}
	return 0;
}
