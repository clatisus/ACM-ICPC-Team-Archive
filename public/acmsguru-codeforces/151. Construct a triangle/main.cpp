#include<bits/stdc++.h>

const long double eps = 1e-12;
typedef long long ll;

inline long double sqr(long double n){return n * n;}
inline ll sqr(int n){return 1ll * n * n;}
inline int sig(long double n){return (n > eps) - (n < -eps);}
inline long double normalize(long double n){return sig(n) ? n : 0.0;}

ll sqrt(ll n){
	ll ret = std::max(0ll, (ll) std::sqrt(n) - 3);
	while (ret * ret <= n){
		++ ret;
	}
	return ret - 1;
}

int main(){
	long double a, b, m;
	scanf("%Lf%Lf%Lf", &a, &b, &m);
	int aa = std::round(a * 1000) + 0.1, bb = std::round(b * 1000) + 0.1, mm = std::round(m * 1000) + 0.1;
	ll c2 = 2 * sqr(aa) + 2 * sqr(bb) - 4 * sqr(mm);
	if (c2 < 0){
		puts("Mission impossible");
		return 0;
	}
	ll cc = sqrt(c2);
	if (cc * cc != c2){
		cc = cc / 10 * 10 + 5;
	}
	if (aa + bb < cc || aa + cc < bb || bb + cc < aa){
		puts("Mission impossible");
		return 0;
	}
	long double anglecos = (4 * sqr(m) - sqr(a) - sqr(b)) / (2 * a);
	long double anglesin = std::sqrt(sqr(b) - sqr(anglecos));
	long double ax = 0.0, ay = 0.0;
	long double bx = normalize(a), by = 0.0;
	long double cx = normalize(anglecos), cy = normalize(anglesin);
	printf("%.5Lf %.5Lf\n", ax, ay);
	printf("%.5Lf %.5Lf\n", bx, by);
	printf("%.5Lf %.5Lf\n", cx, cy);
	//printf("%.10lf\n", std::sqrt(sqr((bx + cx) / 2 - ax) + sqr((by + cy) / 2 - ay)));
	return 0;
}
