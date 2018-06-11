#include<bits/stdc++.h>

const int N = 200010;

int a[N];
int n;

int main(){
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
	}
	if (n & 1){
		for (int i = n - 1; i >= 0; i -= 2){
			printf("%d ", a[i]);
		}
		for (int i = 1; i < n; i += 2){
			printf("%d ", a[i]);
		}
	}
	else{
		for (int i = n - 1; i > 0; i -= 2){
			printf("%d ", a[i]);
		}
		for (int i = 0; i < n; i += 2){
			printf("%d ", a[i]);
		}
	}
	return printf("\n"), 0;
}
