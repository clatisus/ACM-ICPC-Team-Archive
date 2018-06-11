#include<bits/stdc++.h>

/*
bool check(int n){
	int nn = n;
	int mult = 1;
	for ( ; n; n /= 10){
		mult *= n % 10;
	}
	return mult && !(nn % mult);
}*/

const int N = 10;

bool vis[N];

int main(){
	/*
	for (int i = 1; i <= 10000000; ++ i){
		if (check(i)){
			printf("%d\n", i);
		}
	}*/
	int k;
	scanf("%d", &k);
	for (int i = 1; i < N; ++ i){
		int mod = 0;
		for (int j = 0; j < k - 1; ++ j){
			mod = (mod * 10 + 1) % i;
		}
		mod = (mod * 10 + i) % i;
		vis[i] = !mod;
	}
	int cnt = 0;
	for (int i = 1; i < N - 1; ++ i){
		cnt += vis[i] && vis[i + 1];
	}
	printf("%d\n", cnt);
	return 0;
}
