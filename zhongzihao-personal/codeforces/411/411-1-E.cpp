#include<bits/stdc++.h>

std::vector <std::pair <int, int>> solve(int n, int begin){
	std::vector <std::pair <int, int>> ret, vec;
	if (n % 4 == 1){
		vec = solve(n - 1, begin + 1);
		for (auto u : vec){
			if ((begin - u.first & 1) && u.second - u.first == 1){
				ret.push_back({begin, u.first});
				ret.push_back({u.first, u.second});
				ret.push_back({begin, u.second});
			}
			else{
				ret.push_back({u.first, u.second});
			}
		}
		return ret;
	}
	if (n == 4){
		return {{begin, begin + 1}, {begin + 2, begin + 3}, {begin, begin + 2}, {begin + 1, begin + 3}, {begin + 0, begin + 3}, {begin + 1, begin + 2}};
	}
	vec = solve(n - 4, begin + 4);
	ret = {{begin, begin + 1}, {begin + 2, begin + 3}, {begin, begin + 2}, {begin + 1, begin + 3}, {begin + 0, begin + 3}, {begin + 1, begin + 2}};
	for (auto u : vec){
		if ((begin - u.second & 1) && u.second - u.first == 1){
			for (int i = 0; i < 4; ++ i){
				ret.push_back({begin + i, u.first});
			}
			ret.push_back({u.first, u.second});
			for (int i = 3; i >= 0; -- i){
				ret.push_back({begin + i, u.second});
			}
		}
		else{
			ret.push_back({u.first, u.second});
		}
	}
	return ret;
}

int main(){
	int n;
	scanf("%d", &n);
	if (n == 1){
		return printf("YES\n"), 0;
	}
	if (n % 4 == 2 || n % 4 == 3){
		return printf("NO\n"), 0;
	}
	std::vector <std::pair <int, int>> ans = solve(n, 1);
	printf("YES\n");
	for (auto u : ans){
		printf("%d %d\n", u.first, u.second);
	}
	return 0;
}
