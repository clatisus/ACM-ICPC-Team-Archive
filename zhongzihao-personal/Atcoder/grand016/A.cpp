#include<bits/stdc++.h>

const int N = 110;

char s[N];

int main(){
	scanf("%s", s + 1);
	int len = strlen(s + 1);
	int min = INT_MAX;
	for (int i = 0; i < 26; ++ i){
		s[len + 1] = i + 'a';
		int pre = 0, max = 0;
		for (int j = 1; j <= len + 1; ++ j){
			if (s[j] == i + 'a'){
				max = std::max(max, j - pre - 1);
				pre = j;
			}
		}
		min = std::min(min, max);
	}
	return printf("%d\n", min), 0;
}
