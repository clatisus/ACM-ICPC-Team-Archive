#include<bits/stdc++.h>

int n;

int main(){
	scanf("%d", &n);
	int left = 0, right = 1e9;
	while (left < right){
		int mid = left + right >> 1;
		if (1ll * mid * (mid + 1) >> 1 >= n){
			right = mid;
		}
		else{
			left = mid + 1;
		}
	}
	return printf("%d\n", left), 0;
}
