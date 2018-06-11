#include<bits/stdc++.h>

int a, b, c;

int main(){
	scanf("%d%d%d", &a, &b, &c);
	int i = 0;
	for ( ; i < 1000000 && !(a & 1) && !(b & 1) && !(c & 1); ++ i){
		int x = a + b >> 1, y = b + c >> 1, z = a + c >> 1;
		a = x, b = y, c = z;
	}
	return printf("%d\n", i > 900000 ? -1 : i), 0;
}
