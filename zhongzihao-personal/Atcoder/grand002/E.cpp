#include<bits/stdc++.h>

const int N = 100010;

int a[N];

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
	}
	if (n == 1){
		puts(a[0] & 1 ? "Second" : "First");
		return 0;
	}
	std::sort(a, a + n, std::greater <int>());
	int sit;
	for (sit = 0; sit < n - 1; ++ sit){
		if (a[sit] <= sit) break;
	}
	-- sit;
	if (sit == n - 2){
		if (a[n - 1] <= sit){
			puts(a[n - 2] - sit & 1 ? "Second" : "First");
			return 0;
		}
		puts(a[n - 1] - sit & 1 ? "First" : "Second");
		return 0;
	}
	int cnt = 0;
	for (int i = sit + 1; i < n; ++ i){
		cnt += a[i] == sit + 1;
	}
	puts((cnt & 1) || (a[sit] - sit - 1 & 1) ? "First" : "Second");
	return 0;
}
