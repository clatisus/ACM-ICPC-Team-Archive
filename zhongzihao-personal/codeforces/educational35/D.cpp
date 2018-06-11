#include<bits/stdc++.h>

const int N = 1510;

int n;
int a[N];

int main(){
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
	}
	int parity = 0;
	for (int i = 0; i < n; ++ i){
		for (int j = i + 1; j < n; ++ j){
			if (a[i] > a[j]){
				parity ^= 1;
			}
		}
	}
	int m;
	scanf("%d", &m);
	while (m --){
		int l, r;
		scanf("%d%d", &l, &r);
		parity ^= (r - l) * (r - l + 1) >> 1 & 1;
		puts(parity ? "odd" : "even");
	}
	return 0;
}
