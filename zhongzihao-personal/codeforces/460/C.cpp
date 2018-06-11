#include<bits/stdc++.h>

const int N = 2010;
const int MAX = 1 << 12;

char s[N][N];
bool seg[MAX << 1];

void add(int sit, bool value){
	seg[sit += MAX] = value;
	for (sit >>= 1; sit; sit >>= 1){
		seg[sit] = seg[sit << 1] && seg[sit << 1 | 1];
	}
}

bool query(int l, int r){
	bool ret = true;
	for (l += MAX, r += MAX + 1; l < r; l >>= 1, r >>= 1){
		if (l & 1) ret = ret && seg[l ++];
		if (r & 1) ret = ret && seg[-- r];
	}
	return ret;
}

int main(){
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	gets(s[0]);
	for (int i = 0; i < n; ++ i){
		gets(s[i]);
	}
	if (k == 1){
		int cnt = 0;
		for (int i = 0; i < n; ++ i){
			for (int j = 0; j < m; ++ j){
				cnt += s[i][j] == '.';
			}
		}
		printf("%d\n", cnt);
		return 0;
	}
	int cnt = 0;
	for (int i = 0; i < n; ++ i){
		for (int j = 0; j < m; ++ j){
			add(j, s[i][j] == '.');
		}
		for (int j = 0; j <= m - k; ++ j){
			cnt += query(j, j + k - 1);
		}
	}
	for (int i = 0; i < m; ++ i){
		for (int j = 0; j < n; ++ j){
			add(j, s[j][i] == '.');
		}
		for (int j = 0; j <= n - k; ++ j){
			cnt += query(j, j + k - 1);
		}
	}
	printf("%d\n", cnt);
	return 0;
}
