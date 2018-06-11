#include<bits/stdc++.h>

int comb(int x){
	if (x < 2){
		return 0;
	}
	return x * (x - 1) >> 1;
}

int main(){
	int k, s;
	scanf("%d%d", &k, &s);
	return printf("%d\n", comb(s + 2) - 3 * comb(s - k + 1) + 3 * comb(s - 2 * k) - comb(s - 3 * k - 1)), 0;
}
