#include<bits/stdc++.h>

typedef std::pair <int, int> pii;

void solve(int n){
	if (n == 3){
		printf("0 0\n1 0\n0 1\n");
		return;
	}
	if (n == 4){
		printf("0 0\n1 0\n1 1\n0 1\n");
		return;
	}
	if (n == 5){
		printf("0 0\n2 0\n1 2\n1 1\n0 1\n");
		return;
	}
	if (n == 6){
		printf("0 0\n2 0\n2 1\n1 1\n1 2\n0 2\n");
		return;
	}
	if (n == 7){
		printf("1 0\n1 1\n2 1\n2 2\n1 2\n1 3\n0 3\n");
		return;
	}
	std::vector <pii> vec;
	vec.push_back({0, 2});
	switch (n % 4){
		case 0:
			vec.push_back({0, 1});
			vec.push_back({1, 1});
			vec.push_back({1, 0});
			vec.push_back({2, 0});
			vec.push_back({2, 1});
			break;
		case 1:
			vec.push_back({2, 0});
			vec.push_back({2, 1});
			break;
		case 2:
			vec.push_back({0, 0});
			vec.push_back({2, 0});
			vec.push_back({2, 1});
			break;
		case 3:
			vec.push_back({0, 1});
			vec.push_back({1, 0});
			vec.push_back({2, 0});
			vec.push_back({2, 1});
			break;
	}
	if (n <= 48){
		for (int i = 1; i <= 6; ++ i){
			if (vec.size() + 2 < n){
				vec.push_back({2 * i + 1, 1});
				vec.push_back({2 * i + 1, 0});
				vec.push_back({2 * i + 2, 0});
				vec.push_back({2 * i + 2, 1});
			}
		}
		vec.push_back({15, 1});
		vec.push_back({15, 2});
		for (int i = 3; i >= 0; -- i){
			if (vec.size() < n){
				vec.push_back({4 * i + 2, 2});
				vec.push_back({4 * i + 2, 3});
				vec.push_back({4 * i + 1, 3});
				vec.push_back({4 * i + 1, 2});
			}
		}
	}
	else{
		for (int i = 1, sz = n % 8 >= 1 && n % 8 <= 4 ? 5 : 6; i <= sz; ++ i){
			vec.push_back({2 * i + 1, 1});
			vec.push_back({2 * i + 1, 0});
			vec.push_back({2 * i + 2, 0});
			vec.push_back({2 * i + 2, 1});
		}
		vec.push_back({15, 1});
		vec.push_back({15, 2});
		int left = (n - vec.size() - 16) / 8;
		for (int i = 3; i >= 0; -- i){
			int x = std::min(6, left);
			vec.push_back({4 * i + 2, 2});
			vec.push_back({4 * i + 2, 3});
			for (int j = 0; j < x; ++ j){
				vec.push_back({4 * i + 3, 2 * j + 3});
				vec.push_back({4 * i + 3, 2 * j + 4});
				vec.push_back({4 * i + 2, 2 * j + 4});
				vec.push_back({4 * i + 2, 2 * j + 5});
			}
			for (int j = x - 1; j >= 0; -- j){
				vec.push_back({4 * i + 1, 2 * j + 5});
				vec.push_back({4 * i + 1, 2 * j + 4});
				vec.push_back({4 * i + 0, 2 * j + 4});
				vec.push_back({4 * i + 0, 2 * j + 3});
			}
			vec.push_back({4 * i + 1, 3});
			vec.push_back({4 * i + 1, 2});
			left -= x;
		}
	}
	assert(vec.size() == n);
	for (auto u : vec){
		printf("%d %d\n", u.first, u.second);
	}
	for (int i = 0; i < n; ++ i){
		const int T = 30;
		const int OFFSET = 100;
		printf("cv.create_line(%d, %d, %d, %d)\n", vec[i].first * T + OFFSET, vec[i].second * T + OFFSET,
													vec[(i + 1) % n].first * T + OFFSET, vec[(i + 1) % n].second * T + OFFSET);
	}
}

int main(){
	freopen("data.txt", "w", stdout);
	int test;
	scanf("%d", &test);
	while (test --){
		int n;
		scanf("%d", &n);
		solve(n);
	}
	return 0;	
}
