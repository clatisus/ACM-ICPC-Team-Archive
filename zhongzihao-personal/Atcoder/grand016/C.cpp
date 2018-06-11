#include<bits/stdc++.h>
#define pii std::pair <int, int>

pii calc(int a, int b){
	int y = (b + a - 1) / a * 3;
	int x = (a - 1) * y - 1;
	return {x, -y};
}

int H, W, h, w;

int main(){
	scanf("%d%d%d%d", &H, &W, &h, &w);
	if (H % h){
		pii p = calc(h, H);
		printf("Yes\n");
		for (int i = 0; i < H; ++ i){
			for (int j = 0; j < W; ++ j){
				printf("%d%c", i % h ? p.second : p.first, " \n"[j == W - 1]);
			}
		}
	}
	else{
		if (W % w){
			pii p = calc(w, W);
			printf("Yes\n");
			for (int i = 0; i < H; ++ i){
				for (int j = 0; j < W; ++ j){
					printf("%d%c", j % w ? p.second : p.first, " \n"[j == W - 1]);
				}
			}
		}
		else{
			return printf("No\n"), 0;
		}
	}
	for (int i = 0; i < H; ++ i){
		for (int j = 0; j < W; ++ j){
		}
	}
	return 0;
}
