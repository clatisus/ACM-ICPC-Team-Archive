#include<bits/stdc++.h>
#define ll long long

const int moder = 1e9 + 7;

int main(){
	ll n;
	/*scanf("%d", &n);
	if (n & 1){
		int x = (n + 1) / 2;
		return printf("%lld\n", (x % moder * ((x + 1) % moder) - 1 + moder) % moder);
	}
	int x = n / 2 + 1;
	return printf("%lld\n", ((x % moder * ((x + 1) % moder) - (x + 1) % moder) % moder + moder) % moder);*/
	int cnt = 0;
	for (int i = 0; i <= 711; ++ i){
		for (int j = 0; j <= 711; ++ j){
			if ((i | j) <= 711 >> 1){
				++ cnt;
			}
		}
	}
	std::cout << cnt;
}
