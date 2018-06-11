#include<bits/stdc++.h>

int cnt[1000];
char s[1000];

int main(){
	scanf("%s", s);
	int n = strlen(s);
	for (int i = 0; i < n; ++ i){
		++ cnt[s[i]];
	}
	if ((cnt['N'] > 0) + (cnt['S'] > 0) == 1 || (cnt['W'] > 0) + (cnt['E'] > 0) == 1){
		puts("No");
	}
	else{
		puts("Yes");
	}
	return 0;
}
