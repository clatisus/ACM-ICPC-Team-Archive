#include<bits/stdc++.h>

const int N = 10;

char s[N];

int main(){
	scanf("%s", s);
	int x = s[0] == 'H';
	scanf("%s", s);
	int y = s[0] == 'H';
	return printf(x ^ y ? "D\n" : "H\n"), 0;
}
