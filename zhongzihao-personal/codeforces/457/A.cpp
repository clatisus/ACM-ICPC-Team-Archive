#include<bits/stdc++.h>

bool check(int x, int y){
	return x % 10 == 7 || x / 10 == 7 || y % 10 == 7 || y / 10 == 7;
}

int main(){
	int x, h, m;
	scanf("%d%d%d", &x, &h, &m);
	int cnt = 0;
	while (true){
		if (check(h, m)){
			return printf("%d\n", cnt), 0;
		}
		m -= x;
		if (m < 0){
			m += 60;
			-- h;
		}
		if (h < 0){
			h += 24;
		}
		++ cnt;
	}
	return 0;
}
