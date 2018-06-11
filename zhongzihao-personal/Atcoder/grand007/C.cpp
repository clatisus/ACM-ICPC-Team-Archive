#include<bits/stdc++.h>

const int N = 200010;

double s[N], t[N];

int main(){
	s[1] = t[1] = 0.5;
	for (int i = 2; i < N; ++ i){
		s[i] = 0.5 + s[i - 1] * (i + 1) / i;
		t[i] = (i + 1) / 4.0 + (s[i - 1] + (2 * i + 4) * t[i - 1]) / (2 * i);
	}
	int n, d, x;
	scanf("%d%d%d", &n, &d, &x);
	double ans = (2 * d - 3 * x) * s[n] + 4 * x * t[n];
	printf("%.10lf\n", ans);
	return 0;
}
