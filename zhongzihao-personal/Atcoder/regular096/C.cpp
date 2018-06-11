#include<bits/stdc++.h>

int main(){
	int a, b, c, x, y;
	scanf("%d%d%d%d%d", &a, &b, &c, &x, &y);
	if (c << 1 >= a + b){
		printf("%d\n", a * x + b * y);
		return 0;
	}
	int min = std::min(x, y);
	int cost = c * min * 2;
	x -= min, y -= min;
	cost += std::min(c << 1, a) * x;
	cost += std::min(c << 1, b) * y;
	printf("%d\n", cost);
	return 0;
}
