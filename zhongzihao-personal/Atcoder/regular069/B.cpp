#include<bits/stdc++.h>

const int moder = 1e9 + 7;

int n;

int main(){
	scanf("%d", &n);
	int ret = 1;
	for (int i = 1; i <= n; ++ i){
		ret = 1ll * ret * i % moder;
	}
	return printf("%d\n", ret), 0;
}
