#include<bits/stdc++.h>

const int N = 110;

int n, m;
int a[N];

int main(){
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; ++ i){
		scanf("%d", &a[i]);
	}
	if (m == 1){
		if (a[0] == 1){
			printf("1\n1\n1\n");
			return 0;
		}
		printf("%d\n2\n%d 1\n", a[0], a[0] - 1);
		return 0;
	}
	if (m == 2){
		if (a[1] == 1){
			printf("%d %d\n1\n%d\n", a[0], a[1], a[0] + a[1]);
			return 0;
		}
		printf("%d %d\n2\n%d %d\n", a[0], a[1], a[0] + 1, a[1] - 1);
		return 0;
	}
	for (int i = 1; i < m - 1; ++ i){
		if (a[i] & 1){
			if (a[0] % 2 == 0){
				std::swap(a[0], a[i]);
			}
			else if (a[m - 1] % 2 == 0){
				std::swap(a[i], a[m - 1]);
			}
			else{
				printf("Impossible\n");
				return 0;
			}
		}
	}
	for (int i = 0; i < m; ++ i){
		printf("%d%c", a[i], " \n"[i == m - 1]);
	}
	if (a[m - 1] == 1){
		printf("%d\n", m - 1);
		for (int i = 0; i < m - 1; ++ i){
			printf("%d%c", i ? a[i] : a[i] + 1, " \n"[i == m - 2]);
		}
		return 0;
	}
	printf("%d\n", m);
	for (int i = 0; i < m; ++ i){
		printf("%d%c", i == m - 1 ? a[i] - 1 : i ? a[i] : a[i] + 1, " \n"[i == m - 1]);
	}
	return 0;
}
