#include<bits/stdc++.h>

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	int min1 = 1000000, min2 = 1;
	for (int i = 0, x, y; i < n; ++ i){
		scanf("%d%d", &x, &y);
		if (x * min2 < y * min1){
			min1 = x;
			min2 = y;
		}
	}
	printf("%.10lf\n", 1.0 * min1 / min2 * m);
	return 0;
}
