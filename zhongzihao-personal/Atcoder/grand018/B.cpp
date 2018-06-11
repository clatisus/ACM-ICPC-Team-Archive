#include<bits/stdc++.h>

const int N = 310;

int n, m;
int mat[N][N], sit[N], cnt[N];
bool vis[N];

bool check(int mid){
	memset(sit, 0, sizeof(sit));
	for (int i = 1; i <= m; ++ i){
		vis[i] = true;
	}
	int num = m;
	while (num){
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; ++ i){
			++ cnt[mat[i][sit[i]]];
		}
		bool flag = true;
		for (int i = 1; i <= m; ++ i){
			if (cnt[i] > mid){
				flag = false;
				vis[i] = false;
			}
		}
		if (flag){
			return true;
		}
		for (int i = 0; i < n; ++ i){
			while (sit[i] < m && !vis[mat[i][sit[i]]]){
				++ sit[i];
			}
			if (sit[i] == m){
				return false;
			}
		}
	}
	return false;
}

int main(){
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++ i){
		for (int j = 0; j < m; ++ j){
			scanf("%d", &mat[i][j]);
		}
	}
	int left = 0, right = n;
	while (left < right){
		int mid = left + right >> 1;
		if (check(mid)){
			right = mid;
		}
		else{
			left = mid + 1;
		}
	}
	return printf("%d\n", left), 0;
}
