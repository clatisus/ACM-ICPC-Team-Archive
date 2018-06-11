#include<bits/stdc++.h>
#define ll long long

const int N = 100010;

int a, b, n;
int num[N];

bool check(int mid){
	ll cnt = 0, y = a - b;
	for (int i = 0; i < n; ++ i){
		ll x = num[i] - 1ll * b * mid;
		cnt += x >= 0 ? (x + y - 1) / y : 0;
	}
	return cnt <= mid;
}

int main(){
	scanf("%d%d%d", &n, &a, &b);
	for (int i = 0; i < n; ++ i){
		scanf("%d", &num[i]);
	}
	int left = 0, right = 1e9;
	while (left < right){
		int mid = left + right >> 1;
		if (check(mid)){
			right = mid;
		}
		else{
			left = mid + 1;
		}
	}
	return printf("%d\n", left), 0;
}
