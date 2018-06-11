#include<bits/stdc++.h>

const int N = 110;

char s[N][N];
int n, m;

int main(){
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i){
		scanf("%s", s[i] + 1);
	}
	for (int i = 0; i <= n + 1; ++ i){
		s[i][0] = s[i][m + 1] = '#';
	}
	for (int i = 0; i <= m + 1; ++ i){
		s[0][i] = s[n + 1][i] = '#';
	}
	for (int i = 0; i <= n + 1; ++ i){
		printf("%s\n", s[i]);
	}
	return 0;
}
