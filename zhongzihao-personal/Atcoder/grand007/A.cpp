#include<bits/stdc++.h>

const int N = 10;

char s[N][N];
bool vis[N][N];

void no(){
	puts("Impossible");
	exit(0);
}

int main(){
	int h, w;
	scanf("%d%d", &h, &w);
	for (int i = 0; i < h; ++ i){
		scanf("%s", s[i]);
	}
	if (s[0][0] != '#' || s[h - 1][w - 1] != '#') no();
	vis[0][0] = true;
	for (int i = 0, j = 0; i < h - 1 || j < w - 1; ){
		char ch1 = i < h - 1 ? s[i + 1][j] : '.';
		char ch2 = j < w - 1 ? s[i][j + 1] : '.';
		if ((ch1 == '#') + (ch2 == '#') != 1) no();
		if (ch1 == '#') ++ i;
		else ++ j;
		vis[i][j] = true;
	}
	for (int i = 0; i < h; ++ i){
		for (int j = 0; j < w; ++ j){
			if (!vis[i][j] && s[i][j] == '#') no();
		}
	}
	puts("Possible");
	return 0;
}
