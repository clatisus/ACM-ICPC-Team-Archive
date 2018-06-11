#include<bits/stdc++.h>

const int N = 100010;

int a[N];
int n;

int main(){
	scanf("%d", &n);
	int min = INT_MAX;
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
		min = std::min(min, a[i]);
	}
	std::vector <int> vec;
	for (int i = 0; i < n; ++ i){
		if (a[i] == min){
			vec.push_back(i);
		}
	}
	int ans = INT_MAX;
	for (int i = 0, sz = vec.size(); i < sz - 1; ++ i){
		ans = std::min(ans, vec[i + 1] - vec[i]);
	}
	printf("%d\n", ans);
	return 0;
}
