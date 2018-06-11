#include<bits/stdc++.h>

const int N = 410;
const int moder = 1e9 + 7;

int k;
int a[N];

int main(){
	for (int i = 1; i < N; ++ i){
		a[i] = (2ll * a[i - 1] * a[i - 1] % moder + 2ll * a[i - 1] + 1) % moder;
		
	}
	scanf("%d", &k);
	return printf("%d\n", a[k]), 0;
}
