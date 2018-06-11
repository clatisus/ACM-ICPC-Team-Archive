#include<bits/stdc++.h>
const int N = 100010;

char s[N];

int main()
{
	scanf("%s", s);
	int cnt = 0, len = strlen(s);
	for (int i = 1; i < len; i++)
		if (s[i] != s[i - 1])
			cnt ++;
	printf("%d\n", cnt);
	return 0;
}
