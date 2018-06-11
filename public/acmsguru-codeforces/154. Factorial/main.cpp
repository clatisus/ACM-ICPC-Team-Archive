#include <bits/stdc++.h>

using ll = long long;

ll count_factor(int x, int y){
	ll res = 0;
	while(x){
		res += x/y;
		x /= y;
	}
	return res;
}

int main(){
	int Q, l = 1, r = 500000000;
	scanf("%d", &Q);
	while(l<r){
		int mid = (l + r) >> 1;
		if(count_factor(mid, 5) >= Q) r = mid;
		else l = mid + 1;
	}
	if(count_factor(l, 5) == Q) printf("%d\n", l);
	else puts("No solution");
	return 0;
}
