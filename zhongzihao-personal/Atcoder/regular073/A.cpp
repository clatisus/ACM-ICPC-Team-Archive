#include<bits/stdc++.h>

const int N = 100;

char a[N], b[N], c[N];

int main(){
	scanf("%s%s%s", a, b, c);
	int lena = strlen(a), lenb = strlen(b), lenc = strlen(c);
	printf(a[lena - 1] == b[0] && b[lenb - 1] == c[0] ? "YES\n" : "NO\n");
	return 0;
}
