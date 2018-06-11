#include<bits/stdc++.h>

const int N = 100010;

int a[N];
int n, l, t;

int main(){
	scanf("%d%d%d", &n, &l, &t);
	long long cnt = 0;
	for (int i = 0, w; i < n; ++ i){
		scanf("%d%d", &a[i], &w);
		if (w == 1){
			a[i] += t;
			cnt += a[i] / l;
			a[i] %= l;
		}
		else{
			a[i] -= t;
			cnt += a[i] / l;
			a[i] %= l;
			if (a[i] < 0){
				a[i] += l;
				-- cnt;
			}
		}
	}
	std::sort(a, a + n);
	cnt %= n;
	cnt = (cnt + n) % n;
	for (int i = 0; i < n; ++ i){
		printf("%d\n", a[(i + cnt) % n]);
	}
	return 0;
}
