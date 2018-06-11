#include<bits/stdc++.h>

const int N = 110;

char s[N], t[N];

int main(){
	int n;
	scanf("%d%s%s", &n, s, t);
	for (int i = 0; i <= n; ++ i){
		bool flag = true;
		for (int j = i; j < n; ++ j){
			if (s[j] != t[j - i]){
				flag = false;
				break;
			}
		}
		if (flag){
			printf("%d\n", n + i);
			return 0;
		}
	}
}
