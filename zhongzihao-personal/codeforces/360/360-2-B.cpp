#include<cstdio>
#include<cstdlib>
#include<cstring>
int main()
{
	int i;
	char s[100001];
	scanf("%s",s);
	printf("%s",s);
	for (i=strlen(s)-1;i>=0;i--)
		printf("%c",s[i]);
	return 0;
}
