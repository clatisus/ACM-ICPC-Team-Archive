#include<bits/stdc++.h>

const int N = 26;

int cnt[N];
char s[N + 10];

int main(){
	scanf("%s", s);
	int len = strlen(s);
	for (int i = 0; i < len; ++ i){
		++ cnt[s[i] - 'a'];
	}
	for (int i = 0; i < N; ++ i){
		if (cnt[i] >= 2){
			return printf("no\n"), 0;
		}
	}
	return printf("yes\n"), 0;	
}
