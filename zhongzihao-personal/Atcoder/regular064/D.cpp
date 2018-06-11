#include<bits/stdc++.h>

const int N = 100010;

char s[N];

int main(){
	scanf("%s", s);
	int len = strlen(s);
	int odd = len & 1;
	int equal = s[len - 1] == s[0];
	return printf((odd ^ equal) ? "First" : "Second"), 0;
}
