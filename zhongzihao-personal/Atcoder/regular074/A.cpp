#include<bits/stdc++.h>

int a[] = {1, 3, 5, 7, 8, 10, 12};
int b[] = {4, 6, 9, 11};
int c[] = {2};

int x, y;

int main(){
	scanf("%d%d", &x, &y);
	int cnt = 0;
	for (int i = 0; i < 7; ++ i){
		if (a[i] == x || a[i] == y){
			++ cnt;
		}
	}
	if (cnt == 2){
		return printf("Yes\n"), 0;
	}
	cnt = 0;
	for (int i = 0; i < 4; ++ i){
		if (b[i] == x || b[i] == y){
			++ cnt;
		}
	}
	if (cnt == 2){
		return printf("Yes\n"), 0;
	}
	return printf("No\n"), 0;
}
