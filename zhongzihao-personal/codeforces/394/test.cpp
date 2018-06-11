#include<bits/stdc++.h>
#define ll long long

const int N = 1000;
const int M = 5;
const int K = 100;

int rand_int(int n){
	return (rand() * rand() + rand() + 1) % n;
}

ll rand_ll(ll n){
	return (1ll * rand() * rand() * rand() * rand() + rand() * rand() + 1) % n;
}

char rand_low(){
	return 'a' + rand_int(26);
}

int main(){
	freopen("data.txt", "w", stdout);
	srand(time((unsigned) NULL));
	printf("%d %d %d\n", N, M, K);
	for (int i = 0; i < N; ++ i){
		for (int j = 0; j < M; ++ j){
			putchar(rand_low());
		}
		putchar('\n');
	}
	for (int i = 0; i < K; ++ i){
		int a = rand_int(N) + 1, b = rand_int(M) + 1, c = 0, d = 0;
		while (c < a){
			c = rand_int(N) + 1;
		}
		while (d < b){
			d = rand_int(M) + 1;
		}
		char ch = rand_low();
		printf("%d %d %d %d %c\n", a, b, c, d, ch);
	}
	return 0;
}
