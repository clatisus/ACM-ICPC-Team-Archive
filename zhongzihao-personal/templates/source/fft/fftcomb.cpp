#include<bits/stdc++.h>
#include"fft.cpp"

const int N = 1 << 17;
typedef long long ll;
typedef std::complex <double> comp;

void mult(int *a, int lena, int *b, int lenb, int moder){
	int mod = std::sqrt(moder) + 2;
	static comp aux[N], aux1[N], aux2[N], aux3[N], aux4[N], aux5[N];
	int n = lena + lenb;
	int lengthret = 1;
	for ( ; lengthret <= n; lengthret <<= 1)
		;
	memset(aux, 0, sizeof(comp) * lengthret);
	memset(aux1, 0, sizeof(comp) * lengthret);
	for (int i = 0; i <= lena; ++ i){
		aux[i] = comp(a[i] / mod, a[i] % mod);
	}
	for (int i = 0; i <= lenb; ++ i){
		aux1[i] = comp(b[i] / mod, b[i] % mod);
	}
	FFT(aux, lengthret, 1);
	FFT(aux1, lengthret, 1);
	for (int i = 0; i < lengthret; ++ i){
		comp x = std::conj(aux[i ? lengthret - i : 0]);
		aux2[i] = (aux[i] + x) * comp(0.5, 0);
		aux3[i] = (aux[i] - x) * comp(0, -0.5);
		x = std::conj(aux1[i ? lengthret - i : 0]);
		aux4[i] = (aux1[i] + x) * comp(0.5, 0);
		aux5[i] = (aux1[i] - x) * comp(0, -0.5);
	}
	for (int i = 0; i < lengthret; ++ i){
		aux[i] = aux2[i] * aux4[i] + comp(0, 1) * aux3[i] * aux5[i];
		aux1[i] = aux3[i] * aux4[i] + comp(0, 1) * aux2[i] * aux5[i];
	}
	FFT(aux, lengthret, -1);
	FFT(aux1, lengthret, -1);
	for (int i = 0; i <= n; ++ i){
		int x = (ll) (aux[i].real() + 0.5) % moder;
		int y = (ll) (aux[i].imag() + 0.5) % moder;
		int u = (ll) (aux1[i].real() + 0.5) % moder;
		int v = (ll) (aux1[i].imag() + 0.5) % moder;
		a[i] = (1ll * x * mod * mod + y + 1ll * u * mod + 1ll * v * mod) % moder;
	}
}

int main(){
}
