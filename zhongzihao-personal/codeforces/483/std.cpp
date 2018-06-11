#include<bits/stdc++.h>

const int N = 20;

int a[N][N];

int main(){
	//freopen("data.txt", "r", stdin);
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i){
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		for (int j = x1; j < x2; ++ j){
			for (int k = y1; k < y2; ++ k){
				a[j][k] = i + 1;
			}
		}
	}
	std::set <int> ans;
	for (int i = 0; i < N; ++ i){
		for (int j = 0; j < N; ++ j){
			ans.insert(a[i][j]);
			//printf("%d%c", a[i][j], " \n"[j == N - 1]);
		}
	}
	printf("%d\n", (int) ans.size());
	return 0;
}
