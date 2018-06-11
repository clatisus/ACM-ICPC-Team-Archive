#include<bits/stdc++.h>

const double eps = 1e-9;
const double PI = acos(-1.0);

inline int sig(double p){
	return (p > eps) - (p < -eps);
}

inline double sqr(double p){return p * p;}

class P{
public:
	double x, y;
	P (double x = 0, double y = 0) : x(x), y(y){}
	P operator + (const P &p)const &{return P (x + p.x, y + p.y);}
	P operator - (const P &p)const &{return P (x - p.x, y - p.y);}
	P operator * (const double &p)const&{return P (x * p, y * p);}
	friend P operator * (const double &d, const P &p){return P (d * p.x, d * p.y);}
	P operator / (const double &p)const &{return P (x / p, y / p);}
	double operator ^ (const P &p)const &{return x * p.y - y * p.x;}
	double operator % (const P &p)const &{return x * p.x + y * p.y;}
	double abs2()const &{return *this % *this;}
	double abs()const &{return std::sqrt(abs2());}
	double angle()const &{return std::atan2(y, x);}
	
	// 逆时针旋转 rad 弧度 
	P rot(const double &rad)const &{
		double sin = std::sin(rad), cos = std::cos(rad);
		return P (x * cos - y * sin, x * sin + y * cos);
	}
	
	bool operator < (const P &p)const &{
		if (!sig(x - p.x)) return sig(y - p.y) < 0;
		return sig(x - p.x) < 0;
	}
	
	bool operator == (const P &p)const &{
		return !sig(x - p.x) && !sig(y - p.y);
	}
	
	void read(){
		scanf("%lf%lf", &x, &y);
	}
};

bool parallel(P p1, P p2){
	return !sig(p1 ^ p2);
}

double isLL(P p1, P v1, P p2, P v2){
	P u = p2 - p1;
	return (u ^ v2) / (v1 ^ v2); // t 是交点在 p1v1 上的位置，可以用来判断射线、线段等
}

int n, m;

const int N = 1010;

P p[N];

void solve(){
	P l1, l2;
	l1.read(), l2.read();
	bool flag = false;
	if (!sig(l1.x - l2.x)){
		flag = true;
		std::swap(l1.x, l1.y);
		std::swap(l2.x, l2.y);
		for (int i = 0; i < n; ++ i){
			std::swap(p[i].x, p[i].y);
		}
	}
	if (l1.x > l2.x){
		std::swap(l1, l2);
	}
	double ans = 0;
	for (int i = 0; i < n; ++ i){
		P p1 = p[i], p2 = p[(i + 1) % n];
		if (parallel(p2 - p1, l2 - l1)){
			continue;
		}
		double t = isLL(p1, p2 - p1, l1, l2 - l1);
		if (sig(t) < 0 || sig(t - 1) > 0) continue;
		P p = p1 + t * (p2 - p1);
		int ssig = sig(p2.x - p1.x) ? sig(p2.x - p1.x) : sig(p2.y - p1.y);
		if (!sig((p2 - p1) % (l2 - l1))){
			ans += ssig * p.x;
			continue;
		}
		if (sig((p1 - p) ^ (l2 - l1)) < 0){
			ssig *= sig((p1 - p) % (l2 - l1)) > 0;
		}
		else{
			ssig *= sig((p2 - p) % (l2 - l1)) > 0;
		}
		ans += ssig * p.x;
	}
	printf("%.10lf\n", std::abs(ans) * (l2 - l1).abs() / (l2.x - l1.x));
	if (flag){
		for (int i = 0; i < n; ++ i){
			std::swap(p[i].x, p[i].y);
		}
	}
}

int main(){
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++ i){
		p[i].read();
	}
	while (m --){
		solve();
	}
	return 0;
}
