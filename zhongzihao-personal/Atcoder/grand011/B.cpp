#include<bits/stdc++.h>
#define ll long long

const int N = 100010;

int n, a[N];

bool check(int mid){
	ll sum = a[mid];
	for (int i = 0; i < n; ++ i){
		if (i == mid){
			continue;
		}
		if (2 * sum < a[i]){
			return false;
		}
		sum += a[i];
	}
	return true;
}

int main(){
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
	}
	std::sort(a, a + n);
	int left = 0, right = n - 1;
	while (left < right){
		int mid = left + right >> 1;
		if (check(mid)){
			right = mid;
		}
		else{
			left = mid + 1;
		}
	}
	return printf("%d\n", n - left), 0;
}
