#include<bits/stdc++.h>

const long double INF = 1e100;
const long double eps = 1e-9;
const long double PI = acos(-1.0);

inline long double sqr(long double x){return x * x;}

inline int sig(long double p){
	if (std::abs(p) < eps) return 0;
	return p > 0 ? 1 : -1;
}

class P{
public:
	long double x, y;
	P () : x(0), y(0){}
	P (long double x, long double y) : x(x), y(y){}
	P operator + (const P &p)const &{return {x + p.x, y + p.y};}
	P operator - (const P &p)const &{return {x - p.x, y - p.y};}
	P operator * (const long double &p)const &{return {x * p, y * p};}
	friend P operator * (const long double &p, const P & q){return {p * q.x, p * q.y};}
	P operator / (const long double &p)const &{return {x / p, y / p};}
	long double dot(P p){return x * p.x + y * p.y;}
	long double det(P p){return x * p.y - p.x * y;}
	long double abs(){return sqrt(sqr(x) + sqr(y));}
	long double abs2(){return sqr(x) + sqr(y);}
	//逆时针旋转90度 
	P rot90(){return {-y, x};}
};

// 返回圆 c1 和圆 c2 相交部分的面积 
long double areaCC(P c1, long double r1, P c2, long double r2){
	long double d = (c1 - c2).abs();
	if (r1 + r2 < d + eps){
		return 0;
	}
	if (d < std::abs(r1 - r2) + eps){
		long double r = std::min(r1, r2);
		return sqr(r) * PI;
	}
	long double x = (sqr(d) + sqr(r1) - sqr(r2)) / (2 * d);
	long double t1 = acos(x / r1);
	long double t2 = acos((d - x) / r2);
	return sqr(r1) * t1 + sqr(r2) * t2 - d * r1 * sin(t1);
}

int main(){
	int x1, y1, x2, y2, r1, r2;
	scanf("%d%d%d%d%d%d", &x1, &y1, &r1, &x2, &y2, &r2);
	P c1 = {x1, y1}, c2 = {x2, y2};
	printf("%.13lf\n", (double) areaCC(c1, r1, c2, r2));
	return 0;
}
