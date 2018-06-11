#include<bits/stdc++.h>

int main(){
	int a, b, c, d, e, f;
	scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &e, &f);
	std::pair <int, int> max{1, -1};
	for (int i = 0; i <= 30; ++ i){
		for (int j = 0; j <= 30; ++ j){
			if (!(i + j)) continue;
			for (int k = 0; k <= 3000; ++ k){
				int x = 100 * i * a + 100 * j * b + k * c;
				if (x > f){
					continue;
				}
				if (e * (i * a + j * b) < k * c) continue;
				int u = std::min(e * (i * a + j * b) - k * c, f - x) / d;
				std::pair <int, int> ans = {100 * i * a + 100 * j * b, k * c + u * d};
				if (ans.second * max.first > ans.first * max.second){
					max = ans;
				}
			}
		}
	}
	printf("%d %d\n", max.first + max.second, max.second);
}
