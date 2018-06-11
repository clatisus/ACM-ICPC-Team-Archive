#include<bits/stdc++.h>

const int N = 100010;

int a[N], _left[N], _right[N], left[N], right[N], x[N];

bool check(int mid, int n, int b){
	for (int i = 1; i <= n; ++ i){
		x[i] = a[i];
	}
	for (int i = mid + 1, j = 0; i <= n - mid; ++ i){
		j = std::max(j, left[i]);
		while (j <= right[i] && x[i] < b){
			int dif = b - x[i];
			int low = mid + 1 <= j && j <= n - mid ? b : 0;
			if (x[j] > low){
				int y = std::min(dif, x[j] - low);
				x[i] += y;
				x[j] -= y;
			}
			if (x[j] <= low){
				++ j;
			}
		}
		if (x[i] < b){
			return false;
		}
	}
	return true;
}

int main(){
	int n, d, b;
	scanf("%d%d%d", &n, &d, &b);
	for (int i = 1; i <= n; ++ i){
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= n; ++ i){
		int x = std::min(i, n - i + 1);
		left[i] = std::max(1ll, i - 1ll * x * d);
		right[i] = std::min(1ll * n, i + 1ll * x * d);
	}
	int left = 0, right = n + 1 >> 1;
	while (left < right){
		int mid = left + right >> 1;
		if (check(mid, n, b)){
			right = mid;
		}
		else{
			left = mid + 1;
		}
	}
	printf("%d\n", left);
	return 0;
}
