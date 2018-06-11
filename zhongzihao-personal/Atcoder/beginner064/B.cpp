#include<bits/stdc++.h>

int main(){
	int n;
	scanf("%d", &n);
	int min = INT_MAX, max = 0;
	for (int i = 0, x; i < n; ++ i){
		scanf("%d", &x);
		min = std::min(min, x);
		max = std::max(max, x);
	}
	return printf("%d\n", max - min), 0;
}
