#include<bits/stdc++.h>

typedef long long ll;

const int N = 20;

int digit[N];

int main(){
	ll n;
	scanf("%lld", &n);
	int cnt = 0;
	for ( ; n; n /= 10){
		digit[cnt ++] = n % 10;
	}
	std::reverse(digit, digit + cnt);
	int max = digit[0] - 1;
	bool flag = true;
	for (int i = 1; i < cnt; ++ i){
		max += 9;
		flag = flag && digit[i] == 9;
	}
	max += flag;
	printf("%d\n", max);
	return 0;
}
