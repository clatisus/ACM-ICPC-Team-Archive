#include<bits/stdc++.h>

const int N = 100010;

char s[N];

int main(){
	scanf("%s", s);
	int len = strlen(s);
	for (int i = 0; i < len; i += 2){
		putchar(s[i]);
	}
	return printf("\n"), 0;
}
