#include<bits/stdc++.h>

const double PI = acos(-1.0);

void FFT(std::complex <double> *a, int length, int type){
	std::complex <double> *w = new std::complex <double> [length];
	for (int i = 0; i < length; ++ i){
		double angle = 1.0 * i / (length >> 1) * PI;
		w[i] = std::complex <double>(cos(angle), type * sin(angle));
	}
	int len = -1;
	for (int x = length; x; ++ len, x >>= 1)
		;
	for (int i = 1, j = 0; i < length - 1; ++ i){
		for (int s = length; j ^= s >>= 1, ~j & s; )
			;
		if (i < j){
			std::swap(a[i], a[j]);
		}
	}
	for (int i = 1; i <= len; ++ i){
		for (int j = 0, szk = 1 << i - 1, szw = length >> i; j < length; j += 1 << i){
			for (int k = j, noww = 0; k < j + szk; ++ k, noww += szw){
				std::complex <double> s = a[k], t = w[noww] * a[k + szk];
				a[k] = s + t, a[k + szk] = s - t;
			}
		}
	}
	delete [] w;
	if (type == 1) return;
	for (int i = 0; i < length; ++ i){
		a[i] /= length;
	}
}
