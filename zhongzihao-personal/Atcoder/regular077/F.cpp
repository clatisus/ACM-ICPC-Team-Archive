#include<bits/stdc++.h>

typedef long long ll;
const int N = 200010;
const int M = 26;

char p[N];
int fail[N];
ll cnt[M];

int main(){
	ll l, r;
	scanf("%s%lld%lld", p, &l, &r);
    int len = strlen(p);
    fail[0] = -1;
    for(int i = 1, j = -1; i <= len; ++ i){
        while(j >= 0 && p[j] != p[i - 1]) j = fail[j];
        fail[i] = ++ j;
    }
    int n = len - fail[len];
    for (int i = 0; i < n; ++ i){
    	int sit = p[i] - 'a';
		if (l % n <= i){
			++ cnt[sit];
		}
		if (r % n >= i){
			++ cnt[sit];
		}
		cnt[sit] += r / n - l / n - 1;
	}
	for (int i = 0; i < M; ++ i){
		printf("%lld%c", cnt[i], " \n"[i == M - 1]);
	}
	return 0;
};
