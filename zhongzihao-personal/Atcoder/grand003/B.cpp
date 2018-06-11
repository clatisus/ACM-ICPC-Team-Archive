#include<bits/stdc++.h>

const int N = 100010;

int a[N];

int main(){
	int n;
	scanf("%d", &n);
	long long sum = 0;
	int now = 0;
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
		sum += a[i];
		now ^= a[i] & 1;
		if (!a[i]){
			sum -= now;
			now = 0;
		}
	}
	printf("%lld\n", sum >> 1);
	return 0;
}
