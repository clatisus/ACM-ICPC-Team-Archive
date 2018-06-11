#include<bits/stdc++.h>

const int N = 3000;

int rand_int(int n){
	return (rand() * rand() + rand() + 1) % n;
}

int main(){
	freopen("data.txt", "w", stdout);
	srand(time((unsigned) NULL));
	printf("%d %d %d\n", N, N, N - 1);
	for (int i = 1; i <= N; ++ i){
		printf("%d ", rand_int(N) + 1);
	}
	printf("\n");
	for (int i = 2; i <= N; ++ i){
		printf("%d %d\n", i, rand_int(i - 1) + 1);
	}
	return 0;
}
