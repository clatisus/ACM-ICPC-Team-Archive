#include<bits/stdc++.h>

class field2{
public:
	int x, y, a, p;
	
	field2():x(0), y(0), a(0), p(0){}
	field2(int x, int y, int a, int p):x(x), y(y), a(a), p(p){}
	
	field2 operator * (const field2 &f)const{
		int retx = (1ll * x * f.x + 1ll * y * f.y % p * a) % p;
		int rety = (1ll * x * f.y + 1ll * y * f.x) % p;
		return field2(retx, rety, a, p);
	}
	
	field2 powermod(int exp)const{
		field2 ret(1, 0, a, p), aux = *this;
		for ( ; exp > 0; exp >>= 1){
			if (exp & 1){
				ret = ret * aux;
			}
			aux = aux * aux;
		}
		return ret;
	}
};

class field3{
public:
	int x, y, z, a, p;
	
	field3():x(0), y(0), z(0), a(0), p(0){}
	field3(int x, int y, int z, int a, int p):x(x), y(y), z(z), a(a), p(p){}
	
	field3 operator * (const field3 &f)const{
		int retx = 1ll * x * f.x % p;
		retx = (retx + 1ll * y * f.z % p * a) % p;
		retx = (retx + 1ll * z * f.y % p * a) % p;
		int rety = (1ll * x * f.y + 1ll * y * f.x) % p;
		rety = (rety + 1ll * z * f.z % p * a) % p;
		int retz = (1ll * x * f.z + 1ll * z * f.x) % p;
		retz = (retz + 1ll * y * f.y) % p;
		return field3(retx, rety, retz, a, p);
	}
	
	field3 powermod(int exp)const{
		field3 ret(1, 0, 0, a, p), aux(*this);
		for ( ; exp; exp >>= 1){
			if (exp & 1){
				ret = ret * aux;
			}
			aux = aux * aux;
		}
		return ret;
	}
};

int powermod(int a, int exp, int moder){
	int ret = 1;
	for ( ; exp; exp >>= 1){
		if (exp & 1){
			ret = 1ll * ret * a % moder;
		}
		a = 1ll * a * a % moder;
	}
	return ret;
}

int randint(int n){
	return rand() % n;
}

std::vector <int> remain2(int a, int p){
	if (!a || p == 2){
		return {a};
	}
	if (powermod(a, p - 1 >> 1, p) != 1){
		return {};
	}
	while (true){
		field2 f(randint(p - 1) + 1, randint(p - 1) + 1, a, p);
		f = f.powermod(p - 1 >> 1);
		if (f.x) continue;
		int ret = powermod(f.y, p - 2, p);
		return {ret, p - ret};
	}
}

std::vector <int> remain3(int a, int p){
	if (!a || p <= 3){
		return {a};
	}
	if (p % 3 == 2){
		return {powermod(a, (2 * p - 1) / 3, p)};
	}
	while (true){
		field3 f(randint(p - 1) + 1, randint(p - 1) + 1, randint(p - 1) + 1, a, p);
		f = f.powermod((p - 1) / 3);
		if (f.x || f.z) continue;
		int ret = powermod(f.y, p - 2, p);
		std::vector <int> vec = remain2(p - 3, p);
		int root = 1ll * (vec[0] - 1 + p) % p * powermod(2, p - 2, p) % p;
		std::vector <int> ans;
		for (int i = 0; i < 3; ++ i){
			ans.push_back(ret);
			ret = 1ll * ret * root % p;
		}
		return ans;
	}
}

int main(){
	srand((unsigned) time(NULL));
	return 0;
}
