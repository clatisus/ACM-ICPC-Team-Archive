#include<bits/stdc++.h>

const int N = 100010;

int a[N];
int n;

int main(){
	scanf("%d", &n);
	int max = 0;
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
		max = std::max(a[i], max);
	}
	int cnt = 0;
	bool flag = true;
	for (int i = 0; i < n; ++ i){
		if (max != a[i]){
			flag = false;
			break;
		}
	}
	if (flag){
		if (max == n - 1){
			return printf("Yes\n"), 0;
		}
	}
	for (int i = 0; i < n; ++ i){
		if (a[i] != max && a[i] != max - 1){
			return printf("No\n"), 0;
		}
		cnt += a[i] == max;
	}
	int left = !!cnt, right = cnt >> 1;
	return printf(left + n - cnt > max || right + n - cnt < max ? "No\n" : "Yes\n"), 0;
}
