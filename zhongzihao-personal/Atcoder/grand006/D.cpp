#include<bits/stdc++.h>

const int N = 100010;

int a[N << 1];
int big[N << 1];
int n;

bool check(int mid){
	for (int i = 0; i < 2 * n - 1; ++ i){
		big[i] = a[i] >= mid;
	}
	if (big[n - 1] == big[n - 2] || big[n - 1] == big[n]) return big[n - 1];
	int left = n - 1;
	while (left > 0 && big[left] != big[left - 1]){
		-- left;
	}
	int right = n - 1;
	while (right < 2 * n - 2 && big[right] != big[right + 1]){
		++ right;
	}
	if (left == 0 && right == 2 * n - 2) return big[n - 1] ^ (n - 1 & 1);
	return n - 1 - left < right - (n - 1) ? big[left] : big[right];
}

int main(){
	scanf("%d", &n);
	for (int i = 0; i < 2 * n - 1; ++ i){
		scanf("%d", &a[i]);
	}
	int left = 1, right = 2 * n - 1;
	while (left < right){
		int mid = left + right + 1 >> 1;
		if (check(mid)){
			left = mid;
		}
		else{
			right = mid - 1;
		}
	}
	printf("%d\n", left);
	return 0;
}
