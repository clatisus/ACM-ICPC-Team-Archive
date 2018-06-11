#include<bits/stdc++.h>

const int N = 60;

int n;
char s[N];
int cnt[N], _cnt[N];

int main(){
	memset(_cnt, 0x7f, sizeof(_cnt));
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i){
		memset(cnt, 0, sizeof(cnt));
		scanf("%s", s);
		int len = strlen(s);
		for (int j = 0; j < len; ++ j){
			++ cnt[s[j] - 'a'];
		}
		for (int j = 0; j < N; ++ j){
			_cnt[j] = std::min(_cnt[j], cnt[j]);
		}
	}
	for (int i = 0; i < N; ++ i){
		for (int j = 0; j < _cnt[i]; ++ j){
			putchar('a' + i);
		}
	}
	return printf("\n"), 0;
}
