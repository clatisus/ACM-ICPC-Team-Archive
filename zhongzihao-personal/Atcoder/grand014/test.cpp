#include<bits/stdc++.h>

int main(){
	freopen("data.txt", "w", stdout);
	int n = 100000;
	printf("%d\n", n);
	for (int i = 1; i <= n; ++ i){
		printf("%d%c", i & 1, " \n"[i == n]);
	}
	return 0;
}
