#include<stdio.h>
#include<string.h>
#define N (1010)

char s[N], ans[N];

int type(char ch){
	if (ch >= '0' && ch <= '9'){
		return 0;
	}
	if (ch >= 'a' && ch <= 'z'){
		return 1;
	}
	if (ch >= 'A' && ch <= 'Z'){
		return 2;
	}
	return 3;
}

int main(){
	int i, j, k, n;
	scanf("%s", s);
	n = strlen(s);
	for (i = 0, j = 0; i < n; ++ i){
		ans[j ++] = s[i];
		if (i + 2 < N && s[i + 1] == '-'){
			if (type(s[i]) < 3 && type(s[i]) == type(s[i + 2]) && s[i] < s[i + 2]){
				for (k = s[i] + 1; k < s[i + 2]; ++ k){
					ans[j ++] = k;
				}
				++ i;
			}
		}
	}
	printf("%s\n", ans);
	return 0;
}
