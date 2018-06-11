#include<bits/stdc++.h>

const int N = 200010;

int a[N], b[N];
int n, l;

bool check(int mid){
	for (int i = 0; i < n; ++ i){
		
	}
}

int main(){
	scanf("%d%d", &n, &l);
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
	}
	for (int i = 0; i < n; ++ i){
		scanf("%d", &b[i]);
	}
	std::sort(a, a + n);
	std::sort(b, b + n);
	/*int left = 0, right = l;
	while (left < right){
		int mid = left + right >> 1;
		if (check(mid)){
			right = mid;
		}
		else{
			left = mid + 1;
		}
	}
	printf("%d\n", left);*/
	int ans = INT_MAX;
	for (int base = -200; base <= 200; ++ base){
		int tmp = 0;
		for (int i = 0; i < n; ++ i){
			int min = std::min(b[i], a[((i + base) % n + n) % n]), max = std::max(b[i], a[((i + base) % n + n) % n]);
			tmp = std::max(tmp, std::min(max - min, l - (max - min)));
		}
		ans = std::min(ans, tmp);
	}
	printf("%d\n", ans);
	return 0;
}
