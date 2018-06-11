#include<bits/stdc++.h>

int main(){
	freopen("data.txt", "w", stdout);
	int a0, d, n, m;
	scanf("%d%d%d%d", &a0, &d, &n, &m);
	printf("%d %d\n", m, n);
	for (int i = 0; i < n; ++ i){
		printf("%d ", a0);
		a0 = (a0 + d) % m;
	}
	return 0;
}
