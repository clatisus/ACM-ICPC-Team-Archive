#include<bits/stdc++.h>

bool check(int n){
	int sum = 0;
	for ( ; n; n /= 10){
		sum += n % 10;
	}
	return sum == 10;
}

int main(){
	int cnt = 0;
	std::vector <int> vec;
	for (int i = 0; i < 20000000; ++ i){
		if (check(i)){
			vec.push_back(i);
		}
	}
	int n;
	scanf("%d", &n);
	printf("%d\n", vec[n - 1]);
	return 0;
}
