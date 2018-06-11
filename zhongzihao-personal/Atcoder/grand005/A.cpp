#include<bits/stdc++.h>

const int N = 200010;

char s[N];

int main(){
	scanf("%s", s);
	int n = strlen(s);
	int now = 0, ans = 0;
	for (int i = 0; i < n; ++ i){
		if (s[i] == 'S'){
			++ now;
		}
		else{
			if (now){
				-- now;
			}
			else{
				++ ans;
			}
		}
	}
	ans += now;
	printf("%d\n", ans);
	return 0;
}
