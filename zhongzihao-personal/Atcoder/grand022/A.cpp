#include<bits/stdc++.h>

const int N = 30;

char s[N];
int cnt[N];

int main(){
	scanf("%s", s);
	int n = strlen(s);
	if (n < 26){
		for (int i = 0; i < n; ++ i){
			++ cnt[s[i] - 'a'];
		}
		for (int i = 0; i < 26; ++ i){
			if (!cnt[i]){
				printf("%s%c", s, i + 'a');
				return 0;
			}
		}
	}
	for (int i = 25; i; -- i){
		if (s[i] > s[i - 1]){
			int min = INT_MAX;
			for (int j = i; j < 26; ++ j){
				if (s[j] > s[i - 1]){
					min = std::min(min, (int) s[j]);
				}
			}
			for (int j = 0; j < i - 1; ++ j){
				putchar(s[j]);
			}
			putchar(min);
			return 0;
		}
	}
	puts("-1");
	return 0;
}
