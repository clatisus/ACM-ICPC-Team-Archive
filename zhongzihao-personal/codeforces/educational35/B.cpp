#include<bits/stdc++.h>

int n, a, b;

int main(){
	scanf("%d%d%d", &n, &a, &b);
	int left = 1, right = std::min(a, b);
	while (left < right){
		int mid = left + right + 1 >> 1;
		if (a / mid + b / mid >= n){
			left = mid;
		}
		else{
			right = mid - 1;
		}
	}
	printf("%d\n", left);
	return 0;
}
