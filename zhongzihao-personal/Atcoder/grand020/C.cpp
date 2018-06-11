#include<bits/stdc++.h>

const int N = 4000010;

int n;
std::bitset <N> set;

int main(){
	scanf("%d", &n);
	set.set(0);
	int sum = 0;
	for (int i = 0, x; i < n; ++ i){
		scanf("%d", &x);
		set |= set << x;
		sum += x;
	}
	for (int i = sum + 1 >> 1; ; ++ i){
		if (set.test(i)){
			printf("%d\n", i);
			return 0;
		}
	}
	return 0;
}
