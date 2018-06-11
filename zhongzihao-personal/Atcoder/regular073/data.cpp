#include<bits/stdc++.h>
#define ll long long

const int TEST = 1;
const int N = 50000;
const int MAX = 1e3;

int rand_int(int n){
	return (rand() * rand() + rand() + 1) % n;
}

void make_data(int n){
	printf("%d\n", n);
	for (int i = 0; i < n; ++ i){
		printf("%d %d\n", rand_int(MAX) + 1, rand_int(MAX) + 1);
	}
}

int main(){
	srand(time((unsigned) NULL));
	for (int i = 1; i <= TEST; ++ i){
		freopen("data.txt", "w", stdout);
		make_data(N);
	}
	return 0;
}
