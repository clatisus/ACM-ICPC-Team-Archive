#include<bits/stdc++.h>

const int N = 110;

char s[N];

int main(){
	int x;
	scanf("%d", &x);
	scanf("%s", s);
	int len = strlen(s), max = 0, now = 0;
	for (int i = 0; i < len; ++ i){
		if (s[i] == 'I'){
			++ now;
		}
		else{
			-- now;
		}
		max = std::max(max, now);
	}
	return printf("%d\n", max), 0;
}
