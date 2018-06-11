#include<bits/stdc++.h>

const int N = 500010;

int a[N];

int main(){
	int len = 0;
	char ch = getchar();
	while (ch >= '0' && ch <= '9'){
		a[len ++] = ch - '0';
		ch = getchar();
	}
	for (int i = 0; i < len >> 1; ++ i){
		std::swap(a[i], a[len - i - 1]);
	}
	int up = 0;
	for (int i = 0; i <= len; ++ i){
		a[i] *= 9;
		a[i] += up;
		up = a[i] / 10;
		a[i] %= 10;
	}
	if (a[len]){
		++ len;
	}
	int sum = 0, k = 0;
	for (int i = 0; i < len; ++ i){
		sum += a[i];
	}
	while (true){
		++ k;
		a[0] += 9;
		sum += 9;
		int sit = 0;
		while (a[sit] >= 10){
			a[sit] -= 10;
			++ a[sit + 1];
			++ sit;
			sum -= 9;
		}
		if (sum <= 9 * k){
			return printf("%d\n", k), 0;
		}
	}
}
