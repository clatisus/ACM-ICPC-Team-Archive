#include<bits/stdc++.h>

int x, t;

int main(){
	scanf("%d%d", &x, &t);
	return printf("%d\n", x >= t ? x - t : 0), 0;
}
