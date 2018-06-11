#include<bits/stdc++.h>

const int N = 200010;

char s[N];

int main(){
	scanf("%s", s);
	int len = strlen(s), begin = 0, end = len - 1;
	for (; s[begin] != 'A'; ++ begin);
	for (; s[end] != 'Z'; -- end);
	return printf("%d\n", end - begin + 1), 0;
}
