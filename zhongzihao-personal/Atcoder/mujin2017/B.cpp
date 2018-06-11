#include<bits/stdc++.h>

const int N = 510;

int n, cntx[N], cnty[N];
char s[N][N];

int main(){
	scanf("%d", &n);
	int min = INT_MAX;
	bool flag = false;
	for (int i = 0; i < n; ++ i){
		scanf("%s", s[i]);
		for (int j = 0; j < n; ++ j){
			if (s[i][j] == '#'){
				flag = true;
				++ cntx[i];
				++ cnty[j];
			}
		}
	}
	if (!flag){
		return printf("-1\n"), 0;
	}
	for (int i = 0; i < n; ++ i){
		min = std::min(n - cntx[i] + !cnty[i], min);
	}
	int ans = n + min;
	for (int j = 0; j < n; ++ j){
		if (cnty[j] == n){
			-- ans;
		}
	}
	return printf("%d\n", ans), 0;
}
