#include<bits/stdc++.h>

const int N = 510;

char ans1[N][N], ans2[N][N];

int main(){
	int h, w;
	scanf("%d%d", &h, &w);
	for (int i = 0; i < h; ++ i){
		scanf("%s", ans1[i]);
	}
	for (int i = 0; i < h; ++ i){
		for (int j = 0; j < w; ++ j){
			ans2[i][j] = ans1[i][j];
		}
	}
	for (int i = 0; i < h; ++ i){
		for (int j = 1; j < w - 1; ++ j){
			(i & 1 ? ans2[i][j] : ans1[i][j]) = '#';
		}
	}
	for (int i = 0; i < h; ++ i){
		ans1[i][0] = '#';
		ans2[i][w - 1] = '#';
	}
	for (int i = 0; i < h; ++ i){
		for (int j = 0; j < w; ++ j){
			putchar(ans1[i][j]);
		}
		putchar('\n');
	}
	putchar('\n');
	for (int i = 0; i < h; ++ i){
		for (int j = 0; j < w; ++ j){
			putchar(ans2[i][j]);
		}
		putchar('\n');
	}
	return 0;
}
