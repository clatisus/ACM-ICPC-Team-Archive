#include<bits/stdc++.h>

const int N = 100;

char s[2][N];

int main(){
	scanf("%s%s", s[0], s[1]);
	for (int i = 0; ; ++ i){
		char ch = s[i & 1][i >> 1];
		if (ch == '\0'){
			return printf("\n"), 0;
		}
		putchar(ch);
	}
}
