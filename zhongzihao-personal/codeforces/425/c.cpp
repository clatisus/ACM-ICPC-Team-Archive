#include<bits/stdc++.h>

const int N = 1000000;
const int M = 100010;

int n, s;
int x[M], v[M], t[M];

double calc(double mid){
	double zero = 1e10, mil = 1e10;
	for (int i = 0; i < n; ++ i){
		if (t[i] == 2){
			if (x[i] < mid){
				mil = std::min(mil, 1.0 * (N - x[i]) / v[i]);
			}
			else{
				double time = (x[i] - mid) / (s - v[i]);
				double sit = time * s + mid;
				if (sit > N){
					mil = std::min(mil, 1.0 * (N - x[i]) / v[i]);
				}
				else{
					mil = std::min(mil, time + (N - sit) / (v[i] + s));
				}
			}
		}
		else{
			if (x[i] > mid){
				zero = std::min(zero, 1.0 * x[i] / v[i]);
			}
			else{
				double time = (mid - x[i]) / (s - v[i]);
				double sit = mid - time * s;
				if (sit < 0){
					zero = std::min(zero, 1.0 * x[i] / v[i]);
				}
				else{
					zero = std::min(zero, time + sit / (v[i] + s));
				}
			}
		}
	}
	return std::max(zero, mil);
}

int main(){
	scanf("%d%d", &n, &s);
	for (int i = 0; i < n; ++ i){
		scanf("%d%d%d", &x[i], &v[i], &t[i]);
	}
	double left = 0, right = 1e6;
	for (int i = 0; i < 300; ++ i){
		double mid1 = (2 * left + right) / 3, mid2 = (left + 2 * right) / 3;
		if (calc(mid1) < calc(mid2)){
			right = mid2;
		}
		else{
			left = mid1;
		}
	}
	int ans = left;
	return printf("%.10lf\n", std::min(calc(ans), calc(ans + 1))), 0;
}
