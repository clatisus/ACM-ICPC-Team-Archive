#include<bits/stdc++.h>

int main(){
	long long x, y;
	scanf("%lld%lld", &x, &y);
	if (x < y){
		std::swap(x, y);
	}
	return printf(x - y >= 2 ? "Alice\n" : "Brown\n"), 0;
}
