#include<bits/stdc++.h>
using namespace std;
const int N = 100010;
int main()
{
	int m, count = 0;
	bool cover[N];
	char str[N], ans[N] = "";
	memset(cover, false, sizeof(cover));
	scanf("%d%s", &m, str);
	int sit = 0;
	for (char ch = 'a'; ch <= 'z'; ch++)
	{ 
		int  i = -1, len = strlen(str), count1 = 0;
		while (i < len)
		{
			int j = min(len - 1, i + m);
			while (str[j] != ch && j > i)
				j--;
			if (j == i)
			{
				i += m;
				continue;
			}
			bool flag = true;
			for (int k = max (0, j - m + 1), size = min(j, len - m); k <= size; k++)
				if (!cover[k])
				{
					flag = false;
					break;
				}
			if (flag)
			{
				i = j;
				continue;
			}
			for (int k = max (0, j - m + 1), size = min(j, len - m); k <= size; k++)
				if (!cover[k])
				{
					cover[k] = true;
					count++;
				}
			ans[sit++] = ch;
			count1++;
			i = j;
			if (count == len - m + 1)
			{
				printf("%s", ans);
				return 0;
			}
		}
		for (int k = 0; k < len; k++)
		{
			if (str[k] == ch)
			{
				count1--;
				if (count1 < 0)
					ans[sit++] = ch;
			}
		}
	}
}
