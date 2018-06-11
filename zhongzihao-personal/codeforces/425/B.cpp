#include<bits/stdc++.h>

const int N = 100010;

bool good[N];
char s[N], pat[N];
int test;

int main(){
	scanf("%s%s%d", s, pat, &test);
	int len = strlen(s), lenpat = strlen(pat);
	for (int i = 0; i < len; ++ i){
		good[s[i]] = true;
	}
	while (test --){
		scanf("%s", s);
		int len = strlen(s);
		bool flag = false;
		for (int i = 0; i < lenpat; ++ i){
			if (pat[i] == '*'){
				flag = true;
				break;
			}
		}
		if (!flag && len != lenpat || flag && len < lenpat - 1){
			printf("NO\n");
			continue;
		}
		flag = false;
		bool ans = true;
		for (int i = 0; i < lenpat; ++ i){
			if (pat[i] == '*'){
				flag = true;
				for (int j = i; j <= i + len - lenpat; ++ j){
					if (good[s[j]]){
						ans = false;
						break;
					}
				}
				continue;
			}
			int sit = flag ? i + len - lenpat : i;
			if (pat[i] == '?'){
				if (!good[s[sit]]){
					ans = false;
				}
				continue;
			}
			if (pat[i] != s[sit]){
				ans = false;
			}
		}
		printf(ans ? "YES\n" : "NO\n");
	}
	return 0;
}
