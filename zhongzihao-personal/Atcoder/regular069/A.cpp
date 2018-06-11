#include<bits/stdc++.h>

int n, x, y;

int main(){
	scanf("%d", &n);
	x = n * 800;
	y = n / 15 * 200;
	return printf("%d", x - y), 0;
}
