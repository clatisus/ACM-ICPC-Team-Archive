#include<bits/stdc++.h>

const double PI = std::acos(-1.0);

const int MAX = 1 << 18;

void read(int &x){
	char ch;
	while (!isdigit(ch = getchar()));
	x = ch - '0';
	while (isdigit(ch = getchar())){
		x = x * 10 + ch - '0';
	}
}

void read(double &x){
	char ch;
	while (!isdigit(ch = getchar()));
	x = ch - '0';
	while (isdigit(ch = getchar())){
		x = x * 10 + ch - '0';
	}
	if (ch != '.') return;
	double scale = 1;
	while (isdigit(ch = getchar())){
		x += (scale *= 0.1) * (ch - '0');
	}
}

struct comp{
	double real, imag;
	
	comp():real(0), imag(0){}
	comp(double real, double imag):real(real), imag(imag){}
	
	comp operator +(const comp &c)const{
		return comp(real + c.real, imag + c.imag);
	}
	
	comp operator -(const comp &c)const{
		return comp(real - c.real, imag - c.imag);
	}
	
	comp operator *(const comp &c)const{
		return comp(real * c.real - imag * c.imag, real * c.imag + imag * c.real);
	}
	
	comp operator *(const double &d)const{
		return comp(real * d, imag * d);
	}
	
	comp conj()const{
		return comp(real, -imag);
	}
};	

comp w[2][MAX];

void FFT(comp *a, int length, int type){
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
		for (int j = 0, szk = 1 << i - 1, szw = MAX >> i; j < length; j += 1 << i){
			for (int k = j, noww = 0; k < j + szk; ++ k, noww += szw){
				comp s = a[k], t = w[~type ? 0 : 1][noww] * a[k + szk];
				a[k] = s + t, a[k + szk] = s - t;
			}
		}
	}
	if (type == 1) return;
	double coe = 1.0 / length;
	for (int i = 0; i < length; ++ i){
		a[i] = a[i] * coe;
	}
}

comp aux[MAX], aux1[MAX];
double tmp[MAX];

void mult(double *a, int lena, double *b, int lenb, int &lenans){
	if (!~lena || !~lenb){
		lenans = 0;
		return;
	}
	if (lena + lenb <= 2000){
		memset(tmp, 0, sizeof(double) * (lena + lenb + 1));
		for (int i = 0; i <= lena; ++ i){
			for (int j = 0; j <= lenb; ++ j){
				tmp[i + j] += a[i] * b[j];
			}
		}
		lenans = lena + lenb;
		return;
	}
	int n = lena + lenb;
	lenans = 1;
	for ( ; lenans <= n; lenans <<= 1)
		;
	/*
	for (int i = 0; i < lenans; ++ i){
		aux[i] = comp(i > lena ? 0 : a[i], i > lenb ? 0 : b[i]);
	}
	FFT(aux, lenans, 1);
	for (int i = 0; i < lenans; ++ i){
		aux1[i] = aux[i ? lenans - i : 0].conj();
	}
	for (int i = 0; i < lenans; ++ i){
		aux[i] = (aux[i] + aux1[i]) * (aux[i] - aux1[i]) * comp(0, -0.25);
	}
	*/
	for (int i = 0; i < lenans; ++ i){
		aux[i] = comp(i > lena ? 0 : a[i], 0);
		aux1[i] = comp(i > lenb ? 0 : b[i], 0);
	}
	FFT(aux, lenans, 1);
	FFT(aux1, lenans, 1);
	for (int i = 0; i < lenans; ++ i){
		aux[i] = aux[i] * aux1[i];
	}
	FFT(aux, lenans, -1);
	lenans = n;
	for (int i = 0; i <= n; ++ i){
		tmp[i] = aux[i].real;
	}
}

const int N = 100010;

double f[N], g[N], v[N], r[N], a[N], b[N];
int n;

void solve(int left, int right){
	if (left == right){
		f[left] *= v[left];
		if (left < n){
			g[left + 1] = g[left] + f[left] / (n - left);
		}
		return;
	}
	int mid = left + right >> 1;
	solve(left, mid);
	for (int i = left; i <= mid; ++ i){
		a[i - left] = g[i] / (n - i) / v[i];
	}
	for (int i = 1; i <= right - left; ++ i){
		b[i] = 1 - r[i];
	}
	int lenans;
	mult(a, mid - left, b, right - left, lenans);
	for (int i = mid + 1; i <= right; ++ i){
		f[i] += tmp[i - left];
	}
	solve(mid + 1, right);
}

void solve(){
	read(n);
	for (int i = 1; i <= n; ++ i){
		read(v[i]);
	}
	for (int i = 0; i <= n; ++ i){
		f[i] = 0;
	}
	for (int i = 1; i <= n - 1; ++ i){
		read(r[i]);
	}
	f[0] = 1;
	g[1] = 1.0 / n;
	solve(1, n);
	printf("%.10lf\n", f[n] + g[n] - 1);
}

int main(){
	//freopen("data.txt", "r", stdin);
	for (int i = 0; i < MAX; ++ i){
		for (int j = 0; j < 2; ++ j){
			double angle = 1.0 * i / (MAX >> 1) * PI;
			w[j][i] = comp(std::cos(angle), (j ? -1 : 1) * std::sin(angle));
		}
	}
	int test;
	read(test);
	while (test --){
		solve();
	}
	return 0;
}
