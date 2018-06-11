#include<bits/stdc++.h>
#define ll long long

const int N = 100010;

char s[N];

int main(){
	scanf("%s", s);
	int len = strlen(s);
	ll ans = 0;
	for (int i = 0; i < len - 1; ++ i){
		ans += (s[i] == 'U' ? 1 : 2) * (len - 1 - i);
	}
	for (int i = 1; i < len; ++ i){
		ans += (s[i] == 'D' ? 1 : 2) * i;
	}
	return printf("%lld\n", ans), 0;
}
