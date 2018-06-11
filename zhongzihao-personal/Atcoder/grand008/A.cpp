#include<bits/stdc++.h>

int main(){
	int x, y;
	scanf("%d%d", &x, &y);
	if (!x){
		printf("%d\n", y > 0 ? y : -y + 1);
		return 0;
	}
	if (!y){
		printf("%d\n", x < 0 ? -x : x + 1);
		return 0;
	}
	if (x > 0 && y > 0 || x < 0 && y < 0){
		printf("%d\n", x > y ? x - y + 2 : y - x);
		return 0;
	}
	printf("%d\n", std::abs(std::abs(x) - std::abs(y)) + 1);
	return 0;
}
