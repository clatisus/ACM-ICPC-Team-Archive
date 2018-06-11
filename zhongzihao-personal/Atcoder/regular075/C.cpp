#include<bits/stdc++.h>

const int N = 110;

int a[N];
int n;

int main(){
	scanf("%d", &n);
	int sum = 0;
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
		sum += a[i];
	}
	if (sum % 10){
		return printf("%d\n", sum), 0;
	}
	int max = 0;
	for (int i = 0; i < n; ++ i){
		if ((sum - a[i]) % 10){
			max = std::max(max, sum - a[i]);
		}
	}
	return printf("%d\n", max), 0;
}
