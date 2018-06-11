#include<bits/stdc++.h>

int main(){
	int n, pos, l, r;
	scanf("%d%d%d%d", &n, &pos, &l, &r);
	int ans = 0;
	if (l == 1){
		if (r == n){
			return printf("0\n"), 0;
		}
		return printf("%d\n", std::abs(pos - r) + 1), 0;
	}
	if (r == n){
		return printf("%d\n", std::abs(pos - l) + 1), 0;
	}
	return printf("%d\n", std::min(std::abs(pos - l), std::abs(pos - r)) + std::abs(l - r) + 2), 0;
}
