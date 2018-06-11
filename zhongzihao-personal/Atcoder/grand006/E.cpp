#include<bits/stdc++.h>

const int N = 100010;

int cnt[N << 2], a[3][N], inv[N];
bool rev[N];

void no(){
	puts("No");
	exit(0);
}

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 0; i < 3; ++ i){
		for (int j = 0; j < n; ++ j){
			scanf("%d", &a[i][j]);
			++ cnt[a[i][j]];
		}
	}
	for (int i = 1; i <= 3 * n; ++ i){
		if (cnt[i] != 1){
			no();
		}
	}
	for (int i = 0; i < n; ++ i){
		if (a[0][i] + a[2][i] != a[1][i] << 1) no();
		if (std::abs(a[0][i] - a[1][i]) != 1) no();
		if (((a[0][i] - 1) / 3 & 1) != (i & 1)) no();
		inv[(a[0][i] - 1) / 3] = i;
	}
	for (int i = 0; i < n; ++ i){
		if ((a[0][i] - 1) / 3 != i){
			inv[(a[0][i] - 1) / 3] = inv[i];
			for (int j = 0; j < 3; ++ j){
				std::swap(a[j][i], a[j][inv[i]]);
			}
			std::swap(a[0][i + 1], a[2][i + 1]);
			if ((inv[i] - i) >> 1 & 1){
				std::swap(a[0][i], a[2][i]);
				std::swap(a[0][inv[i]], a[2][inv[i]]);
			}
			inv[i] = i;
		}
	}
	for (int i = 0; i < n; ++ i){
		rev[i] = a[0][i] > a[2][i];
	}
	for (int i = 0; i <= n - 4; ++ i){
		if (rev[i]){
			for (int j = 0; j < 4; ++ j){
				rev[i + j] = !rev[i + j];
			}
		}
	}
	if (rev[n - 2] || rev[n - 3] != rev[n - 1]) no();
	puts("Yes");
	return 0;
}
