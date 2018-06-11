#include<bits/stdc++.h>

const int N = 100010;

int n;
std::vector <int> vec[N], __vec;

int dfs(int i){
	__vec.clear();
	for (int j = 0; j < vec[i].size(); ++ j){
		__vec.push_back(dfs(vec[i][j]));
	}
	if (!__vec.size()){
		return 0;
	}
	sort(__vec.begin(), __vec.end());
	for (int j = 0; j < __vec.size(); ++ j){
		__vec[i] += __vec.size() - j;
	}
	sort(__vec.begin(), __vec.end());
	return __vec[__vec.size() - 1];
}

int main(){
	scanf("%d", &n);
	for(int i = 2, x; i <= n; ++ i){
		scanf("%d", &x);
		vec[x].push_back(i);
	}
	printf("%d\n", dfs(1));
	return 0;
}
