#include<bits/stdc++.h>
#define N (110)

char s[N][N];

int main(){
	int n = 2;
	for (int i = 0; i < n; ++ i){
		scanf("%s", s[i]);
	}
	for (int i = 0; i < n; ++ i){
		printf("%s\n", s[i]);
	}
	return 0;
}
