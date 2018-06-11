#include<bits/stdc++.h>

const int N = 100;

int n;
int a[N];

int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i){
		scanf("%d", &a[i]);
	}
	int left = 1, right = n;
	while (left < right){
		int mid = (left + right + 1) / 2;
		if (mid > 1 && a[mid - 1] > a[mid])
			right = mid - 1;
		else
			left = mid;
	}
	int ansright = left;
	left = 1;
	right = n;
	while (left < right){
		int mid = (left + right) / 2;
		if (mid < n && a[mid] < a[mid + 1])
			left = mid + 1;
		else
			right = mid;
	}
	int ansleft = left;
	return printf("%d %d\n", ansleft, ansright), 0;
}
