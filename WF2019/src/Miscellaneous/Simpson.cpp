#include<bits/stdc++.h>

const double eps = 1e-5;

double simpson(double l, double r, double (*f)(double)){
	double mid = (l + r) * 0.5;
	return (f(l) + 4 * f(mid) + f(r)) * (r - l) / 6;
}

double asr(double l, double r, double eps, double value, double (*f) (double)){
	double mid = (l + r) * 0.5;
	double left = simpson(l, mid, f), right = simpson(mid, r, f);
	if (std::abs(left + right - value) < 15 * eps){
		return left + right + (left + right - value) / 15;
	}
	return asr(l, mid, eps / 2, left, f) + asr(mid, r, eps / 2, right, f);
}

double calc(double l, double r, double (*f) (double), double eps) {
	return asr(l, r, eps, simpson(l, r, f), f);
}

int main(){
}
