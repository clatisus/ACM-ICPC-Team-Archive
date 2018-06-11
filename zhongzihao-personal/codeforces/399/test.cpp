#include<bits/stdc++.h>

const int N = 100;

int seg[N];
std::map <std::pair <int, std::set <int>>, int> Hash;

int solve(int n, std::set <int> s){
	if (Hash.count({n, s})){
		return Hash[{n, s}];
	}
	std::set <int> ans;
	for (int i = 1; i <= n; ++ i){
		if (!s.count(i)){
			s.insert(i);
			ans.insert(solve(n - i, s));
			s.erase(i);
		}
	}
	for (int i = 0; ; ++ i){
		if (!ans.count(i)){
			return Hash[{n, s}] = i;
		}
	}
}

int main(){
	for (int i = 1; i <= 60; ++ i){
		std::set <int> s;
		seg[i] = solve(i, s);
		std::cout << seg[i] << ", ";
	}
	return 0;
}
