#include<bits/stdc++.h>

const int N = 110;
const long double INF = 1e12;
const long double PI = acos(-1.0);
inline long double sqr(long double x){return x * x;}

int x[N], y[N];
long double ans[N];

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i){
		scanf("%d%d", &x[i], &y[i]);
	}
	std::vector <long double> vec = {0, 2 * PI};
	for (int i = 0; i < n; ++ i){
		for (int j = i + 1; j < n; ++ j){
			long double angle = std::atan2(y[j] - y[i], x[j] - x[i]) + PI / 2;
			while (angle < 0) angle += PI;
			while (angle >= PI) angle -= PI;
			vec.push_back(angle);
			vec.push_back(angle + PI);
		}
	}
	std::sort(vec.begin(), vec.end());
	for (int i = 0, sz = vec.size(); i < sz - 1; ++ i){
		long double min = 1e200, angle = (vec[i] + vec[i + 1]) / 2;
		long double xx = INF * std::cos(angle), yy = INF * std::sin(angle);
		int sit;
		for (int j = 0; j < n; ++ j){
			long double dis = sqr(xx - x[j]) + sqr(yy - y[j]);
			if (dis < min){
				min = dis;
				sit = j;
			}
		}
		ans[sit] += vec[i + 1] - vec[i];
	}
	for (int i = 0; i < n; ++ i){
		printf("%.10lf\n", (double) ans[i] / (2 * (double) PI));
	}
	return 0;
}
