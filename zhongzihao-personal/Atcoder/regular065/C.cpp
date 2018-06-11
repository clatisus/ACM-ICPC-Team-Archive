#include<bits/stdc++.h>

const int N = 100010;

char s[N];

int main(){
	scanf("%s", s);
	int now = strlen(s);
	while (now > 0){
		if (now < 5)
			return printf("NO\n"), 0;
		if (s[now - 1] == 'm' && s[now - 2] == 'a' && s[now - 3] == 'e' && s[now - 4] == 'r' && s[now - 5] == 'd'){
			now -= 5;
			continue;
		}
		if (s[now - 1] == 'e' && s[now - 2] == 's' && s[now - 3] == 'a' && s[now - 4] == 'r' && s[now - 5] == 'e'){
			now -= 5;
			continue;
		}
		if (now < 6)
			return printf("NO\n"), 0;
		if (s[now - 1] == 'r' && s[now - 2] == 'e' && s[now - 3] == 's' && s[now - 4] == 'a' && s[now - 5] == 'r' && s[now - 6] == 'e'){
			now -= 6;
			continue;
		}
		if (now < 7)
			return printf("NO\n"), 0;
		if (s[now - 1] == 'r' && s[now - 2] == 'e' && s[now - 3] == 'm' && s[now - 4] == 'a' && s[now - 5] == 'e' && s[now - 6] == 'r' && s[now - 7] == 'd'){
			now -= 7;
			continue;
		}
		return printf("NO\n"), 0;
	}
	return printf("YES\n"), 0;
}
