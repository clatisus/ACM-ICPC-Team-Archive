#include<bits/stdc++.h>

const int N = 100010;

int n, a[N], b[N], ans[N];
char s[N];

bool check(int x, int type){
	ans[x] = type;
	for (int i = x; ; i = (i + 3) % n){
		int y = (i + 3) % n, ret = ans[i] ^ b[i];
		if (y == x){
			return ret == ans[x];
		}
		ans[y] = ret;
	}
}

bool check1(){
	for (int i = 0; i < n; ++ i){
		if (ans[i] ^ ans[(i + 1) % n] ^ ans[(i + 2) % n] != a[i]){
			return false;
		}
	}
	return true;
}

void print(){
	for (int i = 0; i < n; ++ i){
		putchar(ans[(i + 1) % n] ? 'W' : 'S');
	}
	putchar('\n');
	exit(0);
}

int main(){
	scanf("%d%s", &n, s);
	for (int i = 0; i < n; ++ i){
		if (s[i] == 'x'){
			a[i] = 1;
		}
	}
	for (int i = 0; i < n; ++ i){
		b[i] = a[i] ^ a[(i + 1) % n];
	}
	if (n == 3){
		if (!a[0] && !a[1] && !a[2]){
			return printf("SSS\n"), 0;
		}
		if (a[0] && a[1] && a[2]){
			return printf("WWW\n"), 0;
		}
		return printf("-1\n"), 0;
	}
	if (n % 3){
		if (check(0, 0) && check1()){
			print();
		}
		if (check(0, 1) && check1()){
			print();
		}
		return printf("-1\n"), 0;
	}
	for (int i = 0; i < 1 << 3; ++ i){
		bool flag = check(0, i & 1) && check(1, i >> 1 & 1) && check(2, i >> 2 & 1);
		if (flag && check1()){
			print();
		}
	}
	return printf("-1\n"), 0;
}
