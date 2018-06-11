#include<bits/stdc++.h>

long long n, m;

int main(){
	scanf("%lld%lld", &n, &m);
	if (m / 2 <= n){
		return printf("%lld\n", m / 2), 0;
	}
	long long x = m - 2 * n;
	return printf("%lld", x / 4 + n), 0;
}
