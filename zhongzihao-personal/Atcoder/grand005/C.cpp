#include<bits/stdc++.h>

const int N = 110;

int cnt[N];

void no(){
	puts("Impossible");
	exit(0);
}

int main(){
	int n;
	scanf("%d", &n);
	int min = INT_MAX, max = 0;
	for (int i = 0, x; i < n; ++ i){
		scanf("%d", &x);
		++ cnt[x];
		min = std::min(min, x);
		max = std::max(max, x);
	}
	if (cnt[min] < 1 || cnt[min] > 2) no();
	if (cnt[min] == 1 && max != 2 * min || cnt[min] == 2 && max != 2 * min - 1) no();
	for (int i = min + 1; i <= max; ++ i){
		if (cnt[i] < 2) no();
	}
	puts("Possible");
	return 0;
}
