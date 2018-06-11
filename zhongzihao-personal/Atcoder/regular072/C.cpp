#include<bits/stdc++.h>
#define ll long long

const int N = 100010;

int a[N];
int n;

int main(){
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
	}
	ll sum = 0, ans = 0;
	for (int i = 0; i < n; ++ i){
		sum += a[i];
		if (i & 1){
			if (sum > 0){
				continue;
			}
			ans += 1 - sum;
			sum = 1;
		}
		else{
			if (sum < 0){
				continue;
			}
			ans += sum + 1;
			sum = -1;
		}
	}
	ll min = ans;
	sum = 0, ans = 0;
	for (int i = 0; i < n; ++ i){
		sum += a[i];
		if (!(i & 1)){
			if (sum > 0){
				continue;
			}
			ans += 1 - sum;
			sum = 1;
		}
		else{
			if (sum < 0){
				continue;
			}
			ans += sum + 1;
			sum = -1;
		}
	}
	min = std::min(ans, min);
	return printf("%lld\n", min), 0;
}
