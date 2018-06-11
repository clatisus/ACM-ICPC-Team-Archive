#include<bits/stdc++.h>

const int N = 210;

char s[N];

bool check(char *s, int n){
	if (n & 1){
		return false;
	}
	for (int i = 0; i < n >> 1; ++ i){
		if (s[i] != s[i + (n >> 1)]){
			return false;
		}
	}
	return true;
}

int main(){
	scanf("%s", s);
	int len = strlen(s);
	for (int i = 1; ; ++ i){
		if (check(s, len - i)){
			return printf("%d\n", len - i), 0;
		}
	}
}
