#include<bits/stdc++.h>

const int N = 1010;
typedef long long ll;

double x[N], y[N];

double det(double x1, double y1, double x2, double y2){
	return x1 * y2 - x2 * y1;
}

int main(){
	int n;
	scanf("%d", &n);
	assert(n >= 3 && n <= 1000);
	for (int i = 0; i < n; ++ i){
		scanf("%lf%lf", &x[i], &y[i]);
		assert(x[i] >= -10000 && x[i] <= 10000 && y[i] >= -10000 && y[i] <= 10000);
	}
	for (int i = 0; i < n; ++ i){
		printf("%d\n", i);
		if (det(x[(i + 2) % n] - x[i], y[(i + 2) % n] - y[i], x[(i + 1) % n] - x[i], y[(i + 1) % n] - y[i]) < 0) assert(0);
	}
	double ans = 0;
	for (int i = 0; i < n - 1; ++ i){
		ans += (x[i] - x[0]) * (y[i + 1] - y[0]) - (x[i + 1] - x[0]) * (y[i] - y[0]);
	}
	return printf("%.3lf\n", std::abs(ans / 2)), 0;
}
