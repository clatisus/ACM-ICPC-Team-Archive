#include<bits/stdc++.h>

char s[100][100];

inline int sqr(int n){return n * n;}

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= 2 * n + 1; ++ i){
		for (int j = 1; j <= 2 * n + 1; ++ j){
			s[i][j] = sqr(i - n - 1) + sqr(j - n - 1) <= sqr(n) ? '#' : '.';
		}
	}
	for (int i = 1; i <= 2 * n + 1; ++ i){
		puts(s[i] + 1);
	}
	return 0;
}
