#include<bits/stdc++.h>

const int N = 7;
const int M = 3;

int a[N];

int main(){
	for (int i = 0; i < N; ++ i){
		std::cin >> a[i];
	}
	double ave = 0;
	for (int i = 0, cnt = 0; cnt < M; ++ i){
		if (a[i] > 0){
			ave += a[i];
			++ cnt;
		}
	}
	std::cout << ave / M << std::endl;
	return 0;
}
