#include<bits/stdc++.h>

const int N = 11;
typedef long long ll;

char s[N];
int ans[N];

bool query(ll n){
	printf("? %lld\n", n);
	fflush(stdout);
	scanf("%s", s);
	return s[0] == 'Y';
}

ll power[N];

int main(){
	power[0] = 1;
	for (int i = 1; i < N; ++ i){
		power[i] = power[i - 1] * 10;
	}
	bool flag = query(power[N - 1]);
	int sit = 0;
	for (int i = 1; i < N; ++ i){
		if (flag && sit){
			break;
		}
		if (query(power[i - 1]) && query(power[i] - 1)){
			sit = i;
		}
	}
	for (int i = 0; i < sit - 1; ++ i){
		ll x = 0;
		for (int j = 0; j < i; ++ j){
			x += ans[j] * power[i - j];
		}
		int left = !i, right = 9;
		for (int mid = left + right + 1 >> 1; left < right; mid = left + right + 1 >> 1){
			if (query(x + mid)){
				left = mid; 
			}
			else{
				right = mid - 1;
			}
		}
		ans[i] = left;
	}
	ll x = 0;
	for (int i = 0; i < sit - 1; ++ i){
		x += ans[i] * power[sit - i];
	}
	int left = sit == 1, right = 9;
	for (int mid = left + right >> 1; left < right; mid = left + right >> 1){
		if (query(x + mid * 10)){
			right = mid; 
		}
		else{
			left = mid + 1;
		}
	}
	ans[sit - 1] = left;
	printf("! ");
	for (int i = 0; i < sit; ++ i){
		printf("%d", ans[i]);
	}
	return printf("\n"), 0;
}
